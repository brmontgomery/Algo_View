#include <iostream>
#include <vector>
#include <random>

#include <GLFW/glfw3.h>

int main()
{
    //For the Article: steps to set up random list 1. Add <random> 2. create the range using a vector 3. Populate the vector 4. Shuffle the vector
    //get a random list of numbers between rangeBegin and rangeEnd
    //set the begin and end values
    const int rangeBegin = 0;
    const int rangeEnd = 1000;

    //set the size of the number list
    std::vector<int> randomNumberList(rangeEnd-rangeBegin);

    //generate the data by iterating over the number lists and inserting the numbers in order
    std::generate(randomNumberList.begin(), randomNumberList.end(), [number = rangeBegin]() mutable {return number++;});
    //shuffle the numbers after they have been added
    std::shuffle(randomNumberList.begin(), randomNumberList.end(), std::mt19937{std::random_device{}()});

    //For the Article: steps to setup OpenGL 1. 
    std::cout << "Hello!" << std::endl;
    return 0;
}