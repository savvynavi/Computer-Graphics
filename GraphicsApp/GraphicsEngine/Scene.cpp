#include "Scene.h"



Scene::Scene(){
	
}

Scene::Scene(std::vector<Instance*> instances, glm::vec3 globalLighting) : m_instances(instances), m_globalLighting(globalLighting){

}


Scene::~Scene(){

}

//remove all camera changes from graphApp and place here
void Scene::Update(){
	camera.Update();
	for each(Instance* object in m_instances){
		object->UpdateTransform();
	}
}

void Scene::Draw(){
	for each(Instance* object in m_instances){
		//object->Draw();
	}
}
