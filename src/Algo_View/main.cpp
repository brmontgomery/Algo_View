#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

#include "Graphics.h"
#include "Algorithm.h"
#include "AlgorithmStats.h"

#include "ImGuiImpl.h"

void shuffle(std::vector<int>& numList, int rangeBegin, int rangeEnd) {
    //generate the data by iterating over the number lists and inserting the numbers in order
    std::generate(numList.begin(), numList.end(), [number = rangeBegin]() mutable {return number++; });
    //shuffle the numbers after they have been added
    std::shuffle(numList.begin(), numList.end(), std::mt19937{ std::random_device{}() });
}

int main()
{
    //get a random list of numbers between rangeBegin and rangeEnd
    //set the begin and end values
    const int rangeBegin = 0;
    int rangeEnd = 50;

    //Graphics Init
    Graphics* graphics = Graphics::getInstance();
    AlgorithmStats stats;

    ImGuiImpl* imGui = ImGuiImpl::getInstance();
    imGui->initImGui(graphics->getWindow());

    //ImGui variables
    int chosenAlgo = -1;
    bool render = true;
    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // render loop
    // -----------
    while (!graphics->close())
    {   
        //if we have not chosen an algorithm to visualize
        if (chosenAlgo == -1) {
            //get any input
            glfwPollEvents();

            graphics->clearBuffer();
            imGui->startMenu(graphics->getWindow(), chosenAlgo, render, rangeEnd);

            //switch to the second buffer
            glfwSwapBuffers(graphics->getWindow());
        }
        else {
            //we have chosen an algorithm
            //set the size of the number list
            std::vector<int> randomNumberList(rangeEnd - rangeBegin);

            //route to the correct algorithm
            //each switch statement does the following
            //1. Shuffles the number list
            //render's the first number list
            //runs the first sort
            //gives the results
            //gives the program time to show the results
            //clears the stats
            switch (chosenAlgo) {
            case 0:
                shuffle(randomNumberList, rangeBegin, rangeEnd);
                if (render) {
                    graphics->render(randomNumberList, -1, -1, stats);
                }
                selectionSort(randomNumberList, stats, render);
                stats.print();
                if (render && !graphics->close()) {
                    std::this_thread::sleep_for(std::chrono::seconds(10));
                }
                stats.clear();
                break;
            case 1:
                shuffle(randomNumberList, rangeBegin, rangeEnd);
                if (render) {
                    graphics->render(randomNumberList, -1, -1, stats);
                }
                bubbleSort(randomNumberList, stats, render);
                stats.print();
                if (render && !graphics->close()) {
                    std::this_thread::sleep_for(std::chrono::seconds(10));
                }
                stats.clear();
                break;
            default:
                break;
            }

            //returns to the menu
            chosenAlgo = -1;
        }
    }

    imGui->shutdown();

    return 0;
}