#include "minmax.h"
#include <assert.h>
#include <limits.h>

void compute_minmax(size_t n, uint32_t* const vec, uint32_t* min, uint32_t* max)
{
	// Compute min/max
	uint32_t local_min = UINT_MAX;
	uint32_t local_max = 0;
	for (size_t i = 0; i < n; i++) {
		const uint32_t v = vec[i];
		if (v < local_min) {
			local_min = v;
		}
		if (v > local_max) {
			local_max = v;
		}
	}

	*min = local_min;
	*max = local_max;
}
