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
        graphics.render(randomNumberList, -1, -1);
        selectionSort(graphics, randomNumberList);
    }

    return 0;
}