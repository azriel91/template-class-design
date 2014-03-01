#include <stdexcept>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "im/azriel/spikes/image/Image.h"
#include "im/azriel/spikes/image/loading/ImageLoader.hpp"
#include "im/azriel/spikes/image/store/BasicImageStore.hpp"

using namespace im::azriel::spikes::image;
using namespace im::azriel::spikes::image::loading;
using namespace im::azriel::spikes::image::store;

using testing::ReturnPointee;

class MockImage : public Image {
public:
	MockImage(const int width, const int height) : Image(width, height) {}
	virtual ~MockImage() {}
};

class MockImageLoader : public ImageLoader<const MockImage*> {
public:
	MockImageLoader() {}
	virtual ~MockImageLoader() {};
	MOCK_CONST_METHOD1(loadImage, const MockImage*(const string path));
	MOCK_CONST_METHOD1(freeImage, void(const MockImage* const image));
};

class BasicImageStoreTest : public testing::Test {
protected:
	const MockImageLoader* imageLoader;
	BasicImageStore<const MockImage*>* basicImageStore;

	virtual void SetUp() {
		this->imageLoader = new MockImageLoader();
		this->basicImageStore = new BasicImageStore<const MockImage*>(this->imageLoader);
	}

	virtual void TearDown() {
		delete this->basicImageStore;
		delete this->imageLoader;
	}
};

TEST_F(BasicImageStoreTest, loadsAndStoresImages) {
	auto const mockImage0 = new MockImage(100, 200);
	auto const mockImage1 = new MockImage(200, 300);

	EXPECT_CALL(*this->imageLoader, loadImage("path/to/an/image")).Times(1)
			.WillOnce(ReturnPointee(&mockImage0));
	EXPECT_CALL(*this->imageLoader, loadImage("path/to/another/image")).Times(1)
			.WillOnce(ReturnPointee(&mockImage1));

	auto const imageId0 = this->basicImageStore->loadImage("path/to/an/image");
	auto const imageId1 = this->basicImageStore->loadImage("path/to/another/image");

	EXPECT_EQ(0, imageId0);
	EXPECT_EQ(1, imageId1);
	EXPECT_EQ(mockImage0, this->basicImageStore->get(imageId0));
	EXPECT_EQ(mockImage1, this->basicImageStore->get(imageId1));

	// expect images to be deleted
	EXPECT_CALL(*this->imageLoader, freeImage(mockImage0)).Times(1);
	EXPECT_CALL(*this->imageLoader, freeImage(mockImage1)).Times(1);

	delete mockImage0;
	delete mockImage1;
}

TEST_F(BasicImageStoreTest, callsLoaderToDeleteImages) {
	auto const mockImage0 = new MockImage(100, 200);

	EXPECT_CALL(*this->imageLoader, loadImage("path/to/an/image")).Times(1)
			.WillOnce(ReturnPointee(&mockImage0));

	auto const imageId0 = this->basicImageStore->loadImage("path/to/an/image");

	EXPECT_EQ(1, this->basicImageStore->getImageCount());

	// unload the image
	EXPECT_CALL(*this->imageLoader, freeImage(mockImage0)).Times(1);

	this->basicImageStore->unloadImage(imageId0);

	EXPECT_EQ(0, this->basicImageStore->getImageCount());

	delete mockImage0;
}

TEST_F(BasicImageStoreTest, throwsInvalidArgumentExceptionWhenInvalidIdPassedToGet) {
	auto const mockImage0 = new MockImage(100, 200);

	EXPECT_CALL(*this->imageLoader, loadImage("path/to/an/image"))
			.Times(1)
			.WillOnce(ReturnPointee(&mockImage0));

	this->basicImageStore->loadImage("path/to/an/image");

	EXPECT_THROW(this->basicImageStore->get(404), std::invalid_argument);

	// expect images to be deleted
	EXPECT_CALL(*this->imageLoader, freeImage(mockImage0)).Times(1);

	delete mockImage0;
}
