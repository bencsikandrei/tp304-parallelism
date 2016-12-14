#include "minmax.h"
#include <assert.h>
#include <limits.h>

#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>

#include <cstdint>

class TBBMinMax {
protected:
	// declare the required variables
	const uint32_t* _arr;
	uint32_t _max_value;
	uint32_t _min_value;

public:
	// constructor with an array
	TBBMinMax(const uint32_t* arr) :
		// constructor initialization
		_arr(arr),
		_max_value(0),
		_min_value(UINT_MAX)
	{
	}
	// second constructor, a splitting constructor, to make smaller inputs 
	TBBMinMax(TBBMinMax& x, tbb::split):
		_arr(x._arr),
		_max_value(0),
		_min_value(UINT_MAX)
	{
	}
public:
	// declare the two operators, min and max
	void operator()(const tbb::blocked_range<size_t>& r)
	{
		const uint32_t* arr = _arr;
		uint32_t min_value = _min_value;
		uint32_t max_value = _max_value;

		for (size_t i = r.begin(); i != r.end(); i++) {
			const uint32_t value = arr[i];
			if (value > max_value) {
				max_value = value;
			}
			if (value < min_value) {
				min_value = value;
			}
		}

		_min_value = min_value;
		_max_value = max_value;
	}
	// part that merges the result
	void join(const TBBMinMax& y)
	{
		if (y._max_value > _max_value) {
			_max_value = y._max_value;
		}
		if (y._min_value < _min_value) {
			_min_value = y._min_value;
		}
	}

	inline uint32_t get_max_value() const { return _max_value; }
	inline uint32_t get_min_value() const { return _min_value; }
};

void compute_minmax(uint32_t n, const uint32_t* vec, uint32_t* min, uint32_t* max)
{
	TBBMinMax minmax(vec);
	tbb::parallel_reduce(tbb::blocked_range<size_t>(0, n), minmax);
	*min = minmax.get_min_value();
	*max = minmax.get_max_value();
}
