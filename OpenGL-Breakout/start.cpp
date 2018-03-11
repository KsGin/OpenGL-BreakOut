#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WIDTH 1920
#define HEIGHT 1080

void InitGlfw() {
	/*��ʼ��glfw*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //�������汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //������С�汾
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //����core-profile
	glfwWindowHint(GLFW_RESIZABLE, false); //���ò��ɸı��С
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);	}

}



int main()
{
	InitGlfw();
	//����һ������
	const auto window = glfwCreateWindow(WIDTH, HEIGHT, "Breakout", nullptr, nullptr);

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

	//����λ��
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window)) {


		glfwPollEvents();
		glfwSwapBuffers(window);

	}

	return 0;

}