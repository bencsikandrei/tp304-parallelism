#include <stdio.h>
#include <stdlib.h>

#include "bench.h"
#include "minmax.h"
// initialize all array values to a random number
static void random_init(size_t n, uint32_t v[n]) {
	for(size_t i=0;i<n; i++)
		v[i] = rand();
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s n\n", argv[0]);
		return 1;
	}
	// covert the argument to a long long
	const size_t n = atoll(argv[1]);
	// allocate enough memory for as many ints as the user requires
	uint32_t (*vec)[n] = malloc( n * sizeof(uint32_t));
    if(!vec) {
        fprintf(stderr, "failed to allocate %lu bytes\n", n*sizeof(uint32_t) );
        return 2;
    }

	srand(0); // Constant values over different launches for "random" numbers
	
	random_init(n, *vec);

	uint32_t min, max;
	// time the run and compute the throughput
	BENCH_START(minmax);
	compute_minmax(n, *vec, &min, &max);
	BENCH_END(minmax, "minmax", n, sizeof(uint32_t), 1, sizeof(uint32_t));

	printf("min = %u / max = %u\n", min, max);
    free(vec);

	return 0;
}
