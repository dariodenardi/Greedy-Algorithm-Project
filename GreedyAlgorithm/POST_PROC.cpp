#include "POST_PROC.h"

int minimumWeight(int i, int n, int profitsItem[], int weights[], double f[]);
int convertFijIndex(int i, int n, int profitsItem[], int item);
bool isItemAlreadyAssigned(int n, int m, int j, double f[]);

/*
Given the feasible solution found,
w := minimum weight of an unassigned item
for each knapsack i do
	if (residual capacity of knapsack i) < w then continue
	for each item j (in the order provided by the current a_j sorting) do
	  if item j is unassigned and it can be feasibly assigned to knapsack i then
		 assign item j to knapsack i and update the current solution
	end do
end do
*/
int solve(int result, int n, int m, int r, int weights[], int capacities[], int profits[], int profitsKnapsack[], int profitsItem[], int classes[], int indexes[], int setups[], int b[], double f[]) {

	int new_result = result;

	for (int i = 0; i < m; i++) {

		// find minimum weight of an unassigned item
		int weight_marked = minimumWeight(i, n, profitsItem, weights, f);

		if (capacities[i] < weight_marked)
			continue;

		for (int j = 0; j < n; j++) {

			// check if fij is not present
			if (f[j + i * n] == 0) {

				// find index in the profits arrays because there is a mismatch between fij array and profits arrays
				int index1 = convertFijIndex(i, n, profitsItem, j);

				// if item is already present
				bool itemIsPresent = isItemAlreadyAssigned(n, m, profitsItem[index1], f);

				if (!itemIsPresent) {

					// find class of the item that we want add
					int class1 = findClass(profitsItem[index1], classes, indexes, r);

					// if setup is already present in knapsack
					bool setupIsPresent = isClassAlreadyPresentInKnapsack(n, m, f, profitsKnapsack[index1], class1, classes, indexes, r);

					if (setupIsPresent) {

						if (capacities[profitsKnapsack[index1]] - weights[index1] > 0) {

							capacities[profitsKnapsack[index1]] = capacities[profitsKnapsack[index1]] - weights[index1];

							new_result += profits[index1];
							// item assigned
							f[profitsItem[index1] + profitsKnapsack[index1] * n] = 1;
						}
					}
					else {
						// check if in b vector there is a free slot
						if (b[class1] > 0) {

							if (capacities[profitsKnapsack[index1]] - weights[index1] - setups[class1] > 0) {

								capacities[profitsKnapsack[index1]] = capacities[profitsKnapsack[index1]] - weights[index1] - setups[class1];
								b[class1] -= 1;

								new_result += profits[index1];
								// item assigned
								f[profitsItem[index1] + profitsKnapsack[index1] * n] = 1;
								// setup assign
								f[n*m + profitsKnapsack[index1] * r + class1] = 1;
							}

						}
					} // if setupIsPresent

				} // itemIsPresent

			} // if fij

		} // j (items)
	} // i (knapsack)

	return new_result;
}

int minimumWeight(int i, int n, int profitsItem[], int weights[], double f[]) {

	int weight = INT_MAX;

	for (int j = 0; j < n; j++) {

		if (f[j + i * n] == 0) {

			int index = convertFijIndex(i, n, profitsItem, j);
			
			if (weights[index] < weight)
				weight = weights[index];
		} // fij

	} // j (items)

	return weight;
}

int convertFijIndex(int i, int n, int profitsItem[], int item) {

	for (int j = 0; j < n; j++)
		if (profitsItem[j + i * n] == item)
			return j + i * n;

}

bool isItemAlreadyAssigned(int n, int m, int j, double f[]) {

	for (int i = 0; i < m; i++) {
		if (f[j + i * n] == 1)
			return true;
	}

	return false;
}