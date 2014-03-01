/*
 * BasicImageStore.hpp
 *
 *  Created on: 25/02/2014
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_SPIKES_IMAGE__BASICIMAGESTORE_HPP_
#define __IM_AZRIEL_SPIKES_IMAGE__BASICIMAGESTORE_HPP_

#include <atomic>
#include <cstdio>
#include <map>
#include <string>

#include "im/azriel/spikes/image/store/ImageStore.h"
#include "im/azriel/spikes/image/store/ImageRepository.hpp"
#include "im/azriel/spikes/image/loading/ImageLoader.hpp"

using namespace std;
using namespace im::azriel::spikes::image::loading;

namespace im {
namespace azriel {
namespace spikes {
namespace image {
namespace store {

template<class ImageClass>
class BasicImageStore : public ImageStore, public ImageRepository<ImageClass> {
	typedef typename std::remove_pointer<ImageClass>::type ImageClassType;
	static_assert(std::is_base_of<Image, ImageClassType>::value, "ImageClass must extend im::azriel::spikes::image::Image");
private:
	/**
	 * The image loader to load images.
	 */
	const ImageLoader<ImageClass>* const imageLoader;
	/**
	 * The counter for the next image id.
	 */
	atomic_int nextImageId;
	/**
	 * Map of images by their id.
	 */
	map<const int, ImageClass>* imageById;

public:
	BasicImageStore(const ImageLoader<ImageClass>* const imageLoader);
	virtual ~BasicImageStore();
	/**
	 * Get the number of images in the image store.
	 *
	 * @return the number of images
	 */
	const int getImageCount() const;
	/**
	 * Loads an image and returns the id of the loaded image.
	 *
	 * @param path the path to the image
	 *
	 * @return the id of the loaded image
	 */
	const int loadImage(const string path) override;
	/**
	 * Unloads an image of the given id.
	 *
	 * @param imageId the id of the image
	 */
	void unloadImage(const int imageId) override;
	/**
	 * Returns the image for the given id.
	 *
	 * @param id the id of the image
	 *
	 * @return the image
	 */
	ImageClass get(const int imageId) const override;
};

template<class ImageClass>
BasicImageStore<ImageClass>::BasicImageStore(const ImageLoader<ImageClass>* const imageLoader) :
		imageLoader(imageLoader),
		nextImageId(0),
		imageById(new map<const int, ImageClass>()) {
}

template<class ImageClass>
BasicImageStore<ImageClass>::~BasicImageStore() {
	for (auto entry : *this->imageById) {
		this->imageLoader->freeImage(entry.second);
	}
	delete this->imageById;
}

template<class ImageClass>
const int BasicImageStore<ImageClass>::getImageCount() const {
	return (int) this->imageById->size();
}

template<class ImageClass>
const int BasicImageStore<ImageClass>::loadImage(const string path) {
	auto const image = this->imageLoader->loadImage(path);
	const int id = this->nextImageId++;
	this->imageById->insert(make_pair(id, image));
	return id;
}

template<class ImageClass>
void BasicImageStore<ImageClass>::unloadImage(const int imageId) {
	auto const imageEntry = this->imageById->find(imageId);
	if (imageEntry != this->imageById->end()) {
		this->imageLoader->freeImage(imageEntry->second);
		this->imageById->erase(imageEntry);
		return;
	}

	char message[255];
	sprintf(message, "imageId not found: [%d]", imageId);
	throw std::invalid_argument(message);
}

template<class ImageClass>
ImageClass BasicImageStore<ImageClass>::get(const int imageId) const {
	auto const imageEntry = this->imageById->find(imageId);
	if (imageEntry != this->imageById->end()) {
		return imageEntry->second;
	}

	char message[255];
	sprintf(message, "imageId not found: [%d]", imageId);
	throw std::invalid_argument(message);
}

} /* namespace store */
} /* namespace image */
} /* namespace spikes */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_SPIKES_IMAGE__BASICIMAGESTORE_HPP_ */
