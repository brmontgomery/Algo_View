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
    //glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // glfw window creation
    gWindow = glfwCreateWindow(windowWidth, windowHeight, "Algo_View", NULL, NULL);
    
    if (gWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    //set the window in the center
    glfwSetWindowPos(gWindow, monitorX + (videoMode->width - windowWidth) / 2, monitorY + (videoMode->height - windowHeight) / 2);
    //show window after centering it
    glfwShowWindow(gWindow);

    //finish configuring screen
    glfwMakeContextCurrent(gWindow);
    glfwSetFramebufferSizeCallback(gWindow, &framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
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

int Window::close() {
    return glfwWindowShouldClose(gWindow);
}

Graphics::Graphics() {
    window.init("Algo_View");
    clearBuffer();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Graphics::processInput()
{
    if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.getWindow(), true);
}

void Graphics::render(std::vector<int>& numList, int index1, int index2) {
    // preprocess for the loop
        // -----
    processInput();

    // render
    // ------
    float listSize = (float)numList.size();
    float boxWidth = 1 / listSize;

    unsigned int indice = 0;

    for (int i = 0; i < numList.size(); ++i)
    {
        // + 1 so value of 0 has height of 1
        float arrayIndexHeight = 1.9 * (numList[i] + 1) / listSize;
        float widthIndexAdder = 2 * i / listSize;

        float leftX = -1 + widthIndexAdder + (boxWidth / 2);
        float rightX = leftX + boxWidth;
        float bottomY = -.95;
        float topY = bottomY + arrayIndexHeight;

        //create the vertices
        Vertex vert;

        //set the color to green if it is one of the ones that we are marking green
        if (i == index1 || i == index2) {
            vert.Color.r = 0.0f;
            vert.Color.g = 1.0f;
            vert.Color.b = 0.0f;
        }
        else {
            vert.Color.r = 1.0f;
            vert.Color.g = 1.0f;
            vert.Color.b = 1.0f;
        }

        //bottom left
        vert.Position.x = leftX; 
        vert.Position.y = bottomY;
        vertices.push_back(vert);

        // bottom right
        vert.Position.x = rightX;
        vert.Position.y = bottomY;
        vertices.push_back(vert);

        //top right
        vert.Position.x = rightX;
        vert.Position.y = topY;
        vertices.push_back(vert);

        //top left
        vert.Position.x = leftX;
        vert.Position.y = topY;
        vertices.push_back(vert);

        //setthe indices for the rectangle's vertices. We have 6 since we are drawing in triangles.
        indices.push_back(indice);
        indices.push_back(indice + 1);
        indices.push_back(indice + 2);
        indices.push_back(indice);
        indices.push_back(indice + 2);
        indices.push_back(indice + 3);

        indice += 4;
    }

    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

    clearBuffer();

    // draw our first triangle
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window.getWindow());
    glfwPollEvents();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    vertices.clear();
    indices.clear();
}

void Graphics::clearBuffer() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Graphics::close() {
    return (window.close());
}

void Graphics::postProcess() {
    glfwSwapBuffers(window.getWindow());
    glfwPollEvents();
}

Graphics::~Graphics() {
    glDeleteProgram(shaderProgram);
}