#include <limits.h>
#include <stdlib.h>

#include "edge_detect.h"

void edge_detect(uint8_t* gray_dst, const uint8_t* gray_img, const int width, const int height, const int edge_width)
{
// TODO: add depth=2
#pragma omp parallel for collapse(2)
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			const int left = MAX(0, x - edge_width);
			const int right = MIN(width-1, x + edge_width);
			const int up = MAX(0, y - edge_width);
			const int down = MIN(height - 1, y + edge_width);

			// Find min and max!
			uint8_t min = 255;
			uint8_t max = 0;
			for (int i = up; i <= down; i++) {
				for (int j = left; j <= right; j++) {
					const uint8_t pixel = gray_img[j+i*width];
					if (pixel < min) {
						min = pixel;
					}
					if (pixel > max) {
						max = pixel;
					}
				}
			}

			// Compute final value
			gray_dst[x+y*width] = max-min;
		}
	}
}
