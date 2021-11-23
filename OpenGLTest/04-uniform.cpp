#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window);

float vertices[] = {
    -0.5f, -0.5f, 0.0f,//0
    0.5f, -0.5f, 0.0f,//1
	0.0f, 0.5f, 0.0f,//2
	0.0f, -1.0f, 0.0f//3
};

unsigned int indices[] = 
{
	0, 1, 2,
	0, 3, 1
};


const char* vertexShaderSource =
"#version 330 core                                                                   \n"
"layout(location = 0) in vec3 aPos; // 位置变量的属性位置值为0                       \n"
"                                                                                    \n"
"out vec4 vertexColor; // 为片段着色器指定一个颜色输出                               \n"
"                                                                                    \n"
"void main()                                                                         \n"
"{                                                                                   \n"
"	gl_Position = vec4(aPos, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数   \n"
"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // 把输出变量设置为暗红色                \n"
"}                                                                                   \n";
                                                                                     
const char* fragmentShaderSource = 
"#version 330 core                                                                   \n"
"out vec4 FragColor;                                                                 \n"
"                                                                                    \n"
"in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）            \n"
"uniform vec4 ourColor;                                                              \n"
"                                                                                    \n"
"void main()                                                                         \n"
"{                                                                                   \n"
"	FragColor = ourColor;                                                         \n"
"}                                                                                   \n";

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


    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glVertexAttribPointer(0/*texcoodid*/, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);//侦测按键输入

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//清屏颜色
        glClear(GL_COLOR_BUFFER_BIT);//清理颜色缓存

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        float timeValue = glfwGetTime() * 5; //获取时间                                                              //外部传入值
        float dynamicValue = sin(timeValue) * 0.5f + 0.5f;                                                           //外部传入值
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor"); //外部传入值控制shader            //外部传入值
        glUseProgram(shaderProgram);                                                                                 
        glUniform4f(vertexColorLocation, 0, dynamicValue, 0, 1.0f);                                                  //外部传入值

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


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