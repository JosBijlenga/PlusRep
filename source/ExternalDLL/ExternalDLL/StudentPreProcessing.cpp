#include "StudentPreProcessing.h"
#include "ImageFactory.h"

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	IntensityImage * grayImage = ImageFactory::newIntensityImage(image.getWidth(),image.getHeight());
	int maxSize = image.getHeight()*image.getWidth();
	for (int i = 0; i < maxSize; i++){
		grayImage->setPixel(i, image.getPixel(i).g);
	}
	return grayImage;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {

	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}