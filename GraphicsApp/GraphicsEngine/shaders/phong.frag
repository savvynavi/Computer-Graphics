#version 410

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

out vec4 FragColour;

void main(){
	vec3 N = normalize(vNormal);
	vec3 L = normalize(LightDirection);
	
	float lambertTerm = max(0, min(1, dot(N, -L)));
		
	//calculate each colour property
	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Ka * lambertTerm;
	
	FragColour = vec4(ambient + diffuse, 1);
}