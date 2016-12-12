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
	compute_serial(size_interval);
}

void Histogram::compute_omp(double size_interval, int /*nthreads*/)
{
	compute_serial(size_interval);
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
