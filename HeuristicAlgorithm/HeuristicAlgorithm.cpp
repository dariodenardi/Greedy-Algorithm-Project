#include <iostream>

#include "RD_INSTANCE.h"
#include "SORT.h"

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
	if (status)
		std::cout << "File not read correctly or wrong format" << std::endl;

	std::cout << n << std::endl;
	std::cout << m << std::endl;
	std::cout << r << std::endl;

	std::cout << "profits" << std::endl;
	for (int i = 0; i < n*m; i++) {

		std::cout << profits[i] << std::endl;

	}
	std::cout << "weights" << std::endl;
	for (int i = 0; i < n; i++) {

		std::cout << weights[i] << std::endl;

	}
	std::cout << "capacities" << std::endl;
	for (int i = 0; i < m; i++) {

		std::cout << capacities[i] << std::endl;

	}
	std::cout << "setups" << std::endl;
	for (int i = 0; i < m; i++) {

		std::cout << setups[i] << std::endl;

	}

	std::cout << "classes" << std::endl;
	for (int k = 0; k < r; k++) {

		for (int j = 0; j < n; j++) {

			int indexes_prev = k > 0 ? indexes[k - 1] : 0;
			for (int z = 0; z < indexes[k] - indexes_prev; z++) {

				if (classes[z + indexes_prev] == j) {
					std::cout << classes[z + indexes_prev] << std::endl;
				}
			}

		} // j (items)

		std::cout << std::endl;
	} // k (items)

	if (q == 1) {

	}
	else if (q == 2) {

	}
	else if (q == 3) {

	}
	else if (q == 4) {

	}
	else {
		std::cout << "Q is not valid!\n";
		return -2;
	}

	// free memory
	free(b);
	free(profits);
	free(weights);
	free(capacities);
	free(setups);
	free(classes);
	free(indexes);

	return 0;
}