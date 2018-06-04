#pragma once
#include<vector>
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include"Camera.h"
#include"Instance.h"

class Scene{
public:
	Scene();
	Scene(std::vector<Instance*> instances, glm::vec3 globalLighting = {});
	~Scene();

	void Draw();
	void Update();
protected:
	std::vector<Instance*> m_instances;
	glm::vec3 m_globalLighting;
	Camera camera;
};

