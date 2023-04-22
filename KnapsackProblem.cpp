#include "KnapsackProblem.h"

//Constructor
KnapsackProblem::KnapsackProblem(int numberOfItems, vector<int> sizes, vector<int> values, int maxSize, int& errorCode)
{
	if (numberOfItems < 0)
		errorCode = NEGATIVE_NUMBER_OF_ITEMS;
	else if (sizes.size() != numberOfItems)
		errorCode = WRONG_SIZES_VECTOR_SIZE;
	else if (values.size() != numberOfItems)
		errorCode = WRONG_VALUES_VECTOR_SIZE;
	else if (maxSize < 0)
		errorCode = NEGATIVE_MAX_SIZE;
	else {
		this->numberOfItems = numberOfItems;
		this->sizes = sizes;
		this->values = values;
		this->maxSize = maxSize;
	}
}

KnapsackProblem::KnapsackProblem()
{
	maxSize = 0;
	numberOfItems = 0;
}

KnapsackProblem::~KnapsackProblem()
{
}

//the most important method - calculating fitness
int KnapsackProblem::calculateFitness(vector<int> genotype)
{
	int fitness = 0;
	int size = calculateSize(genotype);

	if (size <= maxSize) {
		for (int i = 0; i < numberOfItems; i++)
			fitness += values.at(i) * genotype.at(i);
	}
	return fitness;
}

//method that helps calculate fitness
int KnapsackProblem::calculateSize(vector<int> genotype)
{
	int size = 0;
	for (int i = 0; i < numberOfItems; i++) {
		size += sizes.at(i) * genotype.at(i);
	}
	return size;
}

int KnapsackProblem::getNumberOfItems()
{
	return numberOfItems;
}


//long ugly method created in order to load some data from file
bool KnapsackProblem::loadFile(string fileName)
{
	ifstream file(fileName);
	try {
		if (!file.is_open())
			return false;
		string line;
		int readFromFile;
		getline(file, line);
		stringstream ss(line);
		ss >> readFromFile;
		if (readFromFile < 0)
			throw invalid_argument("Negative number of items");
		numberOfItems = readFromFile;
		//cout << numberOfItems << endl;;
		sizes.resize(numberOfItems);
		values.resize(numberOfItems);
		getline(file, line);
		ss = stringstream(line);
		for (int i = 0; i < numberOfItems; i++) {
			if (readFromFile < 0)
				throw invalid_argument("Negative size value");
			ss >> readFromFile;
			sizes[i] = readFromFile;
			//cout << sizes[i] << endl;
		}
		getline(file, line);
		ss = stringstream(line);
		for (int i = 0; i < numberOfItems; i++) {
			if (readFromFile < 0)
				throw invalid_argument("Negative value");
			ss >> readFromFile;
			values[i] = readFromFile;
			//cout << values[i] << endl;
		}
		getline(file, line);
		ss = stringstream(line);
		ss >> readFromFile;
		if (readFromFile < 0)
			throw invalid_argument("Negative backpackSize value");
		maxSize = readFromFile;
		//cout << maxSize;
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}
	file.close();
	return true;
}

