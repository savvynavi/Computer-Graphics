#pragma once
#include <glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include "Input.h"


class Camera{
public:
	Camera();
	~Camera();

	glm::mat4 GetProjectionMatrix(float width, float height);
	glm::mat4 GetViewMatrix();

	void Update();

protected:
	float theta;
	float phi;
	int lastMouseX;
	int lastMouseY;
	glm::vec3 position;	
	const float deg2Rad = (3.14159f / 180.0f);
};

