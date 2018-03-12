#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WIDTH 1920
#define HEIGHT 1080

int main()
{
	/*初始化glfw*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //设置最大版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //设置最小版本
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //设置core-profile
	glfwWindowHint(GLFW_RESIZABLE, false); //设置不可改变大小
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//创建一个窗口
	const auto window = glfwCreateWindow(WIDTH, HEIGHT, "Breakout", nullptr, nullptr);

	//设置窗口环境
	glfwMakeContextCurrent(window);
	if (window == nullptr) {
		std::cout << "ERROR::CREATE_WINDOW_ERROR" << std::endl;
		glfwTerminate();
	}

	//设置glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::INIT_GLEW_ERROR" << std::endl;
		glfwTerminate();
	}

	//设置位置
	glViewport(0, 0, WIDTH, HEIGHT);

	while (!glfwWindowShouldClose(window)) {


		glfwPollEvents();
		glfwSwapBuffers(window);

	}

	return 0;

}