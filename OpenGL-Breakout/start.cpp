#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WIDTH 1920
#define HEIGHT 1080

void InitGlfw() {
	/*��ʼ��glfw*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //�������汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //������С�汾
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //����core-profile
	glfwWindowHint(GLFW_RESIZABLE, false); //���ò��ɸı��С
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}



void DisPlayColor() {
	static int r = 0;
	static int g = 128;
	static int b = 255;
	static int dr = 1;
	static int dg = 1;
	static int db = 1;

	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);

	r += dr;
	g += dg;
	b += db;

	if (r > 255 || r < 0) dr = -dr;
	if (g > 255 || g < 0) dg = -dg;
	if (b > 255 || b < 0) db = -db;

	glClear(GL_COLOR_BUFFER_BIT);

}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);	}

}



int main()
{
	InitGlfw();
	//����һ������
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Empty Window", nullptr, nullptr);

	//���ô��ڻ���
	glfwMakeContextCurrent(window);

	if (window == nullptr) {
		std::cout << "Faild to create glfw window" << std::endl;
		glfwTerminate();
	}

	//����glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Faild to init glew" << std::endl;
		return -1;
	}

	//����λ��
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		DisPlayColor();
		glfwSwapBuffers(window);

	}

	return 0;

}