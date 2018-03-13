#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include <sstream>


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

}

Shader ResourceManager::LoadShader(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile,
	const GLchar* geometryShaderFile, const std::string name) {
	std::string vShaderCode, fShaderCode, gShaderCode;
	std::ifstream ifs(vertexShaderFile);
	if (!ifs.is_open()) std::cout << "ERROR::ResourceManager::LoadShaderFromFile::vShaderFile::FILE_OPEN_REEOR";
	while (!ifs.eof()) {
		std::string tmp;
		ifs >> tmp;
		vShaderCode += tmp;
	}
	ifs.close();
	ifs.open(fragmentShaderFile);
	if (!ifs.is_open()) std::cout << "ERROR::ResourceManager::LoadShaderFromFile::fShaderFile::FILE_OPEN_REEOR";
	while (!ifs.eof()) {
		std::string tmp;
		ifs >> tmp;
		fShaderCode += tmp;
	}
	ifs.close();
	if (geometryShaderFile) {
		ifs.open(geometryShaderFile);
		if (!ifs.is_open()) std::cout << "ERROR::ResourceManager::LoadShaderFromFile::gShaderFile::FILE_OPEN_REEOR";
		while (!ifs.eof()) {
			std::string tmp;
			ifs >> tmp;
			gShaderCode += tmp;
		}
	}

	Shader shader;
	shader.Compile(vShaderCode.c_str(), fShaderCode.c_str(), gShaderCode.c_str());
	shaders[name] = shader;
	return shader;
}

Shader ResourceManager::GetShader(std::string name) {

}

Texture2D ResourceManager::LoadTexture2D(const GLchar* file, GLboolean alpha, std::string name) {
}

Texture2D ResourceManager::GetTexture2D(std::string name) {
}
