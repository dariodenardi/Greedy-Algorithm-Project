#include "POST_PROC.h"

int minimumWeight(int i, int n, int weights[], double f[]);
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
int solve(int result, int n, int m, int r, int weights[], int capacitiesTemp[], int profits[], int profitsItemTemp[], int classes[], int indexes[], int setups[], int b[], double f[]) {

	int new_result = result;

	for (int i = 0; i < m; i++) {

		// find minimum weight of an unassigned item
		int weight_marked = minimumWeight(i, n, weights, f);

		if (capacitiesTemp[i] < weight_marked)
			continue;

		for (int j = 0; j < n; j++) {

			// check if fj is not present
			if (f[profitsItemTemp[j] + i * n] == 0) {

				// if item is already present
				bool itemIsPresent = isItemAlreadyAssigned(n, m, profitsItemTemp[j], f);
				
				if (!itemIsPresent) {

					// find class of the item that we want add
					int class1 = findClass(profitsItemTemp[j], classes, indexes, r);

					// if setup is already present in knapsack
					bool setupIsPresent = isClassAlreadyPresentInKnapsack(n, m, f, i, class1, classes, indexes, r);

					if (setupIsPresent) {

						if (capacitiesTemp[i] - weights[profitsItemTemp[j]] > 0) {

							capacitiesTemp[i] = capacitiesTemp[i] - weights[profitsItemTemp[j]];

							new_result += profits[profitsItemTemp[j] + i * n];
							// item assigned
							f[profitsItemTemp[j] + i * n] = 1;
						}
					}
					else {
						// check if in b vector there is a free slot
						if (b[class1] > 0) {

							if (capacitiesTemp[i] - weights[profitsItemTemp[j]] - setups[class1] > 0) {

								capacitiesTemp[i] = capacitiesTemp[i] - weights[profitsItemTemp[j]] - setups[class1];
								b[class1] -= 1;

								new_result += profits[profitsItemTemp[j] + i * n];
								// item assigned
								f[profitsItemTemp[j] + i * n] = 1;
								// setup assign
								f[n*m + i * r + class1] = 1;
							}

						}
					} // if setupIsPresent

				} // itemIsPresent

			} // if fj = 0

		} // j (items)
	} // i (knapsack)

	return new_result;
}

int minimumWeight(int i, int n, int weights[], double f[]) {

	int weight = INT_MAX;

	for (int j = 0; j < n; j++) {

		if (f[j + i * n] == 0) {
			
			if (weights[j] < weight)
				weight = weights[j];
		} // fj

	} // j (items)

	return weight;
}

bool isItemAlreadyAssigned(int n, int m, int j, double f[]) {

	for (int i = 0; i < m; i++) {
		if (f[j + i * n] == 1)
			return true;
	}

	return false;
}