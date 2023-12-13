#pragma once
#include "Shader.h"


class Material {

public:
	Material(Shader* _shader, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _ambient, float _reflectivity)
	:shader(_shader), diffuse(_diffuse), specular(_specular), ambient(_ambient), reflectivity(_reflectivity){}
	~Material() {}
public:
	Shader* shader;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float reflectivity;
};