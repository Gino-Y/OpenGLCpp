#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window);

int main()
{
	glfwInit();//初始化函数库
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//版本设置主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//此版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW failed.");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);//侦测按键输入

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//清屏颜色
		glClear(GL_COLOR_BUFFER_BIT);//清理颜色缓存




		glfwSwapBuffers(window);
		glfwPollEvents();//获取操作事件
	}
	glfwTerminate();//终止
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}