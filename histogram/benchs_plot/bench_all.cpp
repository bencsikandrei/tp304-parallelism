#include "histogram_bench.h"
#include "tools.h"

#include "gnuplot-iostream.h"

#include <iostream>
#include <map>
#include <vector>

static void usage(const char* path)
{
		std::cerr << "Usage: " << path << " [--file file] [--gen-uniform N] [--gen-normal N]" << std::endl;
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

	// From 1 to 5Mb
	//
	std::vector<double> xs;
	std::map<std::string, std::vector<double>> lines;
	for (size_t size_kb = 0; size_kb < 5*1024; size_kb += 16) {
		size_t size_kb_ = (size_kb == 0) ? 1 : size_kb;
		std::cerr << "Computing histogram of " << size_kb_ << "kb..." << std::endl;
		const double size_interval = Histogram::size_interval_from_integer_count(size_kb_*1024/sizeof(uint32_t));
		benchs_results_type all_res = hist_bench_all(hist, size_interval);
		for (auto const& res: all_res) {
			lines[res.first].push_back(compute_bandwith(hist, res.second));
		}
		xs.push_back(size_kb_);
	}

	Gnuplot gp;
	auto it = lines.begin();
	gp << "plot '-' with lines title '" << it->first << "'";
	++it;
	for (; it != lines.end(); it++) {
		gp << ", '-' with lines title '" << it->first << "'";
	}
	gp << "\n";
	for (auto const& line: lines) {
		gp.send1d(std::make_tuple(xs, line.second));
	}

	return 0;
}
