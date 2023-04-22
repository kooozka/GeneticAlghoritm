#pragma once
#include<iostream>
#include <vector>
#include <random>
#include "KnapsackProblem.h"

using namespace std;

class Individual
{
public:
	Individual(vector<int> genotype, Problem *problem);
	//~Individual() {};
	int getFitness();
	void mutate(int i);
	void cross(Individual &secondParent, int crossIndex);
	vector<int> getGenotype();
	void setGenotype(vector<int> genotype);

private:
	vector<int> genotype;
	//mt19937 engine;
	bool calculated;
	int fitness;
	Problem* problem;
};

