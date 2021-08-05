#ifndef UTILITY_H_
#define UTILITY_H_

// find the class of an item
int findClass(int item, int classes[], int indexes[], int r);

// find the cardinality of an class
int findCardinalityOfClass(int class1, int indexes[]);

// find if the class is already present in a specific knapsack
bool isClassAlreadyPresentInKnapsack(int n, double f[], int knapsack, int classItem, int classes[], int indexes[], int r);

// sum all weights that there are in a specific class without the item inserted in the first parameter
int sumAllWeightsOfClass(int item, int class1, int classes[], int indexes[], int weights[]);

// sum all profits that there are in a specific class without the item inserted in the first parameter
int sumAllProfitsOfClass(int item, int class1, int classes[], int indexes[], int profits[], int i, int n);

void copyArray(int oldArray[], int newArray[], int size);

#endif /* UTILITY_H_ */