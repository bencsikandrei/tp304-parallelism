#include "histogram.h"
#include <cstdlib>
#include <cstring>
#include <limits>
#include <omp.h>
#include <vector>
#include <immintrin.h>

Histogram::Histogram(double const* pts, size_t size):
	_pts(pts),
	_pts_size(size),
	_buf(nullptr),
	_buf_size(0)
{
	compute_minmax();
}

void Histogram::compute_serial(double size_interval)
{
	_size_interval = size_interval;
	resize_buf(hist_integer_count());

	memset(_buf, 0, sizeof(uint32_t)*_buf_size);

	const double diff = _max-_min;
	const double min = _min;
	const double* pts = _pts;
	const size_t pts_size = _pts_size;
	for (size_t i = 0; i < pts_size; i++) {
		double const v = (pts[i] - min)/diff;
		_buf[(size_t)(v/size_interval)]++;
	}
}

void Histogram::compute_sse(double size_interval)
{
#ifdef __SSE4_2__
	_size_interval = size_interval;
	resize_buf(hist_integer_count());

	memset(_buf, 0, sizeof(uint32_t)*_buf_size);

	const double diff = _max-_min;
	const double min = _min;
	const double* pts = _pts;
	const size_t pts_size = _pts_size;
	const size_t pts_size_sse = pts_size & (~3ULL);

	const __m128d sse_min = _mm_set1_pd(min);
	const __m128d sse_diff = _mm_set1_pd(diff);
	const __m128d sse_size_interval = _mm_set1_pd(size_interval);
	size_t i;
	for (i = 0; i < pts_size_sse; i += 2) {
		const __m128d sse_pts = _mm_load_pd(&pts[i]);
		__m128d sse_v = _mm_div_pd(
							_mm_sub_pd(sse_pts, sse_min),
							sse_diff);
		sse_v = _mm_div_pd(sse_v, sse_size_interval);
		const __m128i sse_idxes = _mm_cvttpd_epi32(sse_v);
		_buf[_mm_extract_epi32(sse_idxes, 0)]++;
		_buf[_mm_extract_epi32(sse_idxes, 1)]++;
	}
	for (; i < pts_size; i++) {
		double const v = (pts[i] - min)/diff;
		_buf[(size_t)(v/size_interval)]++;
	}
#else
	compute_serial(size_interval);
#endif
}

#if 0
void Histogram::compute_omp(double size_interval, int nthreads)
{
	_size_interval = size_interval;
	const size_t hist_size = hist_integer_count();

	const double diff = _max-_min;
	const double min = _min;
	const double* pts = _pts;

	std::vector<uint32_t*> hist_locals;
	hist_locals.resize(nthreads, NULL);

	const size_t pts_size = _pts_size;
#pragma omp parallel num_threads(nthreads)
	{
		uint32_t* hist_local;
		posix_memalign((void**) &hist_local, 16, sizeof(uint32_t)*hist_size);
		uuumemset(hist_local, 0, sizeof(uint32_t)*hist_size);
		hist_locals[omp_get_thread_num()] = hist_local;

#pragma omp for
		for (size_t i = 0; i < pts_size; i++) {
			double const v = (pts[i] - min)/diff;
			hist_local[(size_t)(v/size_interval)]++;
		}
	}

	uint32_t* final_hist = NULL;

	// Find the first non-null partial histogram
	std::vector<uint32_t*>::const_iterator it;
	for (it = hist_locals.begin(); it != hist_locals.end(); it++) {
		if (*it != NULL) {
			final_hist = *it;
			it++;
			break;
		}
	}

	if (final_hist == NULL) {
		return;
	}

	// Final reduction
	for (; it != hist_locals.end(); it++) {
		uint32_t* hist_local = *it;
		if (hist_local == NULL) {
			continue;
		}
		for (uint32_t i = 0; i < hist_size; i++) {
			final_hist[i] += hist_local[i];
		}
		free(hist_local);
	}

	if (_buf) {
		free(_buf);
	}
	_buf = final_hist;
	_buf_size = hist_size;
}
#endif

