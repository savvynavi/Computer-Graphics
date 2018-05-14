#include "FlyCamera.h"



FlyCamera::FlyCamera() : m_speed(0), up(glm::vec3(0)){

}

FlyCamera::FlyCamera(float speed) : m_speed(speed), up(glm::vec3(0)){

}


FlyCamera::~FlyCamera(){

}

void FlyCamera::update(float deltaTime){

}

void FlyCamera::setSpeed(float speed){

}
