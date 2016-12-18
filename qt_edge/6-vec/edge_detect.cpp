#include <limits.h>
#include <stdlib.h>
#include <x86intrin.h>

#include "edge_detect.h"

void edge_detect(uint8_t* gray_dst, const uint8_t* gray_img, const int width, const int height, const int edge_width)
{
#pragma omp parallel for collapse(2)
	for (int y = edge_width; y < height-edge_width; y++) {
		for (int x_ = edge_width; x_ < ((width-edge_width)&(~15)); x_ += 16) {
			uint8_t mins[16];
			uint8_t maxs[16];
			for (int k = 0; k < 16; k++) {
				const int x = x_+k;
				const int left = x-edge_width;
				const int right = x + edge_width;
				const int up = y - edge_width;
				const int down = y + edge_width;

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
				mins[k] = min;
				maxs[k] = max;
			}

			const __m128i v = _mm_subs_epu8(_mm_loadu_si128((const __m128i*) &maxs[0]),
			                                _mm_loadu_si128((const __m128i*) &mins[0]));
			_mm_storeu_si128((__m128i*)&gray_dst[x_+y*width], v);
		
	}
}
}
