#include <iostream>
#include "StudentLocalization.h"


template<typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& vec) {
	for (auto& el : vec) {
		os << el << '\n';
	}
	return os;
}

std::vector<int> smoothfilter(const std::vector<int> &histogram){
	std::vector<int> rtn;
	rtn.push_back(histogram.at(0));
	rtn.push_back(histogram.at(1));
	for (int i = 2; i < histogram.size() - 2; i++){
		rtn.push_back((histogram.at(i-2) + histogram.at(i - 1) + histogram.at(i) + histogram.at(i + 1) + histogram.at(i+2)) / 5);
	}
	rtn.push_back(histogram.at(histogram.size()-2));
	rtn.push_back(histogram.at(histogram.size()-1));
	return rtn;
}


bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {
	int width = image.getWidth(), heigth = image.getHeight();
	std::vector<int> xHistogram, yHistogram;
	for (int x = 0; x < width; x++){
		xHistogram.push_back(0);
		for (int y = 0; y < heigth; y++){
			if (image.getPixel(x, y) == 0){
				xHistogram.at(x)++;
			}
		}
	}

	for (int y = 0; y < heigth; y++){
		yHistogram.push_back(0);
		for (int x = 0; x < width; x++){
			if (image.getPixel(x, y) == 0){
				yHistogram.at(y)++;
			}
		}
	}
	xHistogram = smoothfilter(xHistogram);
	yHistogram = smoothfilter(yHistogram);
	std::cout << "xHistogram" << xHistogram << std::endl;
	std::cout << "yHistogram" << yHistogram << std::endl;
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