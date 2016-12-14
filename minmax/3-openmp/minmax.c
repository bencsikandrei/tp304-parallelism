#include "minmax.h"
#include <assert.h>
#include <limits.h>
#include <omp.h>

void compute_minmax(size_t n, uint32_t* const vec, uint32_t* min, uint32_t* max)
{
	uint32_t local_min,local_max;
	// Compute min
	local_min = UINT_MAX;
	local_max = 0;
#pragma omp parallel for reduction(max : local_max), reduction(min : local_min)
	for (size_t i = 0; i < n; i++) {
		const uint32_t v = vec[i];
		if (v > local_max) {
			local_max = v;
		}
		if (v < local_min) {
			local_min = v;
		}
	}
	*min = local_min;
	*max = local_max;
}

void compute_minmax_more_advanced(size_t n, uint32_t* const vec, uint32_t* min, uint32_t* max)
{

	const int nthreads = omp_get_max_threads();
	uint32_t mins[nthreads];
	uint32_t maxs[nthreads];
	for (int i = 0; i < nthreads; i++) {
		mins[i]= UINT_MAX;
		maxs[i]= 0;
	}

#pragma omp parallel
	{
		uint32_t local_min,local_max;
		local_min = UINT_MAX;
		local_max = 0;

#pragma omp for
		for (size_t i = 0; i < n; i++) {
			const uint32_t v = vec[i];
			if (v < local_min) {
				local_min = v;
			}
			if (v > local_max) {
				local_max = v;
			}
		}

		mins[omp_get_thread_num()] = local_min;
		maxs[omp_get_thread_num()] = local_max;
	}

	uint32_t local_min,local_max;
	local_min = mins[0];
	local_max = maxs[0];
	for (int i = 1; i < nthreads; i++) {
		const uint32_t imin = mins[i];
		const uint32_t imax = maxs[i];
		if (imin < local_min) {
			local_min = imin;
		}
		if (imax > local_max) {
			local_max = imax;
		}
	}

	*min = local_min;
	*max = local_max;
}
