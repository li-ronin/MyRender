#include "Camera.h"

Camera::Camera(const glm::vec3 pos, const float pitch, const float yaw, const glm::vec3 world_up) {
	Position = pos;
	WorldUp = world_up;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
	Forward.y = sin(glm::radians(Pitch));
	Forward.z = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	Forward = glm::normalize(Forward);
	Right = glm::normalize(glm::cross(world_up, Forward));
	Up = glm::cross(Forward, Right);
}
Camera::~Camera() {

}
glm::mat4 Camera::GetViewMat() const {
	return glm::lookAt(Position, Position - Forward, WorldUp);
}

void Camera::PosUpdateForward() {
	Position += CameraMoveSpeed * (-Forward);
}
void Camera::PosUpdateBackward() {
	Position -= CameraMoveSpeed * (-Forward);
}
void Camera::PosUpdateRight() {
	Position += CameraMoveSpeed * Right;
}
void Camera::PosUpdateLeft() {
	Position -= CameraMoveSpeed * Right;
}
void Camera::PosUpdateUp() {
	Position += CameraMoveSpeed * WorldUp;
}
void Camera::PosUpdateDown() {
	Position -= CameraMoveSpeed * WorldUp;
}

void Camera::ProcessMouseMove(float deltaX, float deltaY) {
	Pitch += deltaY;
	Yaw -= deltaX;
	UpdateCameraVectors();
	if (Pitch >  89.0f)Pitch =  89.0f;
	if (Pitch < -89.0f)Pitch = -89.0f;
}

void Camera::UpdateCameraVectors() {
	Forward.x = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
	Forward.y = sin(glm::radians(Pitch));
	Forward.z = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	Forward = glm::normalize(Forward);
	Right = glm::normalize(glm::cross(WorldUp, Forward));
	Up = glm::cross(Forward, Right);
}












