#version 330 core
layout (location = 0) in vec3 aPos;         // 位置变量的属性 位置值固定为0
//layout (location = 1) in vec3 aColor;     // 颜色变量的属性 位置值固定为1
layout (location = 2) in vec2 aTexCoord;    // uv变量的属性 位置值固定为2
layout (location = 3) in vec3 aNormal;      // 法向量的属性 位置值为 3

out vec2 TexCoord;      // uv位置坐标
out vec3 FragPos;       // 顶点在世界空间的坐标
out vec3 Normal;        // 顶点在世界空间的法向量

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
    gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0); 
    
    Normal = mat3(transpose(inverse(modelMat))) * aNormal; // 世界空间的法向量
    FragPos = (modelMat * vec4(aPos.xyz, 1.0f)).xyz;       // 物体在世界空间的坐标
    TexCoord = aTexCoord;
}