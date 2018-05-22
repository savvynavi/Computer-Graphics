#include "GraphicsEngineApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

GraphicsEngineApp::GraphicsEngineApp() {

}

GraphicsEngineApp::~GraphicsEngineApp() {

}

bool GraphicsEngineApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	//shader stuff
	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");
	if (m_shader.link() == false) {
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	m_dragon = new aie::OBJMesh;

	if (m_dragon->load("./stanford/Dragon.obj") == false) {
		printf("Dragon Mesh Error!\n");
		return false;
	}

	m_testInstance = new Instance(m_dragon, &m_shader, glm::vec3(0, 0, 0), glm::vec3(10, 50, 0), glm::vec3(0.5, 0.5, 0.5));
	m_dragon2 = new Instance(m_dragon, &m_shader, glm::vec3(0, 10, 0));

	camera = new Camera();

	return true;
}

void GraphicsEngineApp::shutdown() {

	Gizmos::destroy();
}

void GraphicsEngineApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	camera->Update();
	m_testInstance->UpdateTransform();
	m_dragon2->UpdateTransform();

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void GraphicsEngineApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	//run different tests
	m_projectionMatrix = camera->GetProjectionMatrix(getWindowWidth(), getWindowHeight());
	m_viewMatrix = camera->GetViewMatrix();

	m_testInstance->Draw(m_projectionMatrix, m_viewMatrix);
	m_dragon2->Draw(m_projectionMatrix, m_viewMatrix);


	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}