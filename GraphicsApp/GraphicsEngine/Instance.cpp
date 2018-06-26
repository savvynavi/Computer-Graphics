#include <gl_core_4_4.h>
#include "Instance.h"
#include <glm/gtc/matrix_transform.hpp>

//add enum
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

void Instance::Draw(glm::mat4 projectionMat, glm::mat4 viewMat, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, glm::vec3 dir, int numLights, glm::vec3* lPos, glm::vec3* colour, float* intensity){
	m_shader->bind();
	glm::mat4 pmv = projectionMat * viewMat * m_transform;
	m_shader->bindUniform("ProjectionViewModel", pmv);
	m_shader->bindUniform("ModelMatrix", m_transform);
	m_shader->bindUniform("CameraPosition", glm::vec3(glm::inverse(viewMat)[3]));

	//phong shader stuff
	m_shader->bindUniform("Ia", amb);
	m_shader->bindUniform("Id", diff);
	m_shader->bindUniform("Is", spec);
	m_shader->bindUniform("LightDirection", dir);

	//point lights
	m_shader->bindUniform("numLights", numLights);
	m_shader->bindUniform("LightPosition", numLights, lPos);
	m_shader->bindUniform("pointLightIntensity", numLights, intensity);
	m_shader->bindUniform("pointLightColour", numLights, colour);

	m_mesh->draw();
}