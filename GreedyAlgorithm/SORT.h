#include "UTILITY.h"

#include <iostream>

#ifndef SORT_H_
#define SORT_H_

void ascendingSort(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], double f[], int n, int m);

// attribute 1
void decreasingSort1(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int n, int m);

// attribute 2
void decreasingSort2(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int n, int m);

// attribute 3
void decreasingSort3(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int setups[], int classes[], int indexes[], int n, int m, int r);

// attribute 4
void decreasingSort4(int profits[], int profitsKnapsack[], int profitsItem[], int weights[], int n, int m);

#endif /* SORT_H_ */