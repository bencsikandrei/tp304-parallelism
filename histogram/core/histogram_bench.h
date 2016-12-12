#ifndef HISTOGRAM_BENCH_H
#define HISTOGRAM_BENCH_H

#include "histogram.h"
#include "tools.h"

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

typedef std::vector<std::pair<std::string, double>> benchs_results_type;

benchs_results_type hist_bench_all(Histogram& h, const double size);
double compute_bandwith(Histogram const& h, const double time_s);

#endif
