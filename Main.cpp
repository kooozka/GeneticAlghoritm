#include <iostream>
#include <random>
#include "GeneticAlgorithm.h"

using namespace std;
int main() {
	int values[8] = { 3, 4, 3, 2, 3, 1, 7, 6};
	int sizes[8] = { 2, 5, 8, 4, 1, 3, 5, 2};
	vector<int> values1 = {11, 21, 31, 33, 43, 53, 55, 65, 51, 31};
	vector<int> sizes1 = {1, 11, 21, 23, 33, 43, 45, 55, 21, 36};
	Timer timer;
	int i = 0;
	KnapsackProblem problem(10, sizes1, values1, 120, i);
	KnapsackProblem problem1;
	try{
	problem1.loadFile("file.txt");
	}
	catch (runtime_error& e) {
		cout << e.what();
	}
	int x = 0;
	GeneticAlgorithm algorithm(26, 0.6, 0.1, 1000, &problem, x);
	vector<int> result;
	timer.start();
	result = algorithm.runIteration();
	timer.stop();
	for (int i : result) {
		cout << i;
	}
	cout << "\n";
	return 0;
}