#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include "Shader.h"
#include"GL/glew.h"
#include"GL/wglew.h"
#include"GLFW/glfw3.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include <string>
// 选择独显来渲染（仅针对N卡有效)。 需要wglew.h
//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}


// 需要顺时针
float vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};


//0 1 2   2 1 3
unsigned int indices[] = {
	0,1,2,
	2,3,0
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 600, "MyShader", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Open Window failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	// Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Init GLEW failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);

	Shader myShader("./src/vertexSource.glsl", "./src/fragmentSource.glsl");

	// 定义VAO VBO EBO
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 绑定VAO
	glBindVertexArray(VAO);
	// 绑定EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 绑定VBO并加入数据
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 向VAO解释VBO
	// 0:程序需要选中0号栏位开始放入；
	// 3:把我们送进去的这些数值，每3个当成一份资料
	// n*sizeof(float): 步长 每隔3*float个长度去挖下一个
	// 顶点位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);	
	// 顶点颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// uv属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// 生成Texture
	stbi_set_flip_vertically_on_load(true);
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

	// 加载并生成纹理
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


	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 trans = glm::mat4(1.0f);
		// 1、平移
		trans = glm::translate(trans, glm::vec3(1.0f, 0.0f, 0.0f));

		// 2、欧拉角旋转（有万象死锁的问题）
		// trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		// 2、四元数旋转
		// 如：cos(40°/2) + sin(40°/2) (0.67i - 0.67j - 0.33k)
		// [0.67, -0.67, -0.33]是旋转轴，40是旋转角度
		// MyQuaternion = glm::quat(w, x, y, z)
		glm::quat MyQuaternion = glm::quat(cos(glm::radians(22.5f)), 0, 0, sin(glm::radians(22.5f)));
		// 将四元数转化成矩阵
		glm::mat4 RotationMatrix = glm::mat4_cast(MyQuaternion);

		trans *= RotationMatrix;
		// 3、大小
		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBufferA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TexBufferB);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		myShader.use();
		glUniform1i(glGetUniformLocation(myShader.ID, "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(myShader.ID, "ourFace"), 1);
		glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}
