#include "GameLevel.h"
#include <fstream>
#include <sstream>
#include "ResourceManager.h"

GameLevel::GameLevel() {

}

void GameLevel::Load(const GLchar* file, const GLuint levelWidth, const GLuint levelHeight) {
	this->bricks.clear();
	GLuint tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line)) // 读取关卡文件的每一行
		{
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode) // 读取被空格分隔的每个数字
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (!tileData.empty())
			this->Init(tileData, levelWidth, levelHeight);
	}
	fstream.close();
}

void GameLevel::Draw(SpriteRenderer& renderer) {
	for (auto& tile : this->bricks)
        if (!tile.destroyed)
            tile.Draw(renderer);
}

GLboolean GameLevel::IsCompleted() {
	for (auto& tile : this->bricks)
        if (!tile.isSolid && !tile.destroyed)
            return GL_FALSE;
    return GL_TRUE;
}

void GameLevel::Init(std::vector<std::vector<GLuint>> tileData, const GLuint levelWidth, const GLuint levelHeight) {
	const auto height = tileData.size();
	const auto width = tileData[0].size();
	const auto unitWidth = levelWidth / static_cast<GLfloat>(width);
	const auto unitHeight = static_cast<GLfloat>(levelHeight) / height;
	for (GLuint y = 0; y < height; ++y)
	{
		for (GLuint x = 0; x < width; ++x)
		{
			const glm::vec2 pos(unitWidth * x, unitHeight * y);
			const glm::vec2 size(unitWidth, unitHeight);

			if (tileData[y][x] == 1)
			{
				GameObject obj(pos, size,
					ResourceManager::GetTexture2D("block_solid"),
					glm::vec3(1.0f, 0.1f, 0.1f)
				);
				obj.isSolid = GL_TRUE;
				this->bricks.push_back(obj);
			} else if (tileData[y][x] > 1)
			{
				auto color = glm::vec3(0.5f); 
				if (tileData[y][x] == 2)
					color = glm::vec3(0.3f, 0.2f, 0.0f);
				else if (tileData[y][x] == 3)
					color = glm::vec3(0.1f, 0.3f, 0.1f);
				else if (tileData[y][x] == 4)
					color = glm::vec3(0.4f, 0.6f, 0.1f);
				else if (tileData[y][x] == 5)
					color = glm::vec3(0.3f, 0.1f, 0.9f);
				this->bricks.emplace_back(pos, size, ResourceManager::GetTexture2D("block"), color);
			}
		}
	}
}
