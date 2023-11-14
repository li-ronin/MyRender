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
	* GLSL�ļ�(����)-->FileBuffer(�ڴ�)-->StringBuffer����FileBuffer(�ڴ�)->
	* -->Char*(CPU��OpenGL������String����������char����)
	*/
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();

private:
	void checkCompileError(unsigned int ID, std::string type);
};