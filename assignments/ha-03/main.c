#include "sum.h"
#include <stdio.h>
#include <stdlib.h>

int counter = 0;

int main(int argc, char **argv) {
	uint i;
	uint n = 1000;
	int total;
	int array[n];
	int seed = atoi(argv[1]);

	srand(seed);
	for (i = 0 ; i < n ; i ++) {
		array[i] = (rand() % 21) - 10;
	}
	total = sum_array(n, array);

	printf("Total sum: %d\n", total);

	return 0;
}
