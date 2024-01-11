#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

#include "Graphics.h"

void swapValues(int index1,int index2, std::vector<int>& numList, Graphics& graphics) {
    std::swap(numList[index1], numList[index2]);
    graphics.render(numList);
    std::this_thread::sleep_for(std::chrono::microseconds(50));
}

int main()
{
    //get a random list of numbers between rangeBegin and rangeEnd
    //set the begin and end values
    const int rangeBegin = 0;
    const int rangeEnd = 1000;

    //set the size of the number list
    std::vector<int> randomNumberList(rangeEnd - rangeBegin);

    //generate the data by iterating over the number lists and inserting the numbers in order
    std::generate(randomNumberList.begin(), randomNumberList.end(), [number = rangeBegin]() mutable {return number++; });
    //shuffle the numbers after they have been added
    std::shuffle(randomNumberList.begin(), randomNumberList.end(), std::mt19937{ std::random_device{}() });

    //Graphics Init
    Graphics graphics;

    
    // render loop
    // -----------
    while (!graphics.close())
    {
        graphics.render(randomNumberList);
    }

    return 0;
}