void Histogram::compute_omp(double size_interval, int nthreads)
{
	_size_interval = size_interval;
	const size_t hist_size = hist_integer_count();

	const double diff = _max-_min;
	const double min = _min;
	const double* pts = _pts;

	std::vector<uint32_t*> hist_locals;
	hist_locals.resize(nthreads, NULL);

	const size_t pts_size = _pts_size;
	const size_t pts_size_sse = pts_size & (~3ULL);

	const __m128d sse_min = _mm_set1_pd(min);
	const __m128d sse_diff = _mm_set1_pd(diff);
	const __m128d sse_size_interval = _mm_set1_pd(size_interval);

#pragma omp parallel num_threads(nthreads)
	{
		uint32_t* hist_local;
		posix_memalign((void**) &hist_local, 16, sizeof(uint32_t)*hist_size);
		memset(hist_local, 0, sizeof(uint32_t)*hist_size);
		hist_locals[omp_get_thread_num()] = hist_local;

#pragma omp for
		for (size_t i = 0; i < pts_size_sse; i += 2) {
			const __m128d sse_pts = _mm_load_pd(&pts[i]);
			__m128d sse_v = _mm_div_pd(
								_mm_sub_pd(sse_pts, sse_min),
								sse_diff);
			sse_v = _mm_div_pd(sse_v, sse_size_interval);
			const __m128i sse_idxes = _mm_cvttpd_epi32(sse_v);
			hist_local[_mm_extract_epi32(sse_idxes, 0)]++;
			hist_local[_mm_extract_epi32(sse_idxes, 1)]++;
		}
	}

	uint32_t* final_hist = NULL;

	// Find the first non-null partial histogram
	std::vector<uint32_t*>::const_iterator it;
	for (it = hist_locals.begin(); it != hist_locals.end(); it++) {
		if (*it != NULL) {
			final_hist = *it;
			it++;
			break;
		}
	}

	if (final_hist == NULL) {
		return;
	}

	// Final reduction
	for (; it != hist_locals.end(); it++) {
		uint32_t* hist_local = *it;
		if (hist_local == NULL) {
			continue;
		}
		for (uint32_t i = 0; i < hist_size; i++) {
			final_hist[i] += hist_local[i];
		}
		free(hist_local);
	}

	// Missing vectorized values
	for (size_t i = pts_size_sse; i < pts_size; i++) {
		double const v = (pts[i] - min)/diff;
		final_hist[(size_t)(v/size_interval)]++;
	}

	if (_buf) {
		free(_buf);
	}
	_buf = final_hist;
	_buf_size = hist_size;
}

void Histogram::resize_buf(size_t size)
{
	if (_buf_size < size) {
		if (_buf) {
			free(_buf);
		}
		posix_memalign((void**) &_buf, 16, sizeof(uint32_t)*size);
		_buf_size = size;
	}
}

void Histogram::compute_minmax()
{
	double min = std::numeric_limits<double>::max();
	double max = std::numeric_limits<double>::min();

	const size_t pts_size = _pts_size;
	double const* pts = _pts;
	for (size_t i = 0; i < pts_size; i++) {
		double const v = pts[i];
		if (v < min) {
			min = v;
		}
		if (v > max) {
			max = v;
		}
	}

	_min = min;
	_max = max;
}

void Histogram::compute_hist_minmax()
{
	uint32_t min = std::numeric_limits<uint32_t>::max();
	uint32_t max = std::numeric_limits<uint32_t>::min();

	const size_t n = _buf_size;
	uint32_t const* buf = _buf;
	for (size_t i = 0; i < n; i++) {
		uint32_t const v = buf[i];
		if (v < min) {
			min = v;
		}
		if (v > max) {
			max = v;
		}
	}

	_hist_min = min;
	_hist_max = max;
}
