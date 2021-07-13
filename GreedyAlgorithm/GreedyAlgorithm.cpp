#include <iostream>

#include "RD_INSTANCE.h"
#include "SORT.h"
#include "GREEDY.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc < 3) {
		std::cout << "invalid parameters!\n";
		std::cout << "parameters: [nameIstance] [Q]\n";
		return -1;
	}

	// input parameters
	char *istance_name = argv[1];

	int * q = (int *)malloc(sizeof(int) * (argc - 2));
	for (int i = 0; i < argc - 2; i++)
		q[i] = strtol(argv[i + 2], NULL, 10);

	std::cout << "Parameters: " << std::endl;
	std::cout << "instance name: " << istance_name << std::endl;
	for (int i = 0; i < argc - 2; i++)
		std::cout << "order type: " << q[i] << std::endl;
	std::cout << std::endl;

	int num = 25;

	// data for GMKP instance
	int n; // number of objects
	int m; // number of knapsacks
	int r; // number of subsets
	int *b = &num; // item can be assign at most to bk knapsacks // num points to somewhere random
	int *profits = &num; // array for linear profit term
	int *profitsKnapsack = &num; // which knapsack is assigned to i-th profit
	int *profitsItem = &num; // which item is assigned to i-th profit
	int *weights = &num; // array of weights
	int *capacities = &num; // array of knapsack capacities
	int *setups = &num; // array of setup
	int *classes = &num; // array of classes
	int *indexes = &num; // array of indexes

	// read file
	int status = readInstance(istance_name, n, m, r, weights, capacities, profits, profitsKnapsack, profitsItem, classes, indexes, setups, b);
	if (status) {
		std::cout << "File not read correctly or wrong format" << std::endl;
		return -3;
	}

	printInstance(n, m, r, weights, capacities, profits, profitsKnapsack, profitsItem, classes, indexes, setups, b);

	bool *f = (bool *)malloc(sizeof(bool) * n * m); // fj vector

	int *bCopy = (int *)malloc(sizeof(int) * r);
	int *capacitiesCopy = (int *)malloc(sizeof(int) * m);

	// for all sorts
	for (int i = 0; i < argc - 2; i++) {

		if (q[i] == 1)
			decreasingSort(profits, profitsKnapsack, profitsItem, n * m, weights);
		else if (q[i] == 2)
			decreasingSort(profits, profitsKnapsack, profitsItem, weights, n * m);
		else if (q[i] == 3)
			decreasingSort(profits, profitsKnapsack, profitsItem, weights, setups, classes, indexes, n * m, m, r);
		else if (q[i] == 4)
			decreasingSort(profits, profitsKnapsack, profitsItem, weights, n * m, r);
		else {
			std::cout << "Q is not valid!\n";
			return -2;
		}

		//printInstance(n, m, r, weights, capacities, profits, profitsKnapsack, profitsItem, classes, indexes, setups, b);

		// reset fj vector
		for (int j = 0; j < n*m; j++)
			f[j] = 0;

		copyArray(b, bCopy, r);
		copyArray(capacities, capacitiesCopy, m);

		// greedy algorithm
		int result = solve(n, m, r, weights, capacitiesCopy, profits, profitsKnapsack, profitsItem, classes, indexes, setups, bCopy, f);

		if (q[i] == 1)
			std::cout << "Q=1: ";
		else if (q[i] == 2)
			std::cout << "Q=2: ";
		else if (q[i] == 3)
			std::cout << "Q=3: ";
		else
			std::cout << "Q=4: ";
		std::cout << "Result is " << result << std::endl;
	}

	// free memory
	free(b);
	free(profits);
	free(profitsKnapsack);
	free(profitsItem);
	free(weights);
	free(capacities);
	free(setups);
	free(classes);
	free(indexes);
	free(q);
	free(f);
	free(bCopy);
	free(capacitiesCopy);

	return 0;
}