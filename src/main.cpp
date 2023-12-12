#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include "Shader.h"
#include"GL/glew.h"
#include"GL/wglew.h"
#include"GLFW/glfw3.h"
#include "stb_image.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>


 //选择独显来渲染（仅针对N卡有效)。 需要wglew.h
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}


float cube[] = {
	//     ---- 位置 ----      - 纹理坐标 -	
		-0.5f,  0.5f, 0.5f,    0.0f, 1.0f,   // 左上 3
		-0.5f, -0.5f, 0.5f,    0.0f, 0.0f,   // 左下 2
		 0.5f, -0.5f, 0.5f,    1.0f, 0.0f,   // 右下 1     前
		 0.5f, -0.5f, 0.5f,    1.0f, 0.0f,   // 右下 1
		 0.5f,  0.5f, 0.5f,    1.0f, 1.0f,   // 右上 0 
		-0.5f,  0.5f, 0.5f,    0.0f, 1.0f,   // 左上 3 
		
		 
	
		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f,   // 左上 7
		-0.5f, -0.5f, -0.5f,    0.0f, 0.0f,   // 左下 6   后
		 0.5f, -0.5f, -0.5f,    1.0f, 0.0f,   // 右下 5
		 0.5f, -0.5f, -0.5f,    1.0f, 0.0f,   // 右下 5
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,   // 右上 4 
		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f,   // 左上 7
		
		-0.5f, -0.5f, -0.5f,    0.0f, 0.0f,   // 左下 6  
		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f,   // 左上 7   左
		-0.5f,  0.5f,  0.5f,    1.0f, 1.0f,   // 左上 3 
		-0.5f,  0.5f,  0.5f,    1.0f, 1.0f,   // 左上 3 
		-0.5f, -0.5f,  0.5f,    1.0f, 0.0f,   // 左下 2
		-0.5f, -0.5f, -0.5f,    0.0f, 0.0f,   // 左下 6  

		 0.5f, -0.5f, -0.5f,    1.0f, 0.0f,   // 右下 5
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,   // 右上 4   右
		 0.5f,  0.5f,  0.5f,    0.0f, 1.0f,   // 右上 0
		 0.5f,  0.5f,  0.5f,    0.0f, 1.0f,   // 右上 0
		 0.5f, -0.5f,  0.5f,    0.0f, 0.0f,   // 右下 1  
		 0.5f, -0.5f, -0.5f,    1.0f, 0.0f,   // 右下 5

		 0.5f,  0.5f,  0.5f,    1.0f, 0.0f,   // 右上 0 
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,   // 右上 4
		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f,   // 左上 7  上
		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f,   // 左上 7
		-0.5f,  0.5f,  0.5f,    0.0f, 0.0f,   // 左上 3
		 0.5f,  0.5f,  0.5f,    1.0f, 0.0f,   // 右上 0 

		-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,   // 左下 6
		 0.5f, -0.5f, -0.5f,    1.0f, 1.0f,   // 右下 5
		 0.5f, -0.5f,  0.5f,    1.0f, 0.0f,   // 右下 1
		 0.5f, -0.5f,  0.5f,    1.0f, 0.0f,   // 右下 1  下
		-0.5f, -0.5f,  0.5f,    0.0f, 0.0f,   // 左下 2
		-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,   // 左下 6

};
// 【物体中心位置】
glm::vec3 cubePositions[] = {
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),
	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
};

//【相机】
glm::vec3 cameraPos = glm::vec3{ 0.0f, 0.0f, 3.0f };
glm::vec3 WorldUp = glm::vec3{ 0.0f, 1.0f, 0.0f };
Camera MyCamera{ cameraPos, 0.0f, 0.0f, WorldUp };

// 记录每一帧的时间
float deltaTime = 0.0f;
float lastFrameTime = 0.0f;

// 【键盘输入】
void processKeyBoardInput(GLFWwindow* window) {
	// 按下ESC退出窗口
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	// 根据每一帧的时间间隔来调整相机速度，确保移动速度平稳
	if (deltaTime != 0)
	{
		MyCamera.CameraMoveSpeed = deltaTime * 5;
	}
	//camera前后左右根据镜头方向移动
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		MyCamera.PosUpdateForward();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		MyCamera.PosUpdateBackward();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		MyCamera.PosUpdateLeft();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		MyCamera.PosUpdateRight();
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		MyCamera.PosUpdateUp();
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		MyCamera.PosUpdateDown();
}

