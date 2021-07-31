#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "UTILITY.h"

#ifndef RD_INSTANCE_H_
#define RD_INSTANCE_H_

int readInstance(char *file_name, int& n, int& m, int& r, int * &weights, int * &capacities, int * &profits, int * &classes, int * &indexes, int * &setups, int * &b);

// print instance if the order is known
void printInstance(int n, int m, int r, int weights[], int capacities[], int profits[], int classes[], int indexes[], int setups[], int b[]);

// print instance if the order is not known
void printInstance(int n, int m, int r, int weights[], int capacities[], int profits[], int profitsKnapsack[], int profitsItem[], int classes[], int indexes[], int setups[], int b[]);

#endif /* RD_INSTANCE_H_ */