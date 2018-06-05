#pragma once
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include"OBJMesh.h"
#include"Shader.h"

class Instance{
public:
	Instance(aie::OBJMesh* mesh, aie::ShaderProgram* shader,glm::vec3 pos = {}, glm::vec3 euler = {}, glm::vec3 scale = {1, 1, 1});
	~Instance();

	glm::mat4 getTransform(){ return m_transform; }
	void UpdateTransform();

	void Draw(glm::mat4 projectionMat, glm::mat4 viewMat, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, glm::vec3 dir);

	aie::ShaderProgram getShader(){ return *m_shader; }

protected:
	glm::vec3 m_pos;
	glm::vec3 m_euler;
	glm::vec3 m_scale;
	glm::mat4 m_transform;

	aie::OBJMesh* m_mesh;
	aie::ShaderProgram* m_shader;
};

