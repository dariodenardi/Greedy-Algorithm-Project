#include "CHECK_CONS.h"

int checkSolution(double *x, double objval, int n, int m, int r, int * b, int * weights, int * profits, int * capacities, int * setups, int * classes, int * indexes) {

	//double objval_check = 0;
	int sum;
	// check constraint 1
	for (int i = 0; i < m; i++) {

		sum = 0;

		for (int j = 0; j < n; j++) {
			sum += x[i*n + j] * weights[j];
			//std::cout << "WEIGHT" << j + 1 << " " << x[i*n + j] << " " << weights[j] << std::endl;
			//objval_check += x[i*n + j] * profits[i*n + j];
		}

		for (int k = 0; k < r; k++) {
			sum += x[m*n + i * r + k] * setups[k];
			//std::cout << "SETUP" << k + 1 << " " << x[m*n + i * r + k] << " " << setups[k] << std::endl;
		}

		//std::cout << "SUM " << sum << std::endl;

		if (sum > capacities[i])
			return 1;
	}

	// constraint 2
	for (int j = 0; j < n; j++) {

		sum = 0;

		for (int i = 0; i < m; i++) {
			sum += x[i*n + j];
		}

		//std::cout << "ITEM" << j + 1 << " " << sum << " " << std::endl;

		if (sum > 1)
			return 2;
	}

	// check constraint 3
	for (int k = 0; k < r; k++)
	{
		sum = 0;

		for (int i = 0; i < m; i++)
		{
			sum += x[m*n + i * r + k];
		}

		//std::cout << "BIN" << k + 1 << " " << sum << std::endl;

		if (sum > b[k])
			return 3;
	}

	// check constraint 4
	for (int i = 0; i < m; i++) {
		for (int k = 0; k < r; k++) {

			sum = 0;

			for (int j = 0; j < n; j++) {

				int indexes_prev = k > 0 ? indexes[k - 1] : 0;
				for (int z = 0; z < indexes[k] - indexes_prev; z++) {

					if (classes[z + indexes_prev] == j) {
						sum += x[i * n + j];
					}
				}

			} // j (items)

			//std::cout << "CLASS " << x[m*n + i * r + k] << " ITEM " << sum << " " << std::endl;

			if (sum > 0 && x[m*n + i * r + k] == 0)
				return 4;

		} // k (classes)
	} // i (knapsacks)

	// check optimal value
	//std::cout << "RESULTS " << objval_check << " " << objval << std::endl;

	//if (objval_check != objval)
	//	return 5;

	// if solution is ok
	return 0;
}