/*
 * Image.cpp
 *
 *  Created on: 25/02/2014
 *      Author: azriel
 */

#include "im/azriel/spikes/image/Image.h"

namespace im {
namespace azriel {
namespace spikes {
namespace image {

Image::Image(const int width, const int height) :
		width(width), height(height) {
}

Image::~Image() {
}

const int Image::getWidth() const {
	return this->width;
}

const int Image::getHeight() const {
	return this->height;
}

} /* namespace image */
} /* namespace spikes */
} /* namespace azriel */
} /* namespace im */
