#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include"Camera.h"
#include"Mesh.h"
#include"Shader.h"
#include"OBJMesh.h"
#include"Instance.h"
#include"Scene.h"

class GraphicsEngineApp : public aie::Application {
public:

	GraphicsEngineApp();
	virtual ~GraphicsEngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	bool lightingTest();
	bool normMapSword();

protected:

	// camera transforms
	glm::mat4				m_viewMatrix;
	glm::mat4				m_projectionMatrix;

	aie::ShaderProgram		m_shader;
	Mesh					m_mesh;
	glm::mat4				m_quadTransform;
	aie::OBJMesh*			m_dragon;

	Scene*					m_scene;
	Instance*				m_instance1;
	Instance*				m_instance2;

	aie::ShaderProgram		m_swordShader;
	aie::OBJMesh*			m_sword;
	Instance*				m_instance3;

	Camera* camera;
};