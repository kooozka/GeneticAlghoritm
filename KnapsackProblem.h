#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Problem.h"

using namespace std;

#define NO_ERROR 0
#define NEGATIVE_NUMBER_OF_ITEMS 1
#define WRONG_VALUES_VECTOR_SIZE 2
#define WRONG_SIZES_VECTOR_SIZE 3
#define NEGATIVE_MAX_SIZE 4

class KnapsackProblem : public Problem
{
public:
	KnapsackProblem(int numberOfItems, vector<int> sizes, vector<int> values, int maxSize, int &errorCode);
	KnapsackProblem();
	~KnapsackProblem();
	
	int calculateFitness(vector<int> genotype);
	int getNumberOfItems();
	bool loadFile(string fileName);

private:
	int numberOfItems;
	vector<int> sizes;
	vector<int> values;
	int maxSize;

	int calculateSize(vector<int> genotype);
};

