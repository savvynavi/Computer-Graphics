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

out vec4 FragColour;

void main(){
	vec3 N = normalize(vNormal);
	vec3 L = normalize(LightDirection);
	
	float lambertTerm = max(0, min(1, dot(N, -L)));

	//calculate view vector and reflection vector
	vec3 V = normalize(CameraPosition - vPosition.xyz);
	vec3 R = reflect(L, N);

	//calc speculat term
	float specularTerm = pow(max(0, dot(R, V)), specularPower);
		
	//calculate each colour property
	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * lambertTerm;
	vec3 specular = Is * Ks * specularTerm;
	
	FragColour = vec4(ambient + diffuse + specular, 1);
}