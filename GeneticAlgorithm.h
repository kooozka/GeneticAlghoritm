#pragma once
#include <iostream>
#include <random>
#include "Individual.h"
#include "Timer.h"
#include "MySmartPointer.h"
using namespace std;

#define NO_ERROR 0
#define NEGATIVE_POPULATION_SIZE 1
#define NEGATIVE_NUMBER_OF_ITERATIONS 2

class GeneticAlgorithm
{
public:
	GeneticAlgorithm(int populationSize, double crossProbability, double mutationProbability, int numberOfIterations, Problem *problem, int &errorCode);
	~GeneticAlgorithm();
	vector<int> runIteration();

private:
	int populationSize;
	double crossProbability;
	double mutationProbability;
	int numberOfIterations;
	Problem *problem;
	mt19937 engine;
	int currentBestValue;
	vector<int> currentBestSolution;
	vector<Individual*> population;
	vector<Individual*> newPopulation;

	Individual* chooseParent();
	void generateFirstPopulation();
	void mutatePopulation();
	void crossPopulation();
	void deleteOldPopulation();
	void checkSolutions();
	vector<int> generateRandomGenotype();
	bool shouldCross();
	bool shouldMutate();
};

