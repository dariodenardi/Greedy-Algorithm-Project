#include <iostream>

#include "RD_INSTANCE.h"
#include "SORT.h"
#include "GREEDY.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc != 3) {
		std::cout << "invalid parameters!\n";
		std::cout << "parameters: [nameIstance] [Q]\n";
		return -1;
	}

	// input parameters
	int q = strtol(argv[2], NULL, 10);
	char *istance_name = argv[1];

	std::cout << "Parameters: " << std::endl;
	std::cout << "instance name: " << istance_name << std::endl;
	std::cout << "order type: " << q << std::endl;

	int num = 25;
	bool num2 = false;

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
	
	bool *f = &num2;

	// read file
	int status = readInstance(istance_name, n, m, r, weights, capacities, profits, profitsKnapsack, profitsItem, classes, indexes, setups, b);
	if (status) {
		std::cout << "File not read correctly or wrong format" << std::endl;
		return -3;
	}

	printInstance(n, m, r, weights, capacities, profits, profitsKnapsack, profitsItem, classes, indexes, setups, b);

	if (q == 1)
		bubbleDecreasingSort(profits, profitsKnapsack, profitsItem, n * 2, weights);
	else if (q == 2)
		bubbleDecreasingSort(profits, profitsKnapsack, profitsItem, weights, n * 2);
	else if (q == 3)
		bubbleDecreasingSort(profits, profitsKnapsack, profitsItem, weights, setups, classes, indexes, m, n, r);
	else if (q == 4) {

	}
	else {
		std::cout << "Q is not valid!\n";
		return -2;
	}

	printInstance(n, m, r, weights, capacities, profits, profitsKnapsack, profitsItem, classes, indexes, setups, b);

	// greedy algorithm
	int result = solve(n, m, r, weights, capacities, profits, profitsKnapsack, profitsItem, classes, indexes, setups, b, f);
	std::cout << "Result is " << result << std::endl;

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
	free(f);

	return 0;
}