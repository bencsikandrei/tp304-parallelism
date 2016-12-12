#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <cstdlib>
#include <cstdint>
#include <cmath>

class Histogram
{
public:
	Histogram() { }

	Histogram(double const* pts, size_t size);
	Histogram(Histogram&& o):
		_pts(o._pts),
		_pts_size(o._pts_size),
		_min(o._min),
		_max(o._max),
		_buf(o._buf),
		_buf_size(o._buf_size),
		_size_interval(o._size_interval),
		_hist_min(o._hist_min),
		_hist_max(o._hist_max)
	{
		o._buf = nullptr;
		o._buf_size = 0;
	}

public:
	Histogram& operator=(Histogram&& o)
	{
		if (&o == this) {
			return *this;
		}

		_pts = o._pts;
		_pts_size = o._pts_size;
		_min = o._min;
		_max = o._max;
		_buf = o._buf;
		_buf_size = o._buf_size;
		_size_interval = o._size_interval;
		_hist_min = o._hist_min;
		_hist_max = o._hist_max;

		o._buf = nullptr;
		o._buf_size = 0;

		return *this;
	}

public:
	inline void compute(double size_interval) { compute_sse(size_interval); }

	void compute_serial(double size_interval);
	void compute_sse(double size_interval);
	void compute_omp(double size_interval, int nthreads);

public:
	void compute_hist_minmax();

public:
	uint32_t const* hist() const { return _buf; }
	double size_interval() const { return _size_interval; }
	size_t hist_integer_count() const { return std::ceil(1.0/size_interval())+1; }
	uint32_t hist_max() const { return _hist_max; }
	size_t pts_size() const { return _pts_size; }

	static double size_interval_from_integer_count(size_t hist_count) { return 1.0/(hist_count); }

private:
	void resize_buf(size_t size);
	void compute_minmax();

private:
	double const* _pts;
	size_t _pts_size;

	double _min;
	double _max;

	uint32_t* _buf;
	size_t _buf_size;
	double _size_interval;
	uint32_t _hist_min;
	uint32_t _hist_max;
};

#endif
