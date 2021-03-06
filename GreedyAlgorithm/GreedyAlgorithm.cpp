#include <iostream>

#include <time.h>

#include "INSTANCE.h"
#include "CHECK_CONS.h"
#include "SORT.h"
#include "GREEDY.h"
#include "POST_PROC.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc < 3) {
		std::cout << "invalid parameters!\n";
		std::cout << "parameters: [nameInstance] [Q]\n";
		return -1;
	}

	// input parameters
	char *instance_name = argv[1];
	int * q = (int *)malloc(sizeof(int) * (argc - 2));

	for (int i = 0; i < argc - 2; i++)
		q[i] = strtol(argv[i + 2], NULL, 10);

	std::cout << "Input parameters: " << std::endl;
	std::cout << "instance name: " << instance_name << std::endl;
	for (int i = 0; i < argc - 2; i++)
		std::cout << "q=" << q[i] << std::endl;
	std::cout << std::endl;

	// data for GMKP instance
	int n; // number of objects
	int m; // number of knapsacks
	int r; // number of subsets
	int *b = NULL; // item can be assign at most to bk knapsacks
	int *profits = NULL; // array for linear profit term
	int *weights = NULL; // array of weights
	int *capacities = NULL; // array of knapsack capacities
	int *setups = NULL; // array of setup
	int *classes = NULL; // array of classes
	int *indexes = NULL; // array of indexes

	clock_t start, end;
	double time;

	// read file
	int status = readInstance(instance_name, n, m, r, weights, capacities, profits, classes, indexes, setups, b);
	if (status) {
		std::cout << "File not found or not read correctly" << std::endl;
		return -3;
	}

	printInstance(n, m, r, weights, capacities, profits, classes, indexes, setups, b);

	// I could use a bool type but it is a double because in this way I can recycle CHECK_CONS without change any code
	double *f = (double *)malloc(sizeof(double) * (n * m + m * r)); // array of unassigned/assigned items/setups
	
	// temporary array
	int *itemKnapsackTemp = (int *)malloc(sizeof(int) * n); // it says what is the knapsack of first, second...n item
	int *itemIndexTemp = (int *)malloc(sizeof(int) * n); // it says which item is first, second...n
	int *profitsTemp = (int *)malloc(sizeof(int) * n); // it says what is the profit of the first, second...n item
	int *weightsTemp = (int *)malloc(sizeof(int) * n); // it says what is the weight of the first, second...n item
	int *bTemp = (int *)malloc(sizeof(int) * r);
	int *capacitiesTemp = (int *)malloc(sizeof(int) * m);

	// for all sorts entered in input
	for (int i = 0; i < argc - 2; i++) {

		if (q[i] == 1)
			std::cout << "Q=1:" << std::endl;
		else if (q[i] == 2)
			std::cout << "Q=2:" << std::endl;
		else if (q[i] == 3)
			std::cout << "Q=3:" << std::endl;
		else if (q[i] == 4)
			std::cout << "Q=4:" << std::endl;
		else if (q[i] == 5)
			std::cout << "Q=5:" << std::endl;
		else if (q[i] == 6)
			std::cout << "Q=6:" << std::endl;
		else {
			std::cout << "Q is not valid!\n";
			return -2;
		}

		if (q[i] == 1)
			decreasingAttribute1(profits, profitsTemp, itemKnapsackTemp, itemIndexTemp, weights, weightsTemp, n, m);
		else if (q[i] == 2)
			decreasingAttribute2(profits, profitsTemp, itemKnapsackTemp, itemIndexTemp, weights, weightsTemp, n, m);
		else if (q[i] == 3)
			decreasingAttribute3(profits, profitsTemp, itemKnapsackTemp, itemIndexTemp, weights, weightsTemp, setups, classes, indexes, n, m, r);
		else if (q[i] == 4)
			decreasingAttribute4(profits, profitsTemp, itemKnapsackTemp, itemIndexTemp, weights, weightsTemp, n, m);
		else if (q[i] == 5)
			decreasingAttribute5(profits, profitsTemp, itemKnapsackTemp, itemIndexTemp, weights, weightsTemp, setups, classes, indexes, n, m, r);
		else
			decreasingAttribute6(profits, profitsTemp, itemKnapsackTemp, itemIndexTemp, weights, weightsTemp, setups, classes, indexes, n, m, r);

		printInstance(n, m, r, weightsTemp, NULL, profitsTemp, itemKnapsackTemp, itemIndexTemp, classes, indexes, NULL, NULL);

		// reset f array
		for (int j = 0; j < n*m + m * r; j++)
			f[j] = 0;

		// reset b and capacities arrays
		copyArray(b, bTemp, r);
		copyArray(capacities, capacitiesTemp, m);
		
		start = clock();

		// greedy algorithm
		int result = solve(n, m, r, weightsTemp, capacitiesTemp, profitsTemp, itemKnapsackTemp, itemIndexTemp, classes, indexes, setups, bTemp, f);

		std::cout << "Greedy algorithm: result is " << result << std::endl;

		status = checkSolution(f, result, n, m, r, b, weights, profits, capacities, setups, classes, indexes);
		
		if (status == 0) {
			std::cout << "Greedy algorithm: all constraints are ok" << std::endl;
		}
		else if (status == 1) {
			std::cout << "Greedy algorithm: constraint violated: weights of the items are greater than the capacity..." << std::endl;
		}
		else if (status == 2) {
			std::cout << "Greedy algorithm: constraint violated: item is assigned to more than one knapsack..." << std::endl;
		}
		else if (status == 3) {
			std::cout << "Greedy algorithm: constraint violated: class is assigned to more than one knapsack..." << std::endl;
		}
		else if (status == 4) {
			std::cout << "Greedy algorithm: constraint violated: items of class are not assigned to knapsack..." << std::endl;
		}
		else if (status == 5) {
			std::cout << "Greedy algorithm: optimal solution violeted..." << std::endl;
		}

		//printInstance(n, m, r, weightsTemp, capacitiesTemp, profitsTemp, profitsKnapsackTemp, profitsItemTemp, classes, indexes, NULL, NULL);

		// post-precessing
		result = solve(result, n, m, r, weights, capacitiesTemp, profits, itemIndexTemp, classes, indexes, setups, bTemp, f);

		std::cout << "Post-precessing: result is " << result << std::endl;

		status = checkSolution(f, result, n, m, r, b, weights, profits, capacities, setups, classes, indexes);

		if (status == 0) {
			std::cout << "Post-precessing: all constraints are ok" << std::endl;
		}
		else if (status == 1) {
			std::cout << "Post-precessing: constraint violated: weights of the items are greater than the capacity..." << std::endl;
		}
		else if (status == 2) {
			std::cout << "Post-precessing: constraint violated: item is assigned to more than one knapsack..." << std::endl;
		}
		else if (status == 3) {
			std::cout << "Post-precessing: constraint violated: class is assigned to more than one knapsack..." << std::endl;
		}
		else if (status == 4) {
			std::cout << "Post-precessing: constraint violated: items of class are not assigned to knapsack..." << std::endl;
		}
		else if (status == 5) {
			std::cout << "Post-precessing: optimal solution violeted..." << std::endl;
		}

		end = clock();
		time = ((double)(end - start)) / CLOCKS_PER_SEC;

		if (status == 0)
			std::cout << "Elapsed time: " << time << std::endl;
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
	free(itemKnapsackTemp);
	free(itemIndexTemp);
	free(profitsTemp);
	free(weightsTemp);
	free(bTemp);
	free(capacitiesTemp);

	return 0;
}