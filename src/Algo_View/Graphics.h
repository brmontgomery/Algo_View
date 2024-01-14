#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#include "imgui.h"
#include "glm/glm.hpp"
#include "AlgorithmStats.h"

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

//singleton class
class Graphics {
public:
	static Graphics* getInstance();

	void processInput();
	void render(std::vector<int>& numList, int index1, int index2, AlgorithmStats& stats);

	void clearBuffer();
	void postProcess();

	bool close();

	GLFWwindow* getWindow() { return window.getWindow(); };

	~Graphics();

private:
	static Graphics* inst_;   // The one, single instance
	Graphics(); // private constructor
	Graphics(const Graphics&);
	Graphics& operator=(const Graphics&);

	Window window;

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec2 inPos;\n"
		"layout (location = 1) in vec3 inColor;\n"

		"out vec4 vertColor;\n"

		"void main()\n"
		"{\n"
		"   gl_Position = vec4(inPos,1.0f, 1.0f);\n"
		"	vertColor = vec4(inColor, 1.0f);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor; \n"
		"in vec4 vertColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(vertColor);\n"
		"}\n\0";

	unsigned int shaderProgram;
	unsigned int VAO, VBO, EBO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};
#endif