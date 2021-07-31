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
		std::cout << "parameters: [nameIstance] [Q]\n";
		return -1;
	}

	// input parameters
	char *istance_name = argv[1];
	int * q = (int *)malloc(sizeof(int) * (argc - 2));

	for (int i = 0; i < argc - 2; i++)
		q[i] = strtol(argv[i + 2], NULL, 10);

	std::cout << "Input parameters: " << std::endl;
	std::cout << "instance name: " << istance_name << std::endl;
	for (int i = 0; i < argc - 2; i++)
		std::cout << "q=" << q[i] << std::endl;
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

	clock_t start, end;
	double time;

	// read file
	int status = readInstance(istance_name, n, m, r, weights, capacities, profits, classes, indexes, setups, b);
	if (status) {
		std::cout << "File not found or not read correctly" << std::endl;
		return -3;
	}

	printInstance(n, m, r, weights, capacities, profits, classes, indexes, setups, b);

	// it is a double because in this way I can recycle the code CHECK_CONS without change any code
	double *f = (double *)malloc(sizeof(double) * (n * m + m * r)); // fj vector
	
	int *profitsKnapsackBestValueTemp = (int *)malloc(sizeof(int) * n); // temporary vectors of order of the profits (knapsack) for the first part of the algorithm
	int *profitsItemBestValueTemp = (int *)malloc(sizeof(int) * n); // temporary vectors of order of the profits (item) for the first part of the algorithm
	int *profitsBestValueTemp = (int *)malloc(sizeof(int) * n); // temporary vectors of profits for the first part of the algorithm
	int *weightsBestValueTemp = (int *)malloc(sizeof(int) * n); // temporary vectors of weights for the first part of the algorithm
	int *profitsKnapsackTemp = (int *)malloc(sizeof(int) * (n*m)); // temporary vectors of order of the profits (knapsack) for the second part of the algorithm
	int *profitsItemTemp = (int *)malloc(sizeof(int) * (n*m));  // temporary vectors of order of the profits (item) for the second part of the algorithm
	int *profitsTemp = (int *)malloc(sizeof(int) * (n*m)); // temporary vectors of profits for the second part of the algorithm
	int *weightsTemp = (int *)malloc(sizeof(int) * (n*m)); // temporary vectors of weights for the second part of the algorithm
	int *bTemp = (int *)malloc(sizeof(int) * r); // temporary vector of b
	int *capacitiesTemp = (int *)malloc(sizeof(int) * m); // temporary vector of capacities

	// for all sorts entered in input
	for (int i = 0; i < argc - 2; i++) {

		if (q[i] == 1)
			std::cout << "Q=1" << std::endl;
		else if (q[i] == 2)
			std::cout << "Q=2" << std::endl;
		else if (q[i] == 3)
			std::cout << "Q=3" << std::endl;
		else
			std::cout << "Q=4" << std::endl;

		if (q[i] == 1)
			decreasingBestAttribute1(profits, profitsBestValueTemp, profitsKnapsackBestValueTemp, profitsItemBestValueTemp, weights, weightsBestValueTemp, n, m);
		else if (q[i] == 2)
			decreasingBestAttribute2(profits, profitsBestValueTemp, profitsKnapsackBestValueTemp, profitsItemBestValueTemp, weights, weightsBestValueTemp, n, m);
		else if (q[i] == 3)
			decreasingBestAttribute3(profits, profitsBestValueTemp, profitsKnapsackBestValueTemp, profitsItemBestValueTemp, weights, weightsBestValueTemp, setups, classes, indexes, n, m, r);
		else if (q[i] == 4)
			decreasingBestAttribute4(profits, profitsBestValueTemp, profitsKnapsackBestValueTemp, profitsItemBestValueTemp, weights, weightsBestValueTemp, n, m);
		else {
			std::cout << "Q is not valid!\n";
			return -2;
		}

		//printInstance(n, 1, r, weightsBestValueTemp, NULL, profitsBestValueTemp, profitsKnapsackBestValueTemp, profitsItemBestValueTemp, classes, indexes, NULL, NULL);

		// reset fj vector
		for (int j = 0; j < n*m + m * r; j++)
			f[j] = 0;

		// reset b vector e capacities vector
		copyArray(b, bTemp, r);
		copyArray(capacities, capacitiesTemp, m);
		
		start = clock();

		// greedy algorithm
		int result = solve(n, m, r, weightsBestValueTemp, capacitiesTemp, profitsBestValueTemp, profitsKnapsackBestValueTemp, profitsItemBestValueTemp, classes, indexes, setups, bTemp, f);

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

		// prepare array for post-processing
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				profitsItemTemp[j + i * n] = j;
				profitsKnapsackTemp[j + i * n] = i;
				weightsTemp[j + i * n] = weights[j];
			}
		}
		copyArray(profits, profitsTemp, n*m);

		if (q[i] == 1)
			decreasingAllAttribute1(profitsTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, n, m);
		else if (q[i] == 2)
			decreasingAllAttribute2(profitsTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, n, m);
		else if (q[i] == 3)
			decreasingAllAttribute3(profitsTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, setups, classes, indexes, n, m, r);
		//else if (q[i] == 4)
		//	decreasingAllAttribute4(profits, profitsTemp, profitsKnapsackTemp, profitsItemTemp, weights, weightsTemp, n, m);
		else {
			std::cout << "Q is not valid!\n";
			return -2;
		}

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << j + 1 << "\t" << (int)f[j + i * n] << std::endl;
			}
		}
		std::cout << std::endl;

		printInstance(n, m, r, weightsTemp, capacitiesTemp, profitsTemp, profitsKnapsackTemp, profitsItemTemp, classes, indexes, NULL, NULL);

		// post-precessing
		result = solve(result, n, m, r, weightsTemp, capacitiesTemp, profitsTemp, profitsKnapsackTemp, profitsItemTemp, classes, indexes, setups, bTemp, f);

		std::cout << "Post-precessing: result is " << result << std::endl;

		status = checkSolution(f, result, n, m, r, b, weights, profits, capacities, setups, classes, indexes);

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << j + 1 << "\t" << (int)f[j + i * n] << std::endl;
			}
		}
		std::cout << std::endl;

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
	free(profitsKnapsackBestValueTemp);
	free(profitsItemBestValueTemp);
	free(profitsBestValueTemp);
	free(weightsBestValueTemp);
	free(profitsKnapsackTemp);
	free(profitsItemTemp);
	free(profitsTemp);
	free(weightsTemp);
	free(bTemp);
	free(capacitiesTemp);

	return 0;
}