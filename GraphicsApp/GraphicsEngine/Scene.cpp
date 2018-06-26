#include "Scene.h"
#include "Gizmos.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

Scene::Scene(){
	
}

Scene::Scene(std::vector<Instance*> instances, Camera* camera, glm::mat4 projectMat, glm::mat4 viewMat, glm::vec3 lightDir, int numLights, glm::vec3 lightAmbient, glm::vec3 lightDiffuse, glm::vec3 lightSpecular, glm::vec3 lPos, glm::vec3 colour, float intensity) : m_instances(instances), m_camera(camera), m_projectionMatrix(projectMat), m_viewMatrix(viewMat), m_numLights(numLights), m_pointLightPos(lPos), m_pointLightColour(colour), m_intensity(intensity){
	m_light.direction = lightDir;
	m_light.ambient = lightAmbient;
	m_light.diffuse = lightDiffuse;
	m_light.specular = lightSpecular;
}

Scene::~Scene(){

}

//remove all camera changes from graphApp and place here
void Scene::Update(){
	
	////grid
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for(int i = 0; i < 21; ++i){
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}
	Gizmos::addTransform(mat4(1));

	m_camera->Update();
	for each(Instance* object in m_instances){
		object->UpdateTransform();
	}
}

void Scene::Draw(int windowWidth, int windowHeight){
	m_projectionMatrix = m_camera->GetProjectionMatrix(windowWidth, windowHeight);
	m_viewMatrix = m_camera->GetViewMatrix();

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
	Gizmos::draw2D((float)windowWidth, (float)windowHeight);

	for each(Instance* object in m_instances){
		object->Draw(m_projectionMatrix, m_viewMatrix, m_light.ambient, m_light.diffuse,m_light.specular, m_light.direction, m_numLights, m_pointLightPos, m_pointLightColour, m_intensity);
	}
}
