#include "SORT.h"

void decreasingSort1(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int n);
void decreasingSort1(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int start, int end);
void decreasingSort2(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int n);
void decreasingSort2(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int start, int end);
void decreasingSort3(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int setups[], int classes[], int indexes[], int n, int m, int r);
void decreasingSort3(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int setups[], int classes[], int indexes[], int m, int r, int start, int end);
void decreasingSort4(int profits[], int differenceTemp[], int profitsKnapsack[], int profitsItem[], int weights[], int n);
void replace(int *a, int *b);
void replace(double *a, double *b);

// attribute 1
void decreasingBestAttribute1(int profits[], int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weights[], int weightsTemp[], int n, int m)
{
	int i, j, max_idx, max_value, max_knapsack;

	for (j = 0; j < n; j++) {

		// Find the maximum profits of the items in them knapsack
		max_idx = 0;
		max_value = 0;
		max_knapsack = 0;
		for (i = 0; i < m; i++) {

			if (profits[j + i * n] > max_value) {
				max_idx = j + i * n;
				max_value = profits[max_idx];
				max_knapsack = i;
			}
				
		}

		profitsTemp[j] = profits[max_idx];
		weightsTemp[j] = weights[j];
		profitsItemTemp[j] = j;
		profitsKnapsackTemp[j] = max_knapsack;
	} // items

	// order by decreasing value
	decreasingSort1(profitsTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, n);
}

void decreasingSort1(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int n) {
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

void decreasingAllAttribute1(int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weightsTemp[], int n, int m) {
	// order by knapsack
	for (int i = 0; i < m; i++) {
		decreasingSort1(profitsTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, i * n, n + i * n);
	}
}

void decreasingSort1(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int start, int end) {
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = start; i < end - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		for (j = i + 1; j < end; j++) {

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
void decreasingBestAttribute2(int profits[], int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weights[], int weightsTemp[], int n, int m)
{
	int i, j, max_idx, max_knapsack;
	double max_value;

	for (j = 0; j < n; j++) {

		// Find the maximum profits of the items in them knapsack
		max_idx = 0;
		max_value = 0;
		max_knapsack = 0;
		for (i = 0; i < m; i++) {

			double div1 = (double)profits[j + i * n] / weights[j];
			if (div1 > max_value) {
				max_idx = j + i * n;
				max_value = div1;
				max_knapsack = i;
			}

		}

		profitsTemp[j] = profits[max_idx];
		weightsTemp[j] = weights[j];
		profitsItemTemp[j] = j;
		profitsKnapsackTemp[j] = max_knapsack;
	} // items

	// order by decreasing value
	decreasingSort2(profitsTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, n);
}

void decreasingSort2(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int n) {
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

void decreasingAllAttribute2(int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weightsTemp[], int n, int m) {
	// order by knapsack
	for (int i = 0; i < m; i++) {
		decreasingSort2(profitsTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, i * n, n + i * n);
	}
}

void decreasingSort2(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int start, int end) {
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = start; i < end - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		for (j = i + 1; j < end; j++) {

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
void decreasingBestAttribute3(int profits[], int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weights[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int m, int r)
{
	int i, j, max_idx, max_knapsack;
	double max_value;

	for (j = 0; j < n; j++) {

		// Find the maximum profits of the items in them knapsack
		max_idx = 0;
		max_value = 0;
		max_knapsack = 0;
		for (i = 0; i < m; i++) {

			int class1 = findClass(j + i * n, classes, indexes, r);
			double div1 = (double)profits[j + i * n] / ((double)(weights[j] + setups[class1]) / m);

			if (div1 > max_value) {
				max_idx = j + i * n;
				max_value = div1;
				max_knapsack = i;
			}

		}

		profitsTemp[j] = profits[max_idx];
		weightsTemp[j] = weights[j];
		profitsItemTemp[j] = j;
		profitsKnapsackTemp[j] = max_knapsack;
	} // items

	// order by decreasing value
	decreasingSort3(profitsTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, setups, classes, indexes, n, m, r);
}

void decreasingSort3(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int setups[], int classes[], int indexes[], int n, int m, int r) {
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

void decreasingAllAttribute3(int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int m, int r) {
	// order by knapsack
	for (int i = 0; i < m; i++) {
		decreasingSort3(profitsTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, setups, classes, indexes, m, r, i * n, n + i * n);
	}
}

void decreasingSort3(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int setups[], int classes[], int indexes[], int m, int r, int start, int end) {
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = start; i < end - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		for (j = i + 1; j < end; j++) {

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
void decreasingBestAttribute4(int profits[], int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weights[], int weightsTemp[], int n, int m)
{
	int i, j, max_idx, max_idx2, max_value, max_value2, max_knapsack;

	int *differenceTemp = (int *)malloc(sizeof(int) * n);

	// find difference of all items
	for (j = 0; j < n; j++) {

		// Find the maximum profits of the items in them knapsack
		max_idx = 0;
		max_idx2 = 0;
		max_value = 0;
		max_value2 = 0;
		max_knapsack = 0;
		for (int i = 0; i < m; i++) {

			if (profits[j + i * n] > max_value) {
				max_idx2 = max_idx;
				max_idx = j + i * n;
				max_value2 = max_value;
				max_value = profits[max_idx];
				max_knapsack = i;
			}
			else if (profits[j + i * n] > max_value2) {
				max_idx2 = j + i * n;
				max_value2 = profits[max_idx];
			}

		}

		profitsTemp[j] = profits[max_idx];
		weightsTemp[j] = weights[j];
		profitsItemTemp[j] = j;
		profitsKnapsackTemp[j] = max_knapsack;
		differenceTemp[j] = profits[max_idx] - profits[max_idx2];
	}

	// order by decreasing value
	decreasingSort4(profitsTemp, differenceTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, n);

	free(differenceTemp);
}

void decreasingSort4(int profits[], int differenceTemp[], int profitsKnapsack[], int profitsItem[], int weights[], int n) {
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		for (j = i + 1; j < n; j++) {

			if (differenceTemp[j] > differenceTemp[max_idx])
				max_idx = j;
		}

		// Swap the found maximum item
		// with the first item
		replace(&profits[max_idx], &profits[i]);
		replace(&differenceTemp[max_idx], &differenceTemp[i]);
		replace(&profitsKnapsack[max_idx], &profitsKnapsack[i]);
		replace(&profitsItem[max_idx], &profitsItem[i]);
		replace(&weights[max_idx], &weights[i]);
	}
}

void decreasingAllAttribute4(int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int m, int r) {
	// order by knapsack
	for (int i = 0; i < m; i++) {
		//decreasingSort4(profitsTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, setups, classes, indexes, m, r, i * n, n + i * n);
	}
}

void replace(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void replace(double *a, double *b)
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}