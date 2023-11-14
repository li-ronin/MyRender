#pragma once
#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include<iostream>
#include<fstream>
#include<Sstream>
#include<string>

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

private:
	void checkCompileError(unsigned int ID, std::string type);
};