#include "../include/shader.h"
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <bits/types/struct_timeval.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processinput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

std::string readShader(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Failed to open" << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout <<  "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	float vertices[] = {
		// positions		  // colors
		-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
	};


	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexShaderPath = "src/shaders/vertex.vert";
	std::string vertexShaderString = readShader(vertexShaderPath);
	const char* vertexShaderCStr = vertexShaderString.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderCStr, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	
	if(!success)
	{
	    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	} else {
		std::cout << "SHADER COMPILATION SUCCES" << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentShaderPath = "src/shaders/fragment.frag";
	std::string fragmentShaderString = readShader(fragmentShaderPath);
	const char* fragmentShaderCStr = fragmentShaderString.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderCStr, NULL);
	glCompileShader(fragmentShader);

	int  success2;
	char infoLog2[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);
	
	if(!success2)
	{
	    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2);
	    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog2 << std::endl;
	} else {
		std::cout << "SHADER COMPILATION SUCCES" << std::endl;
	}

	/*unsigned int shaderProgram;*/
	/*shaderProgram = glCreateProgram();*/
	/**/
	/*glAttachShader(shaderProgram, vertexShader);*/
	/*glAttachShader(shaderProgram, fragmentShader);*/
	/*glLinkProgram(shaderProgram);*/
	/**/
	/*int success3;*/
	/*char infoLog3[512];*/
	/*glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success3);*/
	/*if (!success3) {*/
	/*	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog3);*/
	/*	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog3 << std::endl;*/
	/*} else {*/
	/*	std::cout << "LINKING SUCCESFULL" << std::endl;*/
	/*}*/

	Shader myShader("src/shaders/vertex.vert", "src/shaders/fragment.frag");

	unsigned int VAO;
	unsigned int VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while(!glfwWindowShouldClose(window)) {
		// inputs
		processinput(window);

		// rendering ill probably do something cool here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();

		/*glUseProgram(shaderProgram);*/

		/*float timeValue = glfwGetTime();*/
		/*float greenValue = (sin(timeValue)/ 2.0f) + 0.5f;*/
		/*int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");*/

		/*glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// check and call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// clean up shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glfwTerminate();
	return 0;
}
