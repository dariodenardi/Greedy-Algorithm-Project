#include "GREEDY.h"

bool isClassAlreadyPresentInKnapsack(int n, bool f[], int knapsack, int profitsKnapsack[], int profitsItem[], int setupItem, int classes[], int indexes[], int r);
bool isItemAlreadyAssigned(int n, bool f[], int item, int profitsItem[]);

int solve(int n, int m, int r, int * weights, int * capacities, int * profits, int * profitsKnapsack, int * profitsItem, int * classes, int * indexes, int * setups, int * b, bool * &f) {

	int result = 0;
	
	// fj vector
	f = (bool *)malloc(sizeof(bool) * n * m);
	for (int j = 0; j < n*m; j++)
		f[j] = 0;

	for (int j = 0; j < n*m; j++) {

		// if item is already present
		bool itemIsPresent = isItemAlreadyAssigned(j, f, profitsItem[j], profitsItem);

		if (!itemIsPresent) {

			// find class of the item that we want add
			int setup = findClass(profitsItem[j], classes, indexes, r);

			// if setup is already present in knapsack
			bool setupIsPresent = isClassAlreadyPresentInKnapsack(j, f, profitsKnapsack[j], profitsKnapsack, profitsItem, setup, classes, indexes, r);

			if (setupIsPresent) {

				if (capacities[profitsKnapsack[j]] - weights[j] > 0) {

					capacities[profitsKnapsack[j]] = capacities[profitsKnapsack[j]] - weights[j];

					result += profits[j];
					// item assigned
					f[j] = 1;
				}
			}
			else {
				// check if in b vector there is a free slot
				if (b[setup] > 0) {

					if (capacities[profitsKnapsack[j]] - weights[j] - setups[setup] > 0) {

						capacities[profitsKnapsack[j]] = capacities[profitsKnapsack[j]] - weights[j] - setups[setup];
						b[setup] -= 1;

						result += profits[j];
						// item assigned
						f[j] = 1;
					}

				}
			} // if setupIsPresent

		} // if itemIsPresent

	} // all items

	return result;
}

bool isClassAlreadyPresentInKnapsack(int n, bool f[], int knapsack, int profitsKnapsack[], int profitsItem[], int setupItem, int classes[], int indexes[], int r) {

	for (int j = 0; j < n; j++) {
		// only if fj item is assigned
		if (f[j] == true && knapsack == profitsKnapsack[j]) {
			int setup = findClass(profitsItem[j], classes, indexes, r);
			if (setup == setupItem)
				return true;
		}
		
	}

	return false;
}

bool isItemAlreadyAssigned(int n, bool f[], int item, int profitsItem[]) {

	for (int j = 0; j < n; j++) {

		if (f[j] && item == profitsItem[j])
			return true;

	}

	return false;
}