#include "SORT.h"

void decreasingSort1(int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weightsTemp[], int n);
void decreasingSort2(int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weightsTemp[], int n);
void decreasingSort3(int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int m, int r);
void decreasingSort4(int profitsTemp[], int differenceTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weightsTemp[], int n);
void decreasingSort5(int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int r);
void decreasingSort6(int profits[], int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weights[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int r);
void replace(int *a, int *b);
void replace(double *a, double *b);

// attribute 1
void decreasingAttribute1(int profits[], int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weights[], int weightsTemp[], int n, int m)
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
		itemIndexTemp[j] = j;
		itemKnapsackTemp[j] = max_knapsack;
	} // items

	// order by decreasing value
	decreasingSort1(profitsTemp, itemKnapsackTemp, itemIndexTemp, weightsTemp, n);
}

void decreasingSort1(int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weightsTemp[], int n) {
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		for (j = i + 1; j < n; j++) {

			if (profitsTemp[j] > profitsTemp[max_idx])
				max_idx = j;
		}

		// Swap the found maximum item
		// with the first item
		replace(&profitsTemp[max_idx], &profitsTemp[i]);
		replace(&itemKnapsackTemp[max_idx], &itemKnapsackTemp[i]);
		replace(&itemIndexTemp[max_idx], &itemIndexTemp[i]);
		replace(&weightsTemp[max_idx], &weightsTemp[i]);
	}
}

// attribute 2
void decreasingAttribute2(int profits[], int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weights[], int weightsTemp[], int n, int m)
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
		itemIndexTemp[j] = j;
		itemKnapsackTemp[j] = max_knapsack;
	} // items

	// order by decreasing value
	decreasingSort2(profitsTemp, itemKnapsackTemp, itemIndexTemp, weightsTemp, n);
}

void decreasingSort2(int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weightsTemp[], int n) {
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		for (j = i + 1; j < n; j++) {

			double div1 = (double)profitsTemp[j] / weightsTemp[j];
			double div2 = (double)profitsTemp[max_idx] / weightsTemp[max_idx];
			if (div1 > div2)
				max_idx = j;
		}

		// Swap the found maximum item
		// with the first item
		replace(&profitsTemp[max_idx], &profitsTemp[i]);
		replace(&itemKnapsackTemp[max_idx], &itemKnapsackTemp[i]);
		replace(&itemIndexTemp[max_idx], &itemIndexTemp[i]);
		replace(&weightsTemp[max_idx], &weightsTemp[i]);
	}
}

// attribute 3
void decreasingAttribute3(int profits[], int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weights[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int m, int r)
{
	int i, j, max_idx, max_knapsack;
	double max_value;

	for (j = 0; j < n; j++) {

		// Find the maximum profits of the items in them knapsack
		max_idx = 0;
		max_value = 0;
		max_knapsack = 0;
		for (i = 0; i < m; i++) {

			int class1 = findClass(j, classes, indexes, r);
			double div1 = (double)profits[j + i * n] / ((double)(weights[j] + setups[class1]) / m);

			if (div1 > max_value) {
				max_idx = j + i * n;
				max_value = div1;
				max_knapsack = i;
			}

		}

		profitsTemp[j] = profits[max_idx];
		weightsTemp[j] = weights[j];
		itemIndexTemp[j] = j;
		itemKnapsackTemp[j] = max_knapsack;
	} // items

	// order by decreasing value
	decreasingSort3(profitsTemp, itemKnapsackTemp, itemIndexTemp, weightsTemp, setups, classes, indexes, n, m, r);
}

void decreasingSort3(int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int m, int r) {
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		for (j = i + 1; j < n; j++) {

			int class1 = findClass(itemIndexTemp[j], classes, indexes, r);
			int class2 = findClass(itemIndexTemp[max_idx], classes, indexes, r);
			double div1 = (double)profitsTemp[j] / ((double)(weightsTemp[j] + setups[class1]) / m);
			double div2 = (double)profitsTemp[max_idx] / ((double)(weightsTemp[max_idx] + setups[class2]) / m);

			if (div1 > div2)
				max_idx = j;
		}

		// Swap the found maximum item
		// with the first item
		replace(&profitsTemp[max_idx], &profitsTemp[i]);
		replace(&itemKnapsackTemp[max_idx], &itemKnapsackTemp[i]);
		replace(&itemIndexTemp[max_idx], &itemIndexTemp[i]);
		replace(&weightsTemp[max_idx], &weightsTemp[i]);
	}
}

// attribute 4
void decreasingAttribute4(int profits[], int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weights[], int weightsTemp[], int n, int m)
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
		itemIndexTemp[j] = j;
		itemKnapsackTemp[j] = max_knapsack;
		differenceTemp[j] = profits[max_idx] - profits[max_idx2];
	}

	// order by decreasing value
	decreasingSort4(profitsTemp, differenceTemp, itemKnapsackTemp, itemIndexTemp, weightsTemp, n);

	free(differenceTemp);
}

void decreasingSort4(int profitsTemp[], int differenceTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weightsTemp[], int n) {
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
		replace(&profitsTemp[max_idx], &profitsTemp[i]);
		replace(&differenceTemp[max_idx], &differenceTemp[i]);
		replace(&itemKnapsackTemp[max_idx], &itemKnapsackTemp[i]);
		replace(&itemIndexTemp[max_idx], &itemIndexTemp[i]);
		replace(&weightsTemp[max_idx], &weightsTemp[i]);
	}
}

