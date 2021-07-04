#include "SORT.h"

void merge(int v[], int i1, int i2, int fine, int vout[]);

void mergeSort(int v[], int first, int last, int vout[]) {
	int mid;

	if (first < last) {
		mid = (last + first) / 2;
		mergeSort(v, first, mid, vout);
		mergeSort(v, mid + 1, last, vout);
		merge(v, first, mid + 1, last, vout);
	}
}

void merge(int v[], int i1, int i2, int fine, int vout[]) {
	int i = i1, j = i2, k = i1;

	while (i <= i2 - 1 && j <= fine) {
		if (v[i] < v[j])
			vout[k] = v[i++];
		else
			vout[k] = v[j++];
		k++;
	}

	while (i <= i2 - 1) { 
		vout[k] = v[i++];
		k++;
	}
	
	while (j <= fine) { 
		vout[k] = v[j++];
		k++;
	}
	
	for (i = i1; i <= fine; i++)
		v[i] = vout[i];
}