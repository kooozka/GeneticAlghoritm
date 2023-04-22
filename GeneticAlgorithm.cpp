#include "GeneticAlgorithm.h"

//Constructor
GeneticAlgorithm::GeneticAlgorithm(int populationSize, double crossProbability, double mutationProbability, int numberOfIterations, Problem* problem, int &errorCode)
{
	if (populationSize < 0)
		errorCode = NEGATIVE_POPULATION_SIZE;
	else if (populationSize % 2 != 0) 
		this->populationSize = populationSize + 1;
	else 
		this->populationSize = populationSize;
	if (numberOfIterations < 0)
		errorCode = NEGATIVE_NUMBER_OF_ITERATIONS;
	else
		this->numberOfIterations = numberOfIterations;
	if (crossProbability < 0) 
		this->crossProbability = 0;
	else if (crossProbability > 1) 
		this->crossProbability = 1;
	else 
		this->crossProbability = crossProbability;
	if (mutationProbability < 0)
		this->mutationProbability = 0;
	else if (mutationProbability > 1)
		this->mutationProbability = 1;
	else
		this->mutationProbability = mutationProbability;
	this->problem = problem;
	newPopulation.reserve(populationSize);
	currentBestValue = -1;
	engine = mt19937(random_device{}());
}

//Destructor
GeneticAlgorithm::~GeneticAlgorithm()
{
	for (int i = 0; i < populationSize; i++) {
		delete population[i];
	}
	population.clear();
}

//The most important method - running iteration
vector<int> GeneticAlgorithm::runIteration()
{
	generateFirstPopulation();
	for (int i = 0; i < numberOfIterations; i++) {
		crossPopulation();
		deleteOldPopulation();
		population = newPopulation;
		newPopulation.clear();
		mutatePopulation();
		checkSolutions();
	}
	cout << currentBestValue << endl;
	return currentBestSolution;
} 

//method that generates first population
void GeneticAlgorithm::generateFirstPopulation()
{
	for (int i = 0; i < populationSize; i++) {
		population.push_back(new Individual(generateRandomGenotype(), problem));
	}
	checkSolutions();
}

//methods which are responsible for working on population
void GeneticAlgorithm::mutatePopulation() {
	for (int i = 0; i < population.size(); i++) {
		for (int j = 0; j < population.at(i)->getGenotype().size(); j++) {
			if (shouldMutate())
				population.at(i)->mutate(j);
		}
		population.at(i)->getFitness();
	}
}

void GeneticAlgorithm::crossPopulation()
{
	int numberOfGenes = problem->getNumberOfItems();
	uniform_int_distribution<int> distribution(1, numberOfGenes);
	for (int i = 0; i < (populationSize / 2); i++) {
		Individual* first = chooseParent();
		Individual* second = chooseParent();
		if (shouldCross()) {
			int crossIndex = distribution(engine);
			first->cross(*second, crossIndex);
		}
		newPopulation.push_back(first);
		newPopulation.push_back(second);
	}
}

Individual* GeneticAlgorithm::chooseParent()
{
	uniform_int_distribution<int> distribiution(0, populationSize - 1);
	Individual* firstCandidate = population.at(distribiution(engine));
	Individual* secondCandidate = population.at(distribiution(engine));
	if (firstCandidate->getFitness() > secondCandidate->getFitness())
		return new Individual(firstCandidate->getGenotype(), problem);
	else
		return new Individual(secondCandidate->getGenotype(), problem);
}

void GeneticAlgorithm::deleteOldPopulation()
{
	for (int i = 0; i < populationSize; i++)
		delete population[i];
}

//bool functions checking mutation/cross
bool GeneticAlgorithm::shouldMutate()
{	
	uniform_real_distribution<double> distribution(0, 1);
	if (distribution(engine) < mutationProbability) {
		return true;
	}
	return false;
}

bool GeneticAlgorithm::shouldCross()
{
	uniform_real_distribution<double> distribution(0, 1);
	if (distribution(engine) < crossProbability){
		return true;
	}
	return false;
}


void GeneticAlgorithm::checkSolutions()
{
	for (Individual* individual : population) {
		if (individual->getFitness() > currentBestValue) {
			currentBestSolution = individual->getGenotype();
			currentBestValue = individual->getFitness();
		}
	}
	//cout << currentBestValue << endl;
}

//generating random genotype for first Individuals' population
vector<int> GeneticAlgorithm::generateRandomGenotype()
{
	vector<int> genotype;
	uniform_int_distribution<int> distribution(0, 1);
	for (int i = 0; i < problem->getNumberOfItems(); i++) {
		genotype.push_back(distribution(engine));
	}
	return genotype;
}



