#include "UTILITY.h"

int findClass(int item, int classes[], int indexes[], int r) {

	int class1 = 0;

	for (int k = 0; k < r; k++) {
		int indexes_prev = k > 0 ? indexes[k - 1] : 0;
		for (int z = 0; z < indexes[k] - indexes_prev; z++) {

			if (classes[z + indexes_prev] == item)
				class1 = k;
		}
	} // k (items)

	return class1;
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

void copyArray(int oldArray[], int newArray[], int size) {

	for (int i = 0; i < size; i++)
		newArray[i] = oldArray[i];

}