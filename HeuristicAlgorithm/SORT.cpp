#include "SORT.h"

void replace(int *a, int *b);

// attribute 1
void bubbleDecreasingSort(int profits[], int profitsKnapsack[], int profitsItem[], int n, int weights[]) {
	int i;
	int ordinato = 0;

	while (n > 1 && ordinato == 0) {
		ordinato = 1;
		for (i = 0; i < n - 1; i++) {

			if (profits[i] < profits[i + 1]) {

				replace(&profits[i], &profits[i + 1]);
				replace(&profitsKnapsack[i], &profitsKnapsack[i + 1]);
				replace(&profitsItem[i], &profitsItem[i + 1]);
				replace(&weights[i], &weights[i + 1]);
				ordinato = 0;

			}

		}
		n--;
	}
}

// attribute 2
void bubbleDecreasingSort(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int n) {
	int i;
	int ordinato = 0;

	while (n > 1 && ordinato == 0) {
		ordinato = 1;
		for (i = 0; i < n - 1; i++) {

			if (profits[i] / weights[i] < profits[i + 1] / weights[i + 1]) {

				replace(&profits[i], &profits[i + 1]);
				replace(&profitsKnapsack[i], &profitsKnapsack[i + 1]);
				replace(&profitsItem[i], &profitsItem[i + 1]);
				replace(&weights[i], &weights[i + 1]);
				ordinato = 0;

			}

		}
		n--;
	}
}

// attribute 3
void bubbleDecreasingSort(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int setups[], int classes[], int indexes[], int m, int n, int r) {
	int i;
	int ordinato = 0;

	while (n > 1 && ordinato == 0) {
		ordinato = 1;
		for (i = 0; i < n - 1; i++) {

			int setup1 = findClass(i, classes, indexes, r);
			int setup2 = findClass(i + 1, classes, indexes, r);
			if (profits[i] / ((weights[i] + setup1) / m) < profits[i + 1] / ((weights[i+ 1] + setup2) / m)) {

				replace(&profits[i], &profits[i + 1]);
				replace(&profitsKnapsack[i], &profitsKnapsack[i + 1]);
				replace(&profitsItem[i], &profitsItem[i + 1]);
				replace(&weights[i], &weights[i + 1]);
				ordinato = 0;

			}

		}
		n--;
	}
}

void replace(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}