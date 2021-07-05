#include "SORT.h"

void scambia(int *a, int *b);

void bubbleSort(int v[], int v2[], int n, int v3[]) {
	int i;
	int ordinato = 0;

	while (n > 1 && ordinato == 0) {
		ordinato = 1;
		for (i = 0; i < n - 1; i++) {

			if (v[i] < v[i + 1]) {

				scambia(&v[i], &v[i + 1]);
				scambia(&v2[i], &v2[i + 1]);
				scambia(&v3[i], &v3[i + 1]);
				ordinato = 0;

			}

		}
		n--;
	}
}

void scambia(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}