#ifndef EDGE_DETECT_H
#define EDGE_DETECT_H

#include <stdint.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void edge_detect(uint8_t* gray_dst, const uint8_t* gray_img, const int width, const int height, const int edge_width);

#endif
