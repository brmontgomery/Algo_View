#ifndef _ALGORITHMSTATS_H_
#define _ALGORITHMSTATS_H_

#include <iostream>
#include <string>

class AlgorithmStats {
	//I'm not grading on time because I am aware that the visualization slows down the algorithm immensely, adversely affecting some algos over others
public:
	AlgorithmStats() : numberOfAccesses(0), numberOfSwaps(0), numberOfComparisons(0) {}
	void addAccess(int numAccesses) { numberOfAccesses += numAccesses; };
	void addSwap() { numberOfSwaps += 1; numberOfAccesses += 2; };
	void addComparison(int numAccesses) { numberOfComparisons += 1; numberOfAccesses += numAccesses; };
	int getAccesses() { return numberOfAccesses; };
	int getSwaps() { return numberOfSwaps; };
	int getComparisons() { return numberOfComparisons; };

	void print() {
		std::cout << std::endl << std::endl << "Number of Accesses: " << std::to_string(numberOfAccesses) << std::endl;
		std::cout << "Number of Comparisons: " << std::to_string(numberOfComparisons) << std::endl;
		std::cout << "Number of Swaps: " << std::to_string(numberOfSwaps) << std::endl;
	}

	void clear() { numberOfAccesses = 0; numberOfSwaps = 0; numberOfComparisons = 0; }
private:
	//number of times we access the numList for anything. I am not counting accesses of iterators at the moment
	int numberOfAccesses;
	//number of times we swap values in the numList
	int numberOfSwaps;
	//number of times we compare values
	int numberOfComparisons;
};
#endif