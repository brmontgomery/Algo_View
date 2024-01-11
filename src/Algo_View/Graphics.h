#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include "glm/glm.hpp"

struct Vertex {
	// position
	glm::vec2 Position;
	// color
	glm::vec3 Color;
};

class Window {
public:
	int init(const char* title);

	static void framebuffer_size_callback(GLFWwindow* windowp, int width, int height);
	GLFWwindow* getWindow() { return gWindow; }

	int close();
	~Window();

private:
	GLFWwindow* gWindow;
};

class Graphics {
public:
	Graphics();

	void processInput();
	void render(std::vector<int>& numList);

	void clearBuffer();
	void postProcess();

	bool close();

	~Graphics();

private:
	Window window;
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec2 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"

		"out vec3 Color;\n"

		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos,1.0f, 1.0f);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor; \n"
		"in vec3 Color;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(Color, 1.0f);\n"
		"}\n\0";
	unsigned int shaderProgram;
	unsigned int VAO, VBO, EBO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};