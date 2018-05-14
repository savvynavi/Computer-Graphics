#pragma once
#include "Camera.h"

//lets you move camera with keyboard/mouse
class FlyCamera : protected Camera {
public:
	FlyCamera();
	FlyCamera(float speed);
	~FlyCamera();

	void update(float deltaTime);
	void setSpeed(float speed);
protected:
	float m_speed;
	glm::vec3 up;
};

