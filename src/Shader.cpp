#include "Shader.h"

 
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	 //�Ӵ���(�ļ�·��)�л�ȡ"������ɫ��"��"Ƭ����ɫ��"
	std::ifstream vertFile;
	std::ifstream fragFile;
	// ���ļ�
	vertFile.open(vertexPath);
	fragFile.open(fragmentPath);
	//��֤ifstream��������׳��쳣��
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