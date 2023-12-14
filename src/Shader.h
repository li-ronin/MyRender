#pragma once
#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include<iostream>
#include<fstream>
#include<Sstream>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader 
{
public:
	std::string vertexStringBuffer;
	std::string fragmentStringBuffer;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;  //Program ID
	/*
	* GLSL文件(磁盘)-->FileBuffer(内存)-->StringBuffer解释FileBuffer(内存)->
	* -->Char*(CPU，OpenGL不操作String，操作的是char数组)
	*/
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void SetUniform3f(const char* name, glm::vec3 vector);
	void SetUniform1f(const char* name, float f);
	void SetUniform1i(const char* name, unsigned int i);
	enum TextureSlot
	{
		DIFFUSE,
		SPECULAR,
		EMISSION
	};

private:
	void checkCompileError(unsigned int ID, std::string type);
};