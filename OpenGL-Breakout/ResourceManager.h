#pragma once
#include <map>
#include "Shader.h"
#include <string>
#include "Texture2D.h"

#define GLEW_STATIC
#include <GL/glew.h>

class ResourceManager
{



public:

	// 定义着色器与纹理存储
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures;

	// 定义 Shader 交互方法
	static Shader LoadShader(const GLchar *vertexShaderFile, const GLchar *fragmentShaderFile, const GLchar *geometryShaderFile, std::string name);
	static Shader GetShader(std::string name);

	// 定义 Texture2D 交互方法
	static Texture2D LoadTexture2D(const GLchar *file, GLboolean alpha, std::string name);
	static Texture2D GetTexture2D(std::string name);

	ResourceManager();
	~ResourceManager();
};