// 【鼠标控制镜头方向】
// 上一帧 鼠标在屏幕的X位置
float lastX=0.0f;  
float lastY=0.0f;
bool firstMouse = true;
float MouseSensitivity = 0.05f;
void MouseCallback(GLFWwindow* window, double currX, double currY) {
	if (firstMouse == true)
	{
		firstMouse = false;
		lastX = currX;
		lastY = currY;
	}
	float deltaX = (currX - lastX) * MouseSensitivity;
	float deltaY = (currY - lastY) * MouseSensitivity;
	lastX = currX;
	lastY = currY;
	MyCamera.ProcessMouseMove(deltaX, deltaY);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// GLFW window
	int ScreenWidth = 1600;
	int ScreenHeight = 900;
	GLFWwindow* window = glfwCreateWindow(ScreenWidth, ScreenHeight, "MyShader", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Open Window failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//关闭鼠标显示
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, MouseCallback);


	// Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Init GLEW failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, ScreenWidth, ScreenHeight);
	// 启动深度缓存
	glEnable(GL_DEPTH_TEST);

	Shader myShader("./src/glsl/vertexSource.glsl", "./src/glsl/fragmentSource.glsl");

	// 【定义VAO VBO EBO】
	unsigned int VAO;
	unsigned int VBO;
	//unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// 【绑定VAO】
	glBindVertexArray(VAO);
	// 【绑定EBO】
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 【绑定VBO并加入数据】
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	/*	 
	 * 【向VAO解释VBO】
	 * glVertexAttribPointer( )
	 * ①：0:程序需要选中0号栏位开始放入；
	 * ②：3:把我们送进去的这些数值，每3个当成一份资料
	 * ⑤：n*sizeof(float): 步长 每隔3*float个长度去挖下一个
	 * ⑥：(void*)(3*sizeof(float)): 偏移量，表示数据在缓冲中距离起始位置的偏移量。位置属性在数组开头，所有偏移是0
	 */
	// 顶点位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);	
	// 顶点颜色属性
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
	//glEnableVertexAttribArray(1);
	// uv属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	//【生成Texture】
	stbi_set_flip_vertically_on_load(true); // 图像上下颠倒问题

	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//【加载并配置纹理】
	int width, height, nrChannel;
	unsigned char* data = stbi_load("./dependencies/wall.jpg", &width, &height, &nrChannel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}else
	{
		printf("Failed to load texture");
	}
	stbi_image_free(data);

	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TexBufferB);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// load texture
	unsigned char* data2 = stbi_load("./dependencies/face.jpg", &width, &height, &nrChannel, 0);
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture");
	}
	stbi_image_free(data2);


	//【定义变换矩阵】:trans
	//glm::mat4 trans = glm::mat4(1.0f);
	//// 1、平移
	//trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
	//// 2、欧拉角旋转（有万象死锁的问题）
	//// trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//// 2、四元数旋转
	//// 如：cos(40°/2) + sin(40°/2) (0.67i - 0.67j - 0.33k)
	//// [0.67, -0.67, -0.33]是旋转轴，40是旋转角度
	//// MyQuaternion = glm::quat(w, x, y, z)
	//glm::quat MyQuaternion = glm::quat(cos(glm::radians(0.0f)), 0, 0, sin(glm::radians(0.0f)));
	//// 将四元数转化成矩阵
	//glm::mat4 RotationMatrix = glm::mat4_cast(MyQuaternion);
	//trans *= RotationMatrix;
	//// 3、缩放
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));



	
	//   Model矩阵：将物体从局部坐标转为世界坐标
	/*glm::mat4 ModelMat;
	ModelMat = glm::rotate(ModelMat, glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 0.0f));*/

	//   View矩阵：将相机作为新的原点（位置以及相机坐标轴的方向），将整个世界空间以及空间中的物体变换到观察空间。
	//      glm中的lookat函数可以得到观察矩阵ViewMat = glm::lookat(相机位置， 相机视野朝向， 世界空间的向上的向量)
	
	
	//   Projection矩阵
	// glm::radians(45.0f)：视角/半视角
	// 800.0f/600.0f,
	// 0.1f  ：近平面 
	// 100.0f：远平面

	while (!glfwWindowShouldClose(window))
	{
		processKeyBoardInput(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


		glm::mat4 ViewMat;
		ViewMat = MyCamera.GetViewMat();
		glm::mat4 Projection;
		Projection = glm::perspective(glm::radians(45.0f), float(ScreenWidth) / float(ScreenHeight), 0.1f, 100.0f);

		for (int i = 0; i < 10; i++)
		{
			//   Model矩阵：将物体从局部坐标转为世界坐标
			glm::mat4 ModelMat;
			ModelMat = glm::translate(ModelMat, cubePositions[i]);
			float angle = 20.0f * i;
			ModelMat = glm::rotate(ModelMat, glm::radians(angle), glm::vec3(1.0f, 1.0f, 0.0f));
		
			myShader.use();
			glUniform1i(glGetUniformLocation(myShader.ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(myShader.ID, "ourFace"), 1);
			glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(ModelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(ViewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "projMat"), 1, GL_FALSE, glm::value_ptr(Projection));
			glDrawArrays(GL_TRIANGLES, 0, 36);


		}
		

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();

		float currFrameTime = glfwGetTime();
		deltaTime = currFrameTime - lastFrameTime;
		lastFrameTime = currFrameTime;

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}
