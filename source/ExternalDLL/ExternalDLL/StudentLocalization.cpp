#include "StudentLocalization.h"

bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {
	int width = image.getWidth(), heigth = image.getHeight();

	bool stop = false;
	//horizontale lijnen
	for (int y = 0; y < heigth && !stop; y++){
		int tmpXArray[2] = { 0 }; //element 0 = black element 1 = white
		for (int x = 0; x < width && !stop; x++){
			tmpXArray[image.getPixel(x, y) == 0 ? 0 : 1]++; //checks if pixel is black or white and then adds 1 accordingly;
		}
		if (tmpXArray[0]>10){
			stop = true;
			features.putFeature(Feature{ Feature::FEATURE_HEAD_TOP, Point2D < double > {0, static_cast<double>(y)} });
		}
	}

	//verticale links naar rechts
	stop = false;
	for (int x = 0; x < width; x++){
		int tmpYArray[2] = { 0 }; //element 0 = black element 1 = white
		for (int y = 0; y < heigth && !stop; y++){
			tmpYArray[image.getPixel(x, y) == 0 ? 0 : 1]++; //checks if pixel is black or white and then adds 1 accordingly;
		}
		if (tmpYArray[0]>20){
			stop = true;
			features.putFeature(Feature{ Feature::FEATURE_HEAD_LEFT_SIDE, Point2D < double > {static_cast<double>(x), 0} });
		}
	}

	//verticale rechts naar links
	stop = false;
	for (int x = width -1; x >= 0; x--){
		int tmpYArray[2] = { 0 }; //element 0 = black element 1 = white
		for (int y = 0; y < heigth && !stop; y++){
			tmpYArray[image.getPixel(x, y) == 0 ? 0 : 1]++; //checks if pixel is black or white and then adds 1 accordingly;
		}
		if (tmpYArray[0]>20){
			stop = true;
			features.putFeature(Feature{ Feature::FEATURE_HEAD_RIGHT_SIDE, Point2D < double > {static_cast<double>(x), 0} });
		}
	}
	return true;
}

bool StudentLocalization::stepFindNoseMouthAndChin(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindChinContours(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindNoseEndsAndEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindExactEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}