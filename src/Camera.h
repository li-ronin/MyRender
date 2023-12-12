#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	~Camera();
	Camera(const glm::vec3 pos, const float pitch, const float yaw, const glm::vec3 world_up);
	Camera(const glm::vec3 pos, const glm::vec3 target, const glm::vec3 world_up);
	glm::mat4 GetViewMat() const;
	void PosUpdateForward();
	void PosUpdateBackward();
	void PosUpdateLeft();
	void PosUpdateRight();
	void PosUpdateUp();
	void PosUpdateDown();
	void ProcessMouseMove(float deltaX, float deltaY); // 鼠标XY的偏移量（规格化后的偏移量）
public:
	glm::vec3 Position;	//相机位置
	glm::vec3 WorldUp;	//世界空间-上方向
	glm::vec3 Up;		//相机的上方向Y+（也就是观察空间的上方向
	glm::vec3 Forward;	//相机的前方向Z+
	glm::vec3 Right;	//相机的右方向X+
	float Pitch;
	float Yaw;
	float CameraMoveSpeed = 0.5;
private:
	void UpdateCameraVectors();
	
};