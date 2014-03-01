/*
 * ImageStore.hpp
 *
 *  Created on: 25/02/2014
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_SPIKES_IMAGE__IMAGESTORE_H_
#define __IM_AZRIEL_SPIKES_IMAGE__IMAGESTORE_H_

#include <string>

using namespace std;

namespace im {
namespace azriel {
namespace spikes {
namespace image {
namespace store {

class ImageStore {
public:
	ImageStore() {}
	virtual ~ImageStore() {}
	/**
	 * Get the number of images in the image store.
	 *
	 * @return the number of images
	 */
	virtual const int getImageCount() const = 0;
	/**
	 * Loads an image and returns the id of the loaded image.
	 *
	 * @param path the path to the image
	 *
	 * @return the id of the loaded image
	 */
	virtual const int loadImage(const string path) = 0;
	/**
	 * Unloads an image of the given id.
	 *
	 * @param imageId the id of the image
	 */
	virtual void unloadImage(const int imageId) = 0;
};

} /* namespace store */
} /* namespace image */
} /* namespace spikes */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_SPIKES_IMAGE__IMAGESTORE_H_ */
