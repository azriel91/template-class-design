/*
 * Image.h
 *
 *  Created on: 25/02/2014
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_SPIKES_IMAGE__IMAGE_H_
#define __IM_AZRIEL_SPIKES_IMAGE__IMAGE_H_

namespace im {
namespace azriel {
namespace spikes {
namespace image {

class Image {
protected:
	/**
	 * The width of this image.
	 */
	const int width;
	/**
	 * The height of this image.
	 */
	const int height;

public:
	/**
	 * @param id the id of the image
	 * @param width the width of the image
	 * @param height the height of the image
	 */
	Image(const int width, const int height);
	virtual ~Image();

	/**
	 * @return the width of this image
	 */
	const int getWidth() const;
	/**
	 * @return the height of this image
	 */
	const int getHeight() const;
};

} /* namespace image */
} /* namespace spikes */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_SPIKES_IMAGE__IMAGE_H_ */
