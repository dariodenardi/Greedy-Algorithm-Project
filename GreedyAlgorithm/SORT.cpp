#include "SORT.h"

void findMaxValue(int& max1, int& max2, int i, int profits[], int profitsItem[], int n, int m);
void decreasingSort(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int n);
void replace(int *a, int *b);
void replace(double *a, double *b);

// attribute 1
void decreasingAttribute1(int profits[], int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weights[], int weightsTemp[], int n, int m)
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
		weightsTemp[j] = weights[max_idx];
		profitsItemTemp[j] = j;
		profitsKnapsackTemp[j] = max_knapsack;
	} // items

	// order by decreasing value
	decreasingSort(profitsTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, n);
}

// attribute 2
void decreasingAttribute2(int profits[], int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weights[], int weightsTemp[], int n, int m)
{
	int i, j, max_idx, max_knapsack;
	double max_value;

	for (j = 0; j < n; j++) {

		// Find the maximum profits of the items in them knapsack
		max_idx = 0;
		max_value = 0;
		max_knapsack = 0;
		for (i = 0; i < m; i++) {

			double div1 = (double)profits[j + i * n] / weights[j + i * n];
			if (div1 > max_value) {
				max_idx = j + i * n;
				max_value = profits[max_idx];
				max_knapsack = i;
			}

		}

		profitsTemp[j] = profits[max_idx];
		weightsTemp[j] = weights[max_idx];
		profitsItemTemp[j] = j;
		profitsKnapsackTemp[j] = max_knapsack;
	} // items

	// order by decreasing value
	decreasingSort(profitsTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, n);
}

// attribute 3
void decreasingAttribute3(int profits[], int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weights[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int m, int r)
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
			double div1 = (double)profits[j + i * n] / ((double)(weights[j + i * n] + setups[class1]) / m);

			if (div1 > max_value) {
				max_idx = j + i * n;
				max_value = profits[max_idx];
				max_knapsack = i;
			}

		}

		profitsTemp[j] = profits[max_idx];
		weightsTemp[j] = weights[max_idx];
		profitsItemTemp[j] = j;
		profitsKnapsackTemp[j] = max_knapsack;
	} // items

	// order by decreasing value
	decreasingSort(profitsTemp, profitsKnapsackTemp, profitsItemTemp, weightsTemp, n);
}

// attribute 4
void decreasingSort4(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int n, int m) {
	int i, k, j, max_idx, max_idx2;

	int * itemTemp = (int *)malloc(sizeof(int) * n);
	int * differenceTemp = (int *)malloc(sizeof(int) * n);

	std::cout << "profit1" << "\t" << "profit2" << "\t" << "diff" << "\t" << "item" << std::endl;
	// find difference of all items
	for (i = 0; i < n; i++) {
		findMaxValue(max_idx, max_idx2, i, profits, profitsItem, n, m);
		itemTemp[i] = i;
		differenceTemp[i] = profits[max_idx] - profits[max_idx2];
		std::cout << profits[max_idx] << "\t" << profits[max_idx2] << "\t" << differenceTemp[i] << "\t" << itemTemp[i] + 1 << "\t" << "\t" << weights[max_idx] << std::endl;
	}

	// decreasing order
	//decreasingSort(differenceTemp, NULL, itemTemp, NULL, n);

	// ordinare gli item in base all'ordinamento di sopra
	for (j = 0; j < n; j++) {
		for (i = 0; i < m; i++) {
			//max_idx = // find idx for all item

			if (itemTemp[j] == profitsItem[j + i*m]) {
				replace(&profits[j + i * m], &profits[j]);
				replace(&profitsKnapsack[j + i * m], &profitsKnapsack[j]);
				replace(&profitsItem[j + i * m], &profitsItem[j]);
				replace(&weights[j + i * m], &weights[j]);
			}
			
		}
		
	} // for
	
	free(itemTemp);
	free(differenceTemp);
}

void findMaxValue(int& max1, int& max2, int i, int profits[], int profitsItem[], int n, int m) {

	// Find the two maximum item in unsorted array
	int value1 = 0;
	int value2 = 0;
	for (int j = 0; j < n*m; j++) {

		if (profitsItem[j] == i && profits[j] > value1) {
			value2 = value1;
			value1 = profits[j];
			max2 = max1;
			max1 = j;
		}
		else if (profitsItem[j] == i && profits[j] > value2) {
			value2 = profits[j];
			max2 = j;
		}

	}
}

void decreasingSort(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int n) {
	int i, j, max_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {

		// Find the maximum item in unsorted array
		max_idx = i;
		for (j = i + 1; j < n; j++) {

			if (profits[j] > profits[max_idx])
				max_idx = j;
		}
		std::cout << profits[max_idx] << "\t" << profitsKnapsack[max_idx] + 1 << "\t" << profitsItem[max_idx] + 1 << "\t" << weights[max_idx] << std::endl;
		// Swap the found maximum item
		// with the first item
		replace(&profits[max_idx], &profits[i]);
		replace(&profitsKnapsack[max_idx], &profitsKnapsack[i]);
		replace(&profitsItem[max_idx], &profitsItem[i]);
		replace(&weights[max_idx], &weights[i]);
	}
	std::cout << profits[n-1] << "\t" << profitsKnapsack[n - 1] + 1 << "\t" << profitsItem[n - 1] + 1 << "\t" << weights[n - 1] << std::endl;
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