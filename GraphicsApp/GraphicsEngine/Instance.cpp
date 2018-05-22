#include <gl_core_4_4.h>
#include "Instance.h"
#include <glm/gtc/matrix_transform.hpp>

Instance::Instance(aie::OBJMesh* mesh, aie::ShaderProgram* shader, glm::vec3 pos, glm::vec3 euler, glm::vec3 scale) : m_mesh(mesh), m_shader(shader), m_pos(pos), m_euler(euler), m_scale(scale){

}

Instance::~Instance(){

}

void Instance::UpdateTransform(){
	float rad = 6.28f / 360.0f;
	m_transform = glm::translate(glm::mat4(1), m_pos)
		* glm::rotate(glm::mat4(1),m_euler.z * rad, glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1),m_euler.y * rad, glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1),m_euler.x * rad, glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), m_scale);
}

void Instance::Draw(glm::mat4 projectionMat, glm::mat4 viewMat){
	m_shader->bind();
	glm::mat4 pmv = projectionMat * viewMat * m_transform;
	m_shader->bindUniform("ProjectionViewModel", pmv);
	m_mesh->draw();
}
