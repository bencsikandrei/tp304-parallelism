#include "histogram_bench.h"
#include <omp.h>
#include <sstream>

#define NTIMES 50
#define REM 10

template <class F>
static double hist_bench(Histogram& h, const double size, F const& f)
{
	std::vector<double> times;
	times.reserve(NTIMES);
	for (int i = 0; i < NTIMES; i++) {
		const double start = get_current_timestamp();
		f(h, size);
		const double end = get_current_timestamp();
		times.push_back(end-start);
	}
	std::sort(times.begin(), times.end());
	double sum = 0;
	for (int i = REM/2; i < NTIMES-(REM/2); i++) {
		sum += times[i];
	}
	return sum/(double)(NTIMES-REM);
}

static double hist_bench_serial(Histogram& h, const double size)
{
	return hist_bench(h, size, [](Histogram& h_, const double size_) { h_.compute_serial(size_); });
}

static double hist_bench_sse(Histogram& h, const double size)
{
	return hist_bench(h, size, [](Histogram& h_, const double size_) { h_.compute_sse(size_); });
}

static double hist_bench_omp(Histogram& h, const double size, const int nthreads)
{
	return hist_bench(h, size, [nthreads](Histogram& h_, const double size_) { h_.compute_omp(size_, nthreads); });
}

benchs_results_type hist_bench_all(Histogram& h, const double size)
{
	benchs_results_type ret;
	ret.emplace_back("serial", hist_bench_serial(h, size));
	ret.emplace_back("sse", hist_bench_sse(h, size));
	for (int i = 1; i <= omp_get_max_threads(); i++) {
		std::stringstream ss_name;
		ss_name << "omp/" << i;
		ret.emplace_back(ss_name.str(), hist_bench_omp(h, size, i));
	}
	return ret;
}

double compute_bandwith(Histogram const& h, const double time_s)
{
	// Bandwidth in MB/s
	return (double)(h.pts_size()*sizeof(double))/(time_s*1024.0*1024.0);
}
