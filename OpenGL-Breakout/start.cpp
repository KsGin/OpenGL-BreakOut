#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"

float width = 1920;
float height = 1080;

int main()
{
	/*��ʼ��glfw*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //�������汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //������С�汾
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //����core-profile
	glfwWindowHint(GLFW_RESIZABLE, false); //���ò��ɸı��С
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//����һ������
	const auto window = glfwCreateWindow(width, height, "Breakout", nullptr, nullptr);

	//���ô��ڻ���
	glfwMakeContextCurrent(window);
	if (window == nullptr) {
		std::cout << "ERROR::CREATE_WINDOW_ERROR" << std::endl;
		glfwTerminate();
	}

	//����glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::INIT_GLEW_ERROR" << std::endl;
		glfwTerminate();
	}

	//����
	glViewport(0, 0, width, height);
	glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	auto game = Game(width , height);
	
	while (!glfwWindowShouldClose(window)) {

		game.Render();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return 0;

}