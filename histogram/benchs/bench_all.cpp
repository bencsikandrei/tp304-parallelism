#include "histogram_bench.h"
#include "tools.h"

#include <iostream>

static void usage(const char* path)
{
		std::cerr << "Usage: " << path << " [--file file] [--gen-uniform N] [--gen-normal N] nbins" << std::endl;
}

int main(int argc, char** argv)
{
	Histogram hist;
	try {
		hist = std::move(parse_args(argc, argv));
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error while parsing args: " << e.what() << std::endl;
		usage(argv[0]);
		return 1;
	}

	if (argc < 4) {
		usage(argv[0]);
		return 1;
	}

	const double size_interval = Histogram::size_interval_from_integer_count(atoll(argv[3]));
	benchs_results_type all_res = hist_bench_all(hist, size_interval);
	for (auto const& res: all_res) {
		std::cout << res.first << ": " << (res.second*1000.0) << " ms" << std::endl;
	}

	return 0;
}
