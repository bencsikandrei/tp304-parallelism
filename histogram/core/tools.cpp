#include <fstream>
#include <sys/time.h>
#include <cstdlib>
#include <string.h>
#include <boost/random.hpp>

#include "tools.h"

class parse_args_exception: public std::exception
{
public:
	parse_args_exception(const char* str):
		_str(str)
	{ }

public:
	const char* what() const throw() override { return _str.c_str(); }

private:
	std::string _str;
};

Histogram parse_args(int argc, char** argv)
{
	if (argc <= 2) {
		throw parse_args_exception("invalid arguments");
	}

	const char* action = argv[1];
	double* pts;
	size_t n = 0;

	boost::mt19937 rng;

	if (strcmp(action, "--file") == 0) {
		const char* path = argv[2];
		std::ifstream file;
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		file.open(path, std::ifstream::in);
		double v;
		std::vector<double> pts_;
		file.exceptions(std::ifstream::goodbit);
		while (file >> v) {
			pts_.push_back(v);
		}
		n = pts_.size();
		posix_memalign((void**) &pts, 16, sizeof(double)*n);
		memcpy(pts, &pts_[0], sizeof(double)*n);
	}
	else
	if (strcmp(action, "--gen-uniform") == 0) {
		boost::random::uniform_real_distribution<double> rand;
		n = atoll(argv[2]);
		posix_memalign((void**) &pts, 16, sizeof(double)*n);
		for (size_t i = 0; i < n; i++) {
			pts[i] = rand(rng);
		}
	}
	else
	if (strcmp(action, "--gen-normal") == 0) {
		boost::normal_distribution<double> rand(10.0, 2.0);
		n = atoll(argv[2]);
		posix_memalign((void**) &pts, 16, sizeof(double)*n);
		for (size_t i = 0; i < n; i++) {
			pts[i] = rand(rng);
		}
	}

	Histogram ret(pts, n);
	return std::move(ret);
}

double get_current_timestamp()
{
	struct timeval curt;
	gettimeofday(&curt, NULL);
	return (double)curt.tv_sec + ((double)curt.tv_usec)/1000000.0;
}
