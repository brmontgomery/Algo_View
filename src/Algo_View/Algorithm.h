#pragma once
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

#include "Graphics.h"

class AlgorithmDiags {
	//I'm not grading on time because I am aware that the visualization slows down the algorithm immensely, adversely affecting some algos over others
public:
	AlgorithmDiags() : numberOfAccesses(0), numberOfSwaps(0), numberOfComparisons(0) {}
	void addAccess(int numAccesses) { numberOfAccesses += numAccesses; };
	void addSwap() { numberOfSwaps += 1; numberOfAccesses += 2;};
	void addComparison(int numAccesses) { numberOfComparisons += 1; numberOfAccesses += numAccesses; };

	void print() {
		std::cout << std::endl << std::endl << "Number of Accesses: " << std::to_string(numberOfAccesses) << std::endl;
		std::cout << "Number of Comparisons: " << std::to_string(numberOfComparisons) << std::endl;
		std::cout << "Number of Swaps: " << std::to_string(numberOfSwaps) << std::endl;
	}

	void clear() { numberOfAccesses = 0; numberOfSwaps = 0; numberOfComparisons = 0;}
private:
	//number of times we access the numList for anything. I am not counting accesses of iterators at the moment
	int numberOfAccesses;
	//number of times we swap values in the numList
	int numberOfSwaps;
	//number of times we compare values
	int numberOfComparisons;
};

void swapValues(int index1, int index2, std::vector<int>& numList, Graphics& graphics, AlgorithmDiags& diags) {
	std::swap(numList[index1], numList[index2]);
	//converting to unsigned here as I have read that vectors use ints as iterators, thus you could get wierd interaction with the vector using unsigned ints as iterators.
	graphics.render(numList, index1, index2);
	std::this_thread::sleep_for(std::chrono::microseconds(50));
}

void selectionSort(Graphics graphics, std::vector<int>& numList, AlgorithmDiags& diags) {
	int least = -1;
											diags.addAccess(1);
	for (int i = 0; i < numList.size(); i++) {
											diags.addComparison(3);
		for (int j = i; j < numList.size(); j++) {
											diags.addComparison(3);
											diags.addComparison(1);
			if (least == -1) {
											diags.addAccess(1);
				least = j;
			}
			else if (numList[j] < numList[least]) {
											diags.addComparison(4); 
											diags.addAccess(1);
				least = j;
			}
			else {
				//for the above else if on the chance it is not true
											diags.addComparison(4);
			}
		}
											diags.addComparison(4);
											diags.addComparison(2);
		if (i != least) {
											diags.addSwap();
			swapValues(i, least, numList, graphics, diags);
		}
											
											diags.addAccess(1);
		least = -1;
	}
											diags.addComparison(3);
}

void BubbleSort(Graphics graphics, std::vector<int>& numList, AlgorithmDiags& diags) {
	bool change = false;
											diags.addAccess(1);
											
	for (int i = 0; i < numList.size(); i++) {
											diags.addComparison(3);
		change = false;
											diags.addAccess(1);
		for (int j = 0; j < (numList.size() - i - 1); j++) {
											diags.addComparison(4);
			if (numList[j] > numList[j + 1]) {
											diags.addSwap();
				swapValues(j, j + 1, numList, graphics, diags);
				change = true;
											diags.addAccess(1);
			}
		}
											diags.addComparison(4);
											diags.addComparison(1);
		if (change = false) {
			break;
		}
	}
											diags.addComparison(3);
}