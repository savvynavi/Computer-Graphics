#include "Camera.h"



Camera::Camera(){

}


Camera::~Camera(){

}

void Camera::setPerspective(float fieldOfView, float aspectRatio, float near, float far) {

}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up) {

}

void Camera::setPosition(glm::vec3 position) {
	
}

glm::mat4 Camera::getWorldTransform() {
	return m_worldTransform;
}

glm::mat4 Camera::getView() {
	return m_viewTransform;
}

glm::mat4 Camera::getProjection() {
	return m_projectionTransform;
}

glm::mat4 Camera::getProjectionView() {
	return m_projectionViewTransform;
}

void Camera::updateProjectionViewTransform() {

}
