#include "SORT.h"

void replace(int *a, int *b);

// attribute 1
void decreasingSort(int profits[], int profitsKnapsack[], int profitsItem[], int n, int weights[])
{
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		for (j = i + 1; j < n; j++) {

			if (profits[j] > profits[max_idx])
				max_idx = j;
		}

		// Swap the found maximum item
		// with the first item
		replace(&profits[max_idx], &profits[i]);
		replace(&profitsKnapsack[max_idx], &profitsKnapsack[i]);
		replace(&profitsItem[max_idx], &profitsItem[i]);
		replace(&weights[max_idx], &weights[i]);
	}
}

// attribute 2
void decreasingSort(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int n)
{
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		for (j = i + 1; j < n; j++) {
			double div1 = (double)profits[j] / weights[j];
			double div2 = (double)profits[max_idx] / weights[max_idx];
			if (div1 > div2)
				max_idx = j;
		}

		// Swap the found maximum item
		// with the first item
		replace(&profits[max_idx], &profits[i]);
		replace(&profitsKnapsack[max_idx], &profitsKnapsack[i]);
		replace(&profitsItem[max_idx], &profitsItem[i]);
		replace(&weights[max_idx], &weights[i]);
	}
}

// attribute 3
void decreasingSort(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int setups[], int classes[], int indexes[], int n, int m, int r)
{
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		for (j = i + 1; j < n; j++) {

			int class1 = findClass(profitsItem[j], classes, indexes, r);
			int class2 = findClass(profitsItem[max_idx], classes, indexes, r);

			double div1 = (double)profits[j] / ((double)(weights[j] + setups[class1]) / m);
			double div2 = (double)profits[max_idx] / ((double)(weights[max_idx] + setups[class2]) / m);
			if (div1 > div2)
				max_idx = j;
		}

		// Swap the found maximum item
		// with the first item
		replace(&profits[max_idx], &profits[i]);
		replace(&profitsKnapsack[max_idx], &profitsKnapsack[i]);
		replace(&profitsItem[max_idx], &profitsItem[i]);
		replace(&weights[max_idx], &weights[i]);
	}
}

// attribute 4
void decreasingSort(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int n, int r) {
	int i, k, j, max_idx, max_idx2;

	std::cout << "profit1" << "\t" << "profit2" << "\t" << "diff" << "\t" << "item" << std::endl;
	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		max_idx2 = i;
		for (j = i + 1; j < n; j++) {

			if (profits[j] > profits[max_idx]) {
				max_idx2 = max_idx;
				max_idx = j;
			} else if (profits[j] > profits[max_idx2]) {
				max_idx2 = j;
			}
			
		}
		
		std::cout << profits[max_idx] << "\t" << profits[max_idx2] << "\t" << profits[max_idx] - profits[max_idx2] << "\t" << profitsItem[max_idx] << "\t" << profitsKnapsack[max_idx] + 1 << "\t" << weights[max_idx] << std::endl;
		// Swap the found maximum item
		// with the first item
		replace(&profits[max_idx], &profits[i]);
		replace(&profitsKnapsack[max_idx], &profitsKnapsack[i]);
		replace(&profitsItem[max_idx], &profitsItem[i]);
		replace(&weights[max_idx], &weights[i]);
	}
}

void replace(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}