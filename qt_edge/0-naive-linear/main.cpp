#include <iostream>
#include <sstream>
#include <cstdlib>

#include "helpers.h"
#include "edge_detect.h"
#include "bench.h"

#include <QApplication>

int main(int argc, char** argv)
{
	if (argc <= 2) {
		std::cerr << "Usage: " << argv[0] << " image edge_width" << std::endl;
		return 1;
	}

	std::istringstream w(argv[2]);
	int edge_width = 0;
	w >> edge_width;
	if(edge_width <= 0) {
		std::cerr << "E: second argument must be a positive integer" << std::endl;
		return 2;
	}

	// Load the image thanks to QImage
	size_t width, height;
	uint8_t* gray_img = load_image_gray(argv[1], &width, &height);
	if (!gray_img) {
		std::cerr << "E: Unable to load image " << argv[1] << std::endl;
		return 3;
	}

	// Get an 8-bit version of that image
	uint8_t* gray_dst;
	if (posix_memalign((void**) &gray_dst, 16, width*height*sizeof(uint8_t)) != 0) {
		perror("posix_memalign");
		return 1;
	}

	BENCH_START(edge);
	edge_detect(gray_dst, gray_img, width, height, edge_width);
	BENCH_END_TRANSFORM(edge, "edge-detect", sizeof(uint8_t), width*height*edge_width*edge_width);

	// Show result
	QApplication app(argc, argv);
	show_image(gray_dst, width, height);
	app.exec();

	free_image(gray_img);
	free(gray_dst);

	return 0;
}
