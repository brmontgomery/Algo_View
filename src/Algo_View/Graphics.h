#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

class Window {
public:
	int init(const char* title);

	void processInput();
	void render(std::vector<int>& numList);

	void clearBuffer();
	void postProcess();

	static void framebuffer_size_callback(GLFWwindow* windowp, int width, int height);
	GLFWwindow* getWindow() { return window; }

	int close();
	~Window();

private:
	
	GLFWwindow* window;
};