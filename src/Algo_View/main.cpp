#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <random>

#include "Graphics.h"

int main()
{
    

    //Graphics Init
    Window window;
    window.init("Algo_View");

    // render loop
    // -----------
    while (!window.close())
    {
        // preprocess for the loop
        // -----
        window.processInput();
        window.clearBuffer();

        // render
        // ------
        

        // loop postprocessing
        // -------------------------------------------------------------------------------
        window.postProcess();
    }

    return 0;
}