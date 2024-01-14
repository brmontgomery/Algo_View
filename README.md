Algo_View by Brian Montgomery

This is a visualizer for sorting algorithms. The project was inspired by my want test out some libraries (including OpenGL and ImGui) and review sorting algorithms in a more interesting way than just reading about them online.

The project has dependencies of GLFW, GLAD and its included KHR file, ImGui, and GLM. 

In its current form, you must use the visual studio .sln and .prj files to run the program. Inclue and Library paths should be correct out of the box as they are relative to the solution directory.

Currently there are 2 available sorting algorithms to run:
1. Selection Sort
2. Bubble Sort

You can choose the size of the array that is being sorted through the ImGui menu as well as whether or not you want to see the visualizer or just the results of the sort.
The program currently tracks the number of Memory Accesses the algorithm makes, the number of Comparisons the algorithm makes, and the number of Swaps the algorithm makes during its run. These are shown in real time during the sort, as well as printed to console after the run is complete.
