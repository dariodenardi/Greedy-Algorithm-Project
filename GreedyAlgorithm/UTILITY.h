#ifndef UTILITY_H_
#define UTILITY_H_

// find the class of an item
int findClass(int item, int classes[], int indexes[], int r);

// find if the class is already present in a specific knapsack
bool isClassAlreadyPresentInKnapsack(int n, int m, double f[], int knapsack, int classItem, int classes[], int indexes[], int r);

void copyArray(int oldArray[], int newArray[], int size);

#endif /* UTILITY_H_ */