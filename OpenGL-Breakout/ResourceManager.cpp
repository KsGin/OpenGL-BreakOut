#include "ResourceManager.h"
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <Common/stb_image.h>

Shader ResourceManager::LoadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile,
	const GLchar* gShaderFile) {
	std::string vShaderCode, fShaderCode, gShaderCode;
	std::ifstream ifs(vShaderFile);
	if (!ifs.is_open()) std::cout << "ERROR::ResourceManager::LoadShaderFromFile::vShaderFile::FILE_OPEN_REEOR";
	while (!ifs.eof()) {
		std::string tmp;
		ifs >> tmp;
		vShaderCode += tmp;
	}
	ifs.close();
	ifs.open(fShaderFile);
	if (!ifs.is_open()) std::cout << "ERROR::ResourceManager::LoadShaderFromFile::fShaderFile::FILE_OPEN_REEOR";
	while (!ifs.eof()) {
		std::string tmp;
		ifs >> tmp;
		fShaderCode += tmp;
	}
	ifs.close();
	if (gShaderFile) {
		ifs.open(gShaderFile);
		if (!ifs.is_open()) std::cout << "ERROR::ResourceManager::LoadShaderFromFile::gShaderFile::FILE_OPEN_REEOR";
		while (!ifs.eof()) {
			std::string tmp;
			ifs >> tmp;
			gShaderCode += tmp;
		}
	}

	Shader shader;
	shader.Compile(vShaderCode.c_str(), fShaderCode.c_str(), gShaderCode.c_str());
	return shader;
}

Texture2D ResourceManager::LoadTextureFromFile(const GLchar* file, GLboolean alpha) {
	Texture2D texture;
	int width, height , channel;
	const auto data = stbi_load(file, &width, &height, &channel, 0);
	texture.Generate(width, height, data);
	return texture;
}

Shader ResourceManager::LoadShader(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile,
	const GLchar* geometryShaderFile, const std::string name) {
	const auto shader = LoadShaderFromFile(vertexShaderFile, fragmentShaderFile, geometryShaderFile);
	shaders[name] = shader;
	return shader;
}

Shader ResourceManager::GetShader(const std::string name) {
	return shaders[name];
}

Texture2D ResourceManager::LoadTexture2D(const GLchar* file, const GLboolean alpha, const std::string name) {
	const auto texture = LoadTextureFromFile(file, alpha);
	textures[name] = texture;
	return texture;
}

Texture2D ResourceManager::GetTexture2D(const std::string name) {
	return textures[name];
}
