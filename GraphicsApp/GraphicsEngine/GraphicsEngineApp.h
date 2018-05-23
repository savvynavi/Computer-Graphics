#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include"Camera.h"
#include"Mesh.h"
#include"Shader.h"
#include"OBJMesh.h"
#include"Instance.h"

class GraphicsEngineApp : public aie::Application {
public:

	GraphicsEngineApp();
	virtual ~GraphicsEngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	bool dragonsSetup();
	void dragonsDraw();
	bool meshTest();
	void meshTestDraw();

protected:

	// camera transforms
	glm::mat4				m_viewMatrix;
	glm::mat4				m_projectionMatrix;

	aie::Texture			m_gridTex;
	aie::ShaderProgram		m_shader;
	Mesh					m_mesh;
	glm::mat4				m_quadTransform;
	aie::OBJMesh			m_bunny;
	glm::mat4				m_bunnyTransform;
	aie::OBJMesh*			m_dragon;
	glm::mat4				m_dragonTransform;
	aie::OBJMesh*			m_sword;

	Instance*				m_testInstance;
	Instance*				m_dragon2;

	struct Light{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	Light					m_light;
	glm::vec3				m_ambientLight;

	Camera* camera;
};