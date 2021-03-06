#version 410

in vec4 vPosition;
in vec3 vNormal;

//ambient + diffuse + speculat light colours
uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;

//material colours
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float specularPower;

uniform vec3 LightDirection;
uniform vec3 CameraPosition;

//point lights
uniform int numLights;
uniform vec3 LightPosition[4];
uniform vec3 pointLightColour[4];
uniform float pointLightIntensity[4];

out vec4 FragColour;

void main(){
	vec3 N = normalize(vNormal);

	// calculate ambient
	vec3 ambient = Ia * Ka;


	// uniform sunlight source
	vec3 L = normalize(LightDirection);
	
	float lambertTerm = max(0, min(1, dot(N, -L)));

	//calculate view vector and reflection vector
	vec3 V = normalize(CameraPosition - vPosition.xyz);
	vec3 R = reflect(L, N);

	//calc speculat term
	float specularTerm = pow(max(0, dot(R, V)), specularPower);
		
	//calculate each colour property
	
	vec3 diffuse = Id * Kd * lambertTerm;
	vec3 specular = Is * Ks * specularTerm;
	float attenuation = 1.0f;



	//point light (Loop it when you can have multiple point lights)

	for(int i = 0; i < numLights; i++){
		L = normalize(LightPosition[i] - vPosition.xyz);
	
		lambertTerm = max(0, min(1, dot(N, -L)));

		//calculate view vector and reflection vector
		V = normalize(CameraPosition - vPosition.xyz);
		float distFromLight = length(LightPosition[i] - vPosition.xyz);
		R = reflect(L, N);

		//calc speculat term
		specularTerm = pow(max(0, dot(R, V)), specularPower);
		
		//attenuation calculation for points
		attenuation = 1.0f / (0.01f + distFromLight*distFromLight);

		//calculate each colour property
		diffuse += pointLightColour[i] * Kd * lambertTerm * attenuation;
		specular += pointLightIntensity[i] * Ks * specularTerm * attenuation;
	}


	FragColour = vec4(ambient + (diffuse + specular), 1);
}