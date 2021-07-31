#include "UTILITY.h"

#include <iostream>

#ifndef SORT_H_
#define SORT_H_

// attribute 1
void decreasingBestAttribute1(int profits[], int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weights[], int weightsTemp[], int n, int m);
void decreasingAllAttribute1(int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weightsTemp[], int n, int m);

// attribute 2
void decreasingBestAttribute2(int profits[], int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weights[], int weightsTemp[], int n, int m);
void decreasingAllAttribute2(int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weightsTemp[], int n, int m);

// attribute 3
void decreasingBestAttribute3(int profits[], int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weights[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int m, int r);
void decreasingAllAttribute3(int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weightsTemp[], int setups[], int classes[], int indexes[], int n, int m, int r);

// attribute 4
void decreasingBestAttribute4(int profits[], int profitsTemp[], int profitsKnapsackTemp[], int profitsItemTemp[], int weights[], int weightsTemp[], int n, int m);

#endif /* SORT_H_ */