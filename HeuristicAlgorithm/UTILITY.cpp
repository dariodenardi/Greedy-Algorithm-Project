#include "UTILITY.h"

int findClass(int item, int classes[], int indexes[], int r) {

	int setup = 0;

	for (int k = 0; k < r; k++) {
		int indexes_prev = k > 0 ? indexes[k - 1] : 0;
		for (int z = 0; z < indexes[k] - indexes_prev; z++) {

			if (classes[z + indexes_prev] == item)
				setup = k;
		}
	} // k (items)

	return setup;
}