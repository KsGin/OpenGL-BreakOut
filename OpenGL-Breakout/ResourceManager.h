#pragma once
#include <map>
#include "Shader.h"
#include <string>
#include "Texture2D.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <unordered_map>

class ResourceManager
{

    // Loads and generates a shader from file
    static Shader    LoadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
    // Loads a single texture from file
    static Texture2D LoadTextureFromFile(const GLchar *file, GLboolean alpha);
public:

	// ������ɫ��������洢
	static std::unordered_map<std::string, Shader> shaders;
	static std::unordered_map<std::string, Texture2D> textures;

	// ���� Shader ��������
	static Shader LoadShader(const GLchar *vertexShaderFile, const GLchar *fragmentShaderFile, const GLchar *geometryShaderFile,
	                         std::string name);
	static Shader GetShader(std::string name);

	// ���� Texture2D ��������
	static Texture2D LoadTexture2D(const GLchar *file, GLboolean alpha, std::string name);
	static Texture2D GetTexture2D(std::string name);
};

