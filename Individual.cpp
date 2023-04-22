#include "Individual.h"

//Constructor
Individual::Individual(vector<int> genotype, Problem *problem)
{
	this->genotype = genotype;
	this->problem = problem;
	fitness = problem->calculateFitness(genotype);
	calculated = true;
}

//get fitness with the usage of our problem
int Individual::getFitness()
{
	if (!calculated) {
		fitness = problem->calculateFitness(genotype);
		calculated = true;
	}
	return fitness;
}

//simple method to mutate specific gene
void Individual::mutate(int i)
{
	genotype.at(i) = 1 - genotype.at(i);
}

//cross two individuals (change their genotypes for others)
void Individual::cross(Individual& secondParent, int crossIndex)
{
	vector<int> firstGenotype;
	vector<int> secondGenotype;

	for (int i = 0; i < crossIndex; i++) {
		firstGenotype.push_back(genotype.at(i));
		secondGenotype.push_back(secondParent.genotype.at(i));
	}

	for (int i = crossIndex; i < genotype.size(); i++) {
		firstGenotype.push_back(secondParent.genotype.at(i));
		secondGenotype.push_back(genotype.at(i));
	}

	this->setGenotype(firstGenotype);
	secondParent.setGenotype(secondGenotype);
}

vector<int> Individual::getGenotype()
{
	return genotype;
}

void Individual::setGenotype(vector<int> genotype)
{
	this->genotype = genotype;
}

