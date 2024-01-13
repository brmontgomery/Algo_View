#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <random>


#include "Graphics.h"
#include "Algorithm.h"

int main()
{
    //get a random list of numbers between rangeBegin and rangeEnd
    //set the begin and end values
    const int rangeBegin = 0;
    const int rangeEnd = 50;

    //set the size of the number list
    std::vector<int> randomNumberList(rangeEnd - rangeBegin);

    //generate the data by iterating over the number lists and inserting the numbers in order
    std::generate(randomNumberList.begin(), randomNumberList.end(), [number = rangeBegin]() mutable {return number++; });
    //shuffle the numbers after they have been added
    std::shuffle(randomNumberList.begin(), randomNumberList.end(), std::mt19937{ std::random_device{}() });

    //Graphics Init
    Graphics graphics;
    AlgorithmDiags diags;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(graphics.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // render loop
    // -----------
    bool show_demo_window = true;
    bool show_another_window = false;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!graphics.close())
    {   
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(&show_demo_window);
    

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(graphics.getWindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(graphics.getWindow());

        //ImGui::Begin("Hello, world!");
        //ImGui::End();
        //graphics.render(randomNumberList, -1, -1);
        //BubbleSort(graphics, randomNumberList, diags);
        //diags.print();
        //diags.clear();

        //ImGui::Render();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}