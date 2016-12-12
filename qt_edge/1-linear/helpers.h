#ifndef HELPERS_H
#define HELPERS_H

#include <stdint.h>
#include <stdlib.h>

// Load image from file "path" converted to 8-bit grayscale, and returns an
// array of this image (or NULL if an error happened). Set the image dimensions
// in `width' and `height'.
uint8_t* load_image_gray(const char* path, size_t* width, size_t* height);

// Free an image buffer returned by load_image_gray
void free_image(uint8_t* img);

// Show an image
void show_image(const uint8_t* img, const size_t width, const size_t height);

// Get current timestamp in seconds
double get_current_timestamp();

#endif
