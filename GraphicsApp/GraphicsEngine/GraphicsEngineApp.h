#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include"FlyCamera.h"

class GraphicsEngineApp : public aie::Application {
public:

	GraphicsEngineApp();
	virtual ~GraphicsEngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	//setup functions
	void Test();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	FlyCamera* camera;
};