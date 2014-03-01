/*
 * ImageRepository.hpp
 *
 *  Created on: 25/02/2014
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_SPIKES_IMAGE__IMAGEREPOSITORY_HPP_
#define __IM_AZRIEL_SPIKES_IMAGE__IMAGEREPOSITORY_HPP_

namespace im {
namespace azriel {
namespace spikes {
namespace image {
namespace store {

template<class ImageClass>
class ImageRepository {
public:
	ImageRepository() {}
	virtual ~ImageRepository() {}
	/**
	 * Returns the image for the given id.
	 *
	 * @param id the id of the image
	 *
	 * @return the image
	 */
	virtual ImageClass get(const int imageId) const = 0;
};

} /* namespace store */
} /* namespace image */
} /* namespace spikes */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_SPIKES_IMAGE__IMAGEREPOSITORY_HPP_ */
