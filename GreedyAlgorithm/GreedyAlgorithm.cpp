#include <iostream>

#include "RD_INSTANCE.h"
#include "CHECK_CONS.h"
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
	int *weights = &num; // array of weights
	int *capacities = &num; // array of knapsack capacities
	int *setups = &num; // array of setup
	int *classes = &num; // array of classes
	int *indexes = &num; // array of indexes

	// read file
	int status = readInstance(istance_name, n, m, r, weights, capacities, profits, classes, indexes, setups, b);
	if (status) {
		std::cout << "File not read correctly or wrong format" << std::endl;
		return -3;
	}

	std::cout << "Instance value:" << std::endl;
	printInstance(n, m, r, weights, capacities, profits, classes, indexes, setups, b);

	// it is a double because in this way I can recycle the code CHECK_CONS without change any code
	double *f = (double *)malloc(sizeof(double) * (n * m + m * r)); // fj vector
	
	int *profitsKnapsackTemp = (int *)malloc(sizeof(int) * n);
	int *profitsItemTemp = (int *)malloc(sizeof(int) * n);
	int *profitsTemp = (int *)malloc(sizeof(int) * n);
	int *weightsTemp = (int *)malloc(sizeof(int) * n);
	int *bTemp = (int *)malloc(sizeof(int) * r);
	int *capacitiesTemp = (int *)malloc(sizeof(int) * m);

	// for all sorts entered in input
	for (int i = 0; i < argc - 2; i++) {

		if (q[i] == 1)
			decreasingAttribute1(profits, profitsTemp, profitsKnapsackTemp, profitsItemTemp, weights, weightsTemp, n, m);
		else if (q[i] == 2)
			decreasingAttribute2(profits, profitsTemp, profitsKnapsackTemp, profitsItemTemp, weights, weightsTemp, n, m);
		else if (q[i] == 3)
			decreasingAttribute3(profits, profitsTemp, profitsKnapsackTemp, profitsItemTemp, weights, weightsTemp, setups, classes, indexes, n, m, r);
		else if (q[i] == 4)
			decreasingAttribute4(profits, profitsTemp, profitsKnapsackTemp, profitsItemTemp, weights, weightsTemp, n, m);
		else {
			std::cout << "Q is not valid!\n";
			return -2;
		}

		// reset fj vector
		for (int j = 0; j < n*m + m * r; j++)
			f[j] = 0;

		copyArray(b, bTemp, r);
		copyArray(capacities, capacitiesTemp, m);
		
		// greedy algorithm
		int result = solve(n, m, r, weightsTemp, capacitiesTemp, profitsTemp, profitsKnapsackTemp, profitsItemTemp, classes, indexes, setups, bTemp, f);

		if (q[i] == 1)
			std::cout << "Q=1: ";
		else if (q[i] == 2)
			std::cout << "Q=2: ";
		else if (q[i] == 3)
			std::cout << "Q=3: ";
		else
			std::cout << "Q=4: ";
		std::cout << "Result is " << result << std::endl;

		status = checkSolution(f, result, n, m, r, b, weights, profits, capacities, setups, classes, indexes);

		if (status == 0) {
			std::cout << "All constraints are ok" << std::endl;
		}
		else if (status == 1) {
			std::cout << "Constraint violated: weights of the items are greater than the capacity..." << std::endl;
		}
		else if (status == 2) {
			std::cout << "Constraint violated: item is assigned to more than one knapsack..." << std::endl;
		}
		else if (status == 3) {
			std::cout << "Constraint violated: class is assigned to more than one knapsack..." << std::endl;
		}
		else if (status == 4) {
			std::cout << "Constraint violated: items of class are not assigned to knapsack..." << std::endl;
		}
		else if (status == 5) {
			std::cout << "Optimal solution violeted..." << std::endl;
		}
	} // for

	// free memory
	free(b);
	free(profits);
	free(weights);
	free(capacities);
	free(setups);
	free(classes);
	free(indexes);
	free(q);
	free(f);
	free(profitsKnapsackTemp);
	free(profitsItemTemp);
	free(profitsTemp);
	free(weightsTemp);
	free(bTemp);
	free(capacitiesTemp);

	return 0;
}