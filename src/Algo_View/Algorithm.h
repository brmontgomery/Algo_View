#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

#include "Graphics.h"
#include "ImGuiImpl.h"
#include "AlgorithmStats.h"



void swapValues(int index1, int index2, std::vector<int>& numList, AlgorithmStats& stats, bool render) {
	Graphics* graphics = Graphics::getInstance(); 
	std::swap(numList[index1], numList[index2]);
	//converting to unsigned here as I have read that vectors use ints as iterators, thus you could get wierd interaction with the vector using unsigned ints as iterators.
	if (render) {
		graphics->render(numList, index1, index2, stats);
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}

/*Selction sort:

*/
void selectionSort(std::vector<int>& numList, AlgorithmStats& stats, bool render) {
	Graphics* graphics = Graphics::getInstance(); 
	int least = -1;
											stats.addAccess(1);
	for (int i = 0; i < numList.size(); i++) {
											stats.addComparison(3);
		for (int j = i; j < numList.size(); j++) {
			//best place to seethat weneed to exit the algo
			if (graphics->close()) {
				return;
			}
											stats.addComparison(3);
											stats.addComparison(1);
			if (least == -1) {
											stats.addAccess(1);
				least = j;
			}
			else if (numList[j] < numList[least]) {
											stats.addComparison(4); 
											stats.addAccess(1);
				least = j;
			}
			else {
				//for the above else if on the chance it is not true
											stats.addComparison(4);
			}
		}
											stats.addComparison(4);
											stats.addComparison(2);
		if (i != least) {
											stats.addSwap();
			swapValues(i, least, numList, stats, render);
		}
											
											stats.addAccess(1);
		least = -1;
	}
											stats.addComparison(3);
}

/*Bubble sort:

*/
void bubbleSort(std::vector<int>& numList, AlgorithmStats& stats, bool render) {
	Graphics* graphics = Graphics::getInstance(); 
	bool change = false;
											stats.addAccess(1);
											
	for (int i = 0; i < numList.size(); i++) {
											stats.addComparison(3);
		change = false;
											stats.addAccess(1);
		for (int j = 0; j < (numList.size() - i - 1); j++) {
											stats.addComparison(4);
			if (numList[j] > numList[j + 1]) {
				//best place to seethat weneed to exit the algo
				if (graphics->close()) {
					return;
				}
											stats.addSwap();
				swapValues(j, j + 1, numList, stats, render);
				change = true;
											stats.addAccess(1);
			}
		}
											stats.addComparison(4);
											stats.addComparison(1);
		if (change = false) {
			break;
		}
	}
											stats.addComparison(3);
}
#endif