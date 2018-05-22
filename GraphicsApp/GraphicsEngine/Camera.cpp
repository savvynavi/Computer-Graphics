#include "Camera.h"



Camera::Camera() : theta(0), phi(-20), position(-10, 4, 0){

}


Camera::~Camera(){
	
}

glm::mat4 Camera::GetProjectionMatrix(float width, float height) {
	return glm::perspective(glm::pi<float>() * 0.25f, width / height, 0.1f, 1000.0f);
}

glm::mat4 Camera::GetViewMatrix() {
	float thetaR = theta * deg2Rad;
	float phiR = phi * deg2Rad;
	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	return glm::lookAt(position, position + forward, glm::vec3(0, 1, 0));
}

void Camera::Update() {
	aie::Input* input = aie::Input::getInstance();
	float thetaR = theta * deg2Rad;
	float phiR = phi * deg2Rad;

	//calculates the axes
	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
	glm::vec3 up(0, 1, 0);

	float deltaTime = 0.1f;

	//movement up/down
	if (input->isKeyDown(aie::INPUT_KEY_X)) {
		position += up * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_Z)) {
		position += -up * deltaTime;
	}
	//movement around using WSAD
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		position += -right * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		position += right * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		position += forward * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		position += -forward * deltaTime;
	}

	//rotating camera by holding mouse button down + dragging
	float mx = input->getMouseX();
	float my = input->getMouseY();
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT)) {
		theta += 0.05f *(mx - lastMouseX);
		phi -= 0.05f * (my - lastMouseY);
	}
	lastMouseX = mx;
	lastMouseY = my;
}