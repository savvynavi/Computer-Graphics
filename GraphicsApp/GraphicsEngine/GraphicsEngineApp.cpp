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


	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");
	if(m_shader.link() == false){
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	if(m_gridTex.load("./textures/numbered_grid.tga") == false){
		printf("Failed to load texture\n");
		return false;
	}

	//m_mesh.initialiseQuad();
	//m_quadTransform = {
	//	10, 0, 0, 0,
	//	0, 10, 0, 0,
	//	0, 0, 10, 0,
	//	0, 0, 0, 1 };

	//Lighting
	m_light.diffuse = { 1, 1, 0 };
	m_light.specular = { 1, 1, 0 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };

	//Material
	m_material.ambient = {1, 1, 0};
	m_material.diffuse = {1, 1, 0};
	m_material.specular = {0.25f, 0.25f, 0.25f};

	//dragon model load
	m_dragon = new aie::OBJMesh;

	if(m_dragon->load("./stanford/Dragon.obj") == false){
		printf("Dragon Mesh Error!\n");
		return false;
	}

	m_testInstance = new Instance(m_dragon, &m_shader, glm::vec3(0, 0, 0), glm::vec3(10, 50, 0), glm::vec3(0.5, 0.5, 0.5));

	/*m_sword = new aie::OBJMesh;
	if(m_sword->load("./soulspear/soulspear.obj", true, true) == false){
		printf("Soulspear Mesh Error\n");
		return false;
	}

	m_testInstance = new Instance(m_sword, &m_shader);*/

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

	//light mesh stuff
	float time = getTime();
	m_light.direction = glm::normalize(vec3(glm::cos(time * 2), glm::sin(time * 2), 0));

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

	//dragonsDraw();

	//mesh texture stuff
	m_shader.bind();
	//lighting binding
	m_shader.bindUniform("Ia", m_ambientLight);
	m_shader.bindUniform("Id", m_light.diffuse);
	m_shader.bindUniform("Is", m_light.specular);

	m_shader.bindUniform("LightDirection", m_light.direction);

	//material binding
	//m_shader.bindUniform("Ka", m_material.ambient);
	//m_shader.bindUniform("Kd", m_material.diffuse);
	//m_shader.bindUniform("Ks", m_material.specular);

	auto pmv = m_projectionMatrix * m_viewMatrix * m_quadTransform;
	m_shader.bindUniform("ProjectionViewModel", pmv);
	m_shader.bindUniform("CameraPosition", glm::vec3(glm::inverse(m_viewMatrix)[3]));
	//m_shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_quadTransform)));

	////m_shader.bindUniform("diffuseTexture", 0);
	////m_gridTex.bind(0);
	//m_mesh.draw();

	//m_testInstance->Draw(m_projectionMatrix, m_viewMatrix);



	//dragon lighting test

	m_testInstance->Draw(m_projectionMatrix, m_viewMatrix);

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}

bool GraphicsEngineApp::dragonsSetup(){
	//shader stuff
	//m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	//m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");
	//if(m_shader.link() == false){
	//	printf("Shader Error: %s\n", m_shader.getLastError());
	//	return false;
	//}

	m_dragon = new aie::OBJMesh;

	if(m_dragon->load("./stanford/Dragon.obj") == false){
		printf("Dragon Mesh Error!\n");
		return false;
	}

	m_testInstance = new Instance(m_dragon, &m_shader, glm::vec3(0, 0, 0), glm::vec3(10, 50, 0), glm::vec3(0.5, 0.5, 0.5));
	m_dragon2 = new Instance(m_dragon, &m_shader, glm::vec3(0, 10, 0));
	return true;
}

void GraphicsEngineApp::dragonsDraw(){

	m_testInstance->Draw(m_projectionMatrix, m_viewMatrix);
	m_dragon2->Draw(m_projectionMatrix, m_viewMatrix);
}

bool GraphicsEngineApp::meshTest(){
	return true;
}

void GraphicsEngineApp::meshTestDraw(){

}
