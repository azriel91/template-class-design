/*
 * ImageLoader.hpp
 *
 *  Created on: 25/02/2014
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_SPIKES_IMAGE__IMAGELOADER_HPP_
#define __IM_AZRIEL_SPIKES_IMAGE__IMAGELOADER_HPP_

#include <string>
#include <type_traits>

#include "im/azriel/spikes/image/Image.h"

using namespace std;
using namespace im::azriel::spikes::image;

namespace im {
namespace azriel {
namespace spikes {
namespace image {
namespace loading {

template <class ImageClass>
class ImageLoader {
public:
	ImageLoader() {}
	virtual ~ImageLoader() {}
	virtual ImageClass loadImage(const string path) const = 0;
	virtual void freeImage(ImageClass image) const = 0;
};

} /* namespace loading */
} /* namespace image */
} /* namespace spikes */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_SPIKES_IMAGE__IMAGELOADER_HPP_ */
