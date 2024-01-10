#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
	int init(const char* title);

	void processInput();
	int close();

	void clearBuffer();
	void postProcess();

	static void framebuffer_size_callback(GLFWwindow* windowp, int width, int height);

	GLFWwindow* getWindow() { return window; }

	~Window();

private:
	
	GLFWwindow* window;
};