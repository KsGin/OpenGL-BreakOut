#pragma once
#include <vector>
#include "GameObject.h"

class GameLevel {
public:
	std::vector<GameObject> bricks;
	GameLevel();
	// ���ļ��м��عؿ�
    void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
    // ��Ⱦ�ؿ�
    void Draw(SpriteRenderer &renderer);
    // ���һ���ؿ��Ƿ������ (���зǼ�Ӳ�Ĵ�ש�����ݻ�)
    GLboolean IsCompleted();
private:
    // ��ש�����ݳ�ʼ���ؿ�
	void Init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};
