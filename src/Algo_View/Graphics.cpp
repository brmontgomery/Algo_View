#include "Graphics.h"
#include <iostream>

int Window::init(const char* title) {
    //getting a size for the window based on the size of the screen
    //vars for getting the center of screen
    int monitorCount;
    int windowWidth, windowHeight;
    int monitorX, monitorY;

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();

    //logic for getting imensions of screen and calculating center
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);
    windowWidth = videoMode->width / 1.5;
    windowHeight = windowWidth / 16 * 9;

    glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //hide window before creation so that we can center it before showing it
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // glfw window creation
    window = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    //set the window in the center
    glfwSetWindowPos(window, monitorX + (videoMode->width - windowWidth) / 2, monitorY + (videoMode->height - windowHeight) / 2);
    //show window after centering it
    glfwShowWindow(window);

    //finish configuring screen
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    clearBuffer();
}

void Window::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Window::render(std::vector<int>& numList) {
    // preprocess for the loop
        // -----
    processInput();
    clearBuffer();

    // render
    // ------
    float l = (float)numList.size();
    float widthAdder = 1 / l;

    for (int i = 0; i < numList.size(); ++i)
    {
        glBegin(GL_POLYGON);

        // + 1 so value of 0 has height of 1
        float arrayIndexHeightRatio = 2 * (numList[i] + 1) / l;
        float widthIndexAdder = 2 * i / l;

        float leftX = -1 + widthIndexAdder;
        float rightX = leftX + widthAdder;
        float bottomY = -1;
        float topY = bottomY + arrayIndexHeightRatio;

        // bottom left
        glColor4f(1, 0, 0, 0);
        glVertex2f(leftX, bottomY);

        // bottom right
        glColor4f(0, 1, 0, 0);
        glVertex2f(rightX, bottomY);

        // top right
        glColor4f(0, 0, 1, 0);
        glVertex2f(rightX, topY);

        // top left
        glColor4f(0, 0, 0, 1);
        glVertex2f(leftX, topY);

        glEnd();
    }

    // loop postprocessing
    // -------------------------------------------------------------------------------
    postProcess();
}

int Window::close() {
    return glfwWindowShouldClose(window);
}

void Window::clearBuffer() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::postProcess() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Window::framebuffer_size_callback(GLFWwindow* windowp, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

Window::~Window() {
    glfwTerminate();
}