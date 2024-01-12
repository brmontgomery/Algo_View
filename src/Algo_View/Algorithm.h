#pragma once
#include <vector>
#include <chrono>
#include <thread>

#include "Graphics.h"

void swapValues(int index1, int index2, std::vector<int>& numList, Graphics& graphics) {
	std::swap(numList[index1], numList[index2]);
	//converting to unsigned here as I have read that vectors use ints as iterators, thus you could get wierd interaction with the vector using unsigned ints as iterators.
	graphics.render(numList, index1, index2);
	std::this_thread::sleep_for(std::chrono::microseconds(50));
}

void selectionSort(Graphics graphics, std::vector<int>& numList) {
	int least = -1;
	for (int i = 0; i < numList.size(); i++) {
		for (int j = i; j < numList.size(); j++) {
			if (least == -1) {
				least = j;
			}
			else if (numList[j] < numList[least]) {
				least = j;
			}
		}
		if (i != least) {
			swapValues(i, least, numList, graphics);
		}
		least = -1;
	}
}