#include <stdio.h>
#include <stdlib.h>

#include "bench.h"
#include "minmax.h"

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

	const size_t n = atoll(argv[1]);

	uint32_t (*vec)[n] = malloc( n*sizeof(uint32_t));
    if(!vec) {
        fprintf(stderr, "failed to allocate %lu bytes\n", n*sizeof(uint32_t) );
        return 2;
    }

	srand(0); // Constant values over different launches for "random" numbers
	random_init(n, *vec);

	uint32_t min, max;

	BENCH_START(minmax);
	compute_minmax_more_advanced(n, *vec, &min, &max);
	BENCH_END(minmax, "minmax", n, sizeof(uint32_t), 1, sizeof(uint32_t));

	printf("min = %u / max = %u\n", min, max);
    free(vec);

	return 0;
}
