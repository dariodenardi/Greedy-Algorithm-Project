#include "GREEDY.h"

bool isClassAlreadyPresentInKnapsack(int n, int m, double f[], int knapsack, int classItem, int classes[], int indexes[], int r);

int solve(int n, int m, int r, int weights[], int capacities[], int profits[], int profitsKnapsack[], int profitsItem[], int classes[], int indexes[], int setups[], int b[], double f[]) {

	int result = 0;

	for (int j = 0; j < n; j++) {

		// find class of the item that we want add
		int class1 = findClass(profitsItem[j], classes, indexes, r);

		// if setup is already present in knapsack
		bool setupIsPresent = isClassAlreadyPresentInKnapsack(n, m, f, profitsKnapsack[j], class1, classes, indexes, r);

		if (setupIsPresent) {

			if (capacities[profitsKnapsack[j]] - weights[j] > 0) {

				capacities[profitsKnapsack[j]] = capacities[profitsKnapsack[j]] - weights[j];

				result += profits[j];
				// item assigned
				f[profitsItem[j] + profitsKnapsack[j] * n] = 1;
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
					f[profitsItem[j] + profitsKnapsack[j] * n] = 1;
					// setup assign
					f[n*m + profitsKnapsack[j] * r + class1] = 1;
				}

			}
		} // if setupIsPresent

	} // all items

	return result;
}

bool isClassAlreadyPresentInKnapsack(int n, int m, double f[], int knapsack, int classItem, int classes[], int indexes[], int r) {

	for (int j = 0; j < n; j++) {
		// only if fj item is assigned
		if (f[j + knapsack * n] == 1) {
			int class1 = findClass(j, classes, indexes, r);
			if (class1 == classItem)
				return true;
		}
		
	}

	return false;
}