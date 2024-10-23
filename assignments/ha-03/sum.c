#include "sum.h"

int sum_counter;

int sum_array(uint n, int *A) {
	uint i;
	int sum = 0;

	for (i = 0 ; i < n ; i++) {
		sum += A[i];
	}

	return sum;
}
