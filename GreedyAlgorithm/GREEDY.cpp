#include "GREEDY.h"

bool isClassAlreadyPresentInKnapsack(int n, double f[], int knapsack, int profitsKnapsack[], int profitsItem[], int classItem, int classes[], int indexes[], int r);
bool isItemAlreadyAssigned(int n, double f[], int item, int profitsItem[]);

int solve(int n, int m, int r, int weights[], int capacities[], int profits[], int profitsKnapsack[], int profitsItem[], int classes[], int indexes[], int setups[], int b[], double f[]) {

	int result = 0;

	for (int j = 0; j < n*m; j++) {

		// if item is already present
		bool itemIsPresent = isItemAlreadyAssigned(j, f, profitsItem[j], profitsItem);

		if (!itemIsPresent) {

			// find class of the item that we want add
			int class1 = findClass(profitsItem[j], classes, indexes, r);

			// if setup is already present in knapsack
			bool setupIsPresent = isClassAlreadyPresentInKnapsack(j, f, profitsKnapsack[j], profitsKnapsack, profitsItem, class1, classes, indexes, r);

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
				if (b[class1] > 0) {

					if (capacities[profitsKnapsack[j]] - weights[j] - setups[class1] > 0) {

						capacities[profitsKnapsack[j]] = capacities[profitsKnapsack[j]] - weights[j] - setups[class1];
						b[class1] -= 1;

						result += profits[j];
						// item assigned
						f[j] = 1;
						// setup assign
						f[n*m + profitsKnapsack[j]*r + class1] = 1;
					}

				}
			} // if setupIsPresent

		} // if itemIsPresent

	} // all items

	return result;
}

bool isClassAlreadyPresentInKnapsack(int n, double f[], int knapsack, int profitsKnapsack[], int profitsItem[], int classItem, int classes[], int indexes[], int r) {

	for (int j = 0; j < n; j++) {
		// only if fj item is assigned
		if (f[j] == 1 && knapsack == profitsKnapsack[j]) {
			int class1 = findClass(profitsItem[j], classes, indexes, r);
			if (class1 == classItem)
				return true;
		}
		
	}

	return false;
}

bool isItemAlreadyAssigned(int n, double f[], int item, int profitsItem[]) {

	for (int j = 0; j < n; j++) {

		if (f[j] && item == profitsItem[j])
			return true;

	}

	return false;
}