// attribute 5
void decreasingAttribute5(int profits[], int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weights[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int m, int r)
{
	int i, j, max_idx, max_knapsack;
	double max_value;

	for (j = 0; j < n; j++) {

		// Find the maximum profits of the items in them knapsack
		max_idx = 0;
		max_value = 0;
		max_knapsack = 0;
		for (i = 0; i < m; i++) {

			int class1 = findClass(j, classes, indexes, r);
			int cardinality1 = findCardinalityOfClass(class1, indexes);

			double div1 = (double)profits[j + i * n] / ((double)(weights[j] + setups[class1]) / cardinality1);

			if (div1 > max_value) {
				max_idx = j + i * n;
				max_value = div1;
				max_knapsack = i;
			}

		}

		profitsTemp[j] = profits[max_idx];
		weightsTemp[j] = weights[j];
		itemIndexTemp[j] = j;
		itemKnapsackTemp[j] = max_knapsack;
	} // items

	// order by decreasing value
	decreasingSort5(profitsTemp, itemKnapsackTemp, itemIndexTemp, weightsTemp, setups, classes, indexes, n, r);
}

void decreasingSort5(int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int r) {
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		for (j = i + 1; j < n; j++) {

			int class1 = findClass(itemIndexTemp[j], classes, indexes, r);
			int cardinality1 = findCardinalityOfClass(class1, indexes);
			int class2 = findClass(itemIndexTemp[max_idx], classes, indexes, r);
			int cardinality2 = findCardinalityOfClass(class2, indexes);

			double div1 = (double)profitsTemp[j] / ((double)(weightsTemp[j] + setups[class1]) / cardinality1);
			double div2 = (double)profitsTemp[max_idx] / ((double)(weightsTemp[max_idx] + setups[class2]) / cardinality2);

			if (div1 > div2)
				max_idx = j;
		}

		// Swap the found maximum item
		// with the first item
		replace(&profitsTemp[max_idx], &profitsTemp[i]);
		replace(&itemKnapsackTemp[max_idx], &itemKnapsackTemp[i]);
		replace(&itemIndexTemp[max_idx], &itemIndexTemp[i]);
		replace(&weightsTemp[max_idx], &weightsTemp[i]);
	}
}

// attribute 6
void decreasingAttribute6(int profits[], int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weights[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int m, int r)
{
	int i, j, max_idx, max_knapsack;
	double max_value;

	for (j = 0; j < n; j++) {

		// Find the maximum profits of the items in them knapsack
		max_idx = 0;
		max_value = 0;
		max_knapsack = 0;
		for (i = 0; i < m; i++) {

			int class1 = findClass(j, classes, indexes, r);
			double ro1 = (double)sumAllWeightsOfClass(j, class1, classes, indexes, weights) / sumAllProfitsOfClass(j, class1, classes, indexes, profits, i, n);

			double div1 = (double)profits[j + i * n] / (weights[j] + (double)setups[class1] * ro1);

			if (div1 > max_value) {
				max_idx = j + i * n;
				max_value = div1;
				max_knapsack = i;
			}

		}

		profitsTemp[j] = profits[max_idx];
		weightsTemp[j] = weights[j];
		itemIndexTemp[j] = j;
		itemKnapsackTemp[j] = max_knapsack;
	} // items

	// order by decreasing value
	decreasingSort6(profits, profitsTemp, itemKnapsackTemp, itemIndexTemp, weights, weightsTemp, setups, classes, indexes, n, r);
}

void decreasingSort6(int profits[], int profitsTemp[], int itemKnapsackTemp[], int itemIndexTemp[], int weights[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int r) {
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		for (j = i + 1; j < n; j++) {

			int class1 = findClass(itemIndexTemp[j], classes, indexes, r);
			double ro1 = (double)sumAllWeightsOfClass(itemIndexTemp[j], class1, classes, indexes, weights) / sumAllProfitsOfClass(itemIndexTemp[j], class1, classes, indexes, profits, itemKnapsackTemp[j], n);
			int class2 = findClass(itemIndexTemp[max_idx], classes, indexes, r);
			double ro2 = (double)sumAllWeightsOfClass(itemIndexTemp[max_idx], class2, classes, indexes, weights) / sumAllProfitsOfClass(itemIndexTemp[max_idx], class2, classes, indexes, profits, itemKnapsackTemp[max_idx], n);

			double div1 = (double)profitsTemp[j] / (weightsTemp[j] + (double)setups[class1] * ro1);
			double div2 = (double)profitsTemp[max_idx] / (weightsTemp[max_idx] + (double)setups[class2] * ro2);

			if (div1 > div2)
				max_idx = j;
		}

		// Swap the found maximum item
		// with the first item
		replace(&profitsTemp[max_idx], &profitsTemp[i]);
		replace(&itemKnapsackTemp[max_idx], &itemKnapsackTemp[i]);
		replace(&itemIndexTemp[max_idx], &itemIndexTemp[i]);
		replace(&weightsTemp[max_idx], &weightsTemp[i]);
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