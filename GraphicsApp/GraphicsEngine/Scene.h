#pragma once
#include<vector>
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include"Camera.h"
#include"Instance.h"

class Scene{
public:
	Scene();
	Scene(std::vector<Instance*> instances, Camera* camera, glm::mat4 projectMat, glm::mat4 viewMat, glm::vec3 lightDir = {}, glm::vec3 lightAmbient = {}, glm::vec3 lightDiffuse = {}, glm::vec3 lightSpecular = {});
	~Scene();

	void Draw(int windowWidth, int windowHeight);
	void Update();
protected:
	struct Light{
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	Light m_light;
	std::vector<Instance*> m_instances;
	glm::vec3 m_globalLighting;
	Camera* m_camera;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;

};

