#include "Shader.h"

 
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	 //从磁盘(文件路径)中获取"顶点着色器"和"片段着色器"
	std::ifstream vertFile;
	std::ifstream fragFile;
	// 打开文件
	vertFile.open(vertexPath);
	fragFile.open(fragmentPath);
	//保证ifstream对象可以抛出异常：
	vertFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	try
	{
		if (!vertFile.is_open() || !fragFile.is_open())
		{
			throw std::exception("open file eror");
		}
		std::stringstream vertSStream;
		std::stringstream fragSStream;
		vertSStream << vertFile.rdbuf();
		fragSStream << fragFile.rdbuf();
		vertexStringBuffer = vertSStream.str();
		fragmentStringBuffer = fragSStream.str();
		vertexSource = vertexStringBuffer.c_str();
		fragmentSource = fragmentStringBuffer.c_str();

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);

		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		glValidateProgram(ID);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::SetUniform3f(const char* name, glm::vec3 vector) {
	glUniform3f(glGetUniformLocation(ID, name), vector.x, vector.y, vector.z);
}

void Shader::SetUniform1f(const char* name, float f) {
	glUniform1f(glGetUniformLocation(ID, name), f);
}

void Shader::checkCompileError(unsigned int shader_id, std::string type)
{
	int result;
	
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(shader_id, length, &length, message);
			std::cout << "shader compile error:" << message << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader_id, GL_LINK_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetProgramInfoLog(shader_id, length, &length, message);
			std::cout << "program linking error:" << message << std::endl;
		}
	}
	
}