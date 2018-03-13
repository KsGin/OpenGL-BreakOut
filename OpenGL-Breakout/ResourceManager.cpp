#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
}

Shader ResourceManager::loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile,
	const GLchar* gShaderFile) {
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar* file, GLboolean alpha) {
}

Shader ResourceManager::LoadShader(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile,
	const GLchar* geometryShaderFile, std::string name) {
}

Shader ResourceManager::GetShader(std::string name) {
}

Texture2D ResourceManager::LoadTexture2D(const GLchar* file, GLboolean alpha, std::string name) {
}

Texture2D ResourceManager::GetTexture2D(std::string name) {
}
