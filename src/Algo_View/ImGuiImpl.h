#ifndef _IMGUIIMPL_H_
#define _IMGUIIMPL_H_

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"

#include "AlgorithmStats.h"

//singleton class
class ImGuiImpl {
public:
	static ImGuiImpl* getInstance();

	void initImGui(GLFWwindow* window);
	void shutdown();
	ImGuiIO& getImGuiIO() { return io; };
	void startMenu(GLFWwindow* window, int& chosenAlgo, bool& render, int& rangeEnd);
	void stats(AlgorithmStats stats, GLFWwindow* window);

private:
	static ImGuiImpl* inst_;   // The one, single instance
	ImGuiImpl() {} // private constructor
	ImGuiImpl(const ImGuiImpl&);
	ImGuiImpl& operator=(const ImGuiImpl&);

	ImGuiIO io;
};




#endif