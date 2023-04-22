#pragma once
#include <vector>

using namespace std;

class Problem
{
public:
	virtual ~Problem() {};
	virtual int calculateFitness(vector<int> genotype) = 0;
	virtual int getNumberOfItems() = 0;
};

