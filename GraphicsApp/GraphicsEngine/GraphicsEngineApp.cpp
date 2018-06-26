#include "GraphicsEngineApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <imgui.h>

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
	camera = new Camera();

	//different scene loads
	lightingTest();
	//normMapSword();


	return true;
}

void GraphicsEngineApp::shutdown() {

	Gizmos::destroy();
}

void GraphicsEngineApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	//scene update
	m_scene->Update();

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void GraphicsEngineApp::draw() {

	// wipe the screen to the background colour
	clearScreen();
	//scene draw
	m_scene->Draw(getWindowWidth(), getWindowHeight());

	ImGui::BeginChild("Lights");
	ImGui::SliderFloat3("Light 1", (float*)&m_pointLightPositions[0],-20,20);
	ImGui::SliderFloat3("Light 2", (float*)&m_pointLightPositions[1],-20,20);
	//ImGui::DragFloat3("Light 2", &m_pointLightPositions[1]);
	ImGui::End();
}

//loads in 2 dragons with phong lighting
bool GraphicsEngineApp::lightingTest(){
	//shaders
	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");
	if(m_shader.link() == false){
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	m_swordShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/normalmap.vert");
	m_swordShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/normalmap.frag");
	if(m_swordShader.link() == false){
		printf("Shader Error: %s\n", m_swordShader.getLastError());
		return false;
	}

	m_sword = new aie::OBJMesh;
	if(m_sword->load("./soulspear/soulspear.obj", true, true) == false){
		printf("Soulspear Mesh Error\n");
		return false;
	}



	//model
	m_dragon = new aie::OBJMesh;

	if(m_dragon->load("./stanford/Dragon.obj") == false){
		printf("Dragon Mesh Error!\n");
		return false;
	}

	//point light setup
	PointLight pointLight;
	pointLight.pos = {2, 2, 1};
	pointLight.colour = {0, 0, 1 };
	pointLight.intensity = 100;

	PointLight pointLight2;
	pointLight2.pos = { 2, 10, 0};
	pointLight2.colour = { 1, 0, 0 };
	pointLight2.intensity = 75;

	m_pointLightPositions[0] = pointLight.pos;
	m_pointLightPositions[1] = pointLight2.pos;

	m_pointLightsColour[0] = pointLight.colour;
	m_pointLightsColour[1] = pointLight2.colour;

	m_pointLightsIntensity[0] = pointLight.intensity;
	m_pointLightsIntensity[1] = pointLight2.intensity;

	//creating instances and scene
	m_instance1 = new Instance(m_dragon, &m_shader, glm::vec3(0, 0, 0), glm::vec3(50, 50, 0), glm::vec3(0.5, 0.5, 0.5));
	m_instance2 = new Instance(m_dragon, &m_shader, glm::vec3(5, 5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	m_instance3 = new Instance(m_sword, &m_swordShader, glm::vec3(0, 0, -10), glm::vec3(50, 50, 50));
	m_instance4 = new Instance(m_sword, &m_swordShader, glm::vec3(0, 0, 10), glm::vec3(-50,50, -50));

	std::vector<Instance*> objects;
	objects.push_back(m_instance1);
	objects.push_back(m_instance2);
	objects.push_back(m_instance3);
	objects.push_back(m_instance4);

	m_scene = new Scene(objects, camera, m_projectionMatrix, m_viewMatrix, 
		{ 1, 0, 0 }, //light direction
		2, //number of point lights
		{ 0.25f, 0.25f, 0.25f }, // ambient light
		{ 1, 1, 0 },  // diffuse light
		{ 1, 1, 1 }, // specular light 
		&m_pointLightPositions[0], &m_pointLightsColour[0], &m_pointLightsIntensity[0]);
	return true;
}

//loads in textured swords with different shaders to compare normal mapping
bool GraphicsEngineApp::normMapSword(){
	//shaders
	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/normalmap.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/normalmap.frag");
	if(m_shader.link() == false){
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	m_swordShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/textured.vert");
	m_swordShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/textured.frag");
	if(m_swordShader.link() == false){
		printf("Shader Error: %s\n", m_swordShader.getLastError());
		return false;
	}

	m_sword = new aie::OBJMesh;
	if(m_sword->load("./soulspear/soulspear.obj", true, true) == false){
		printf("Soulspear Mesh Error\n");
		return false;
	}

	m_instance3 = new Instance(m_sword, &m_shader, glm::vec3(0, 0, 0), glm::vec3(10, 50, 0));
	m_instance1 = new Instance(m_sword, &m_swordShader, glm::vec3(0, 0, 2), glm::vec3(10, 50, 0));

	std::vector<Instance*> objects;
	objects.push_back(m_instance3);
	objects.push_back(m_instance1);

	//m_scene = new Scene(objects, camera, m_projectionMatrix, m_viewMatrix, { 1, 0, 0 }, { 0.25f, 0.25f, 0.25f }, { 1, 1, 0 }, { 1, 1, 0 });

	return true;
}
