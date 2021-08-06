#include "GREEDY.h"

int solve(int n, int m, int r, int weights[], int capacities[], int profits[], int itemKnapsack[], int itemIndex[], int classes[], int indexes[], int setups[], int b[], double f[]) {

	int result = 0;

	for (int j = 0; j < n; j++) {

		// find class of the item that we want add
		int class1 = findClass(itemIndex[j], classes, indexes, r);

		// if setup is already present in knapsack
		bool setupIsPresent = isClassAlreadyPresentInKnapsack(n, f, itemKnapsack[j], class1, classes, indexes, r);

		if (setupIsPresent) {

			if (capacities[itemKnapsack[j]] - weights[j] > 0) {

				capacities[itemKnapsack[j]] = capacities[itemKnapsack[j]] - weights[j];

				result += profits[j];
				// item assigned
				f[itemIndex[j] + itemKnapsack[j] * n] = 1;
			}
		}
		else {
			// check if in b vector there is a free slot
			if (b[class1] > 0) {

				if (capacities[itemKnapsack[j]] - weights[j] - setups[class1] > 0) {

					capacities[itemKnapsack[j]] = capacities[itemKnapsack[j]] - weights[j] - setups[class1];
					b[class1] -= 1;

					result += profits[j];
					// item assigned
					f[itemIndex[j] + itemKnapsack[j] * n] = 1;
					// setup assign
					f[n*m + itemKnapsack[j] * r + class1] = 1;
				}

			}
		} // if setupIsPresent

	} // j (items)

	return result;
}