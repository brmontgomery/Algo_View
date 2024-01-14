#include "ImGuiImpl.h"// Setup Dear ImGui context

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Define the static Singleton pointer since it is a singleton
ImGuiImpl* ImGuiImpl::inst_ = NULL;

ImGuiImpl* ImGuiImpl::getInstance() {
    if (inst_ == NULL) {
        inst_ = new ImGuiImpl();
    }
    return(inst_);
}

void ImGuiImpl::initImGui(GLFWwindow* window) {
    //init ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

void ImGuiImpl::shutdown() {
    //get rid of the ImGui Implementation
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiImpl::startMenu(GLFWwindow* window, int& chosenAlgo, bool& render, int& rangeEnd) {
    //ImGui Frame for choosing algorithm
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Algo View!");

        ImGui::Text("Choose which sorting type you want to sort with.");
        if (ImGui::Button("Selecion Sort")) {                           // Buttons return true when clicked (most widgets return true when edited/activated)
            chosenAlgo = 0;
        }
        if (ImGui::Button("Bubble Sort")) {                           // Buttons return true when clicked (most widgets return true when edited/activated)
            chosenAlgo = 1;
        }

        ImGui::NewLine();
        ImGui::InputInt("Number of Values to Sort", &rangeEnd);
        ImGui::NewLine();
        ImGui::Checkbox("Render Visualization", &render);

        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}

void ImGuiImpl::stats(AlgorithmStats stats, GLFWwindow* window) {
    //ImGui frame for displaying algorithm stats during and directly after the algorithm runs
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Algo View!");

    ImGui::Text("Algorithm Stats.");
    ImGui::NewLine();
    ImGui::Text("Accesses: %d", stats.getAccesses());
    ImGui::NewLine();
    ImGui::Text("Comparisons: %d", stats.getComparisons());
    ImGui::NewLine();
    ImGui::Text("Swaps: %d", stats.getSwaps());


    ImGui::End();

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}