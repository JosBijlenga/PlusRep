#include <iostream>
#include <math.h>
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
		rtn.push_back((histogram.at(i - 2) + histogram.at(i - 1) + histogram.at(i) + histogram.at(i + 1) + histogram.at(i + 2)) / 5);
	}
	rtn.push_back(histogram.at(histogram.size() - 2));
	rtn.push_back(histogram.at(histogram.size() - 1));
	return rtn;
}

std::vector<int> derivative(const std::vector<int> &histogram){
	std::vector<int> rtn;
	for (int i = 0; i < histogram.size() - 1; i++){
		rtn.push_back(histogram.at(i + 1) - histogram.at(i));
	}
	rtn.push_back(0);
	return rtn;
}

std::vector<int> abs(const std::vector<int> &histogram){
	std::vector<int> rtn;
	for (int i = 0; i < histogram.size() - 1; i++){
		rtn.push_back(abs(histogram.at(i)));
	}
	rtn.push_back(0);
	return rtn;
}

float getAverageVector(const std::vector<int> &histogram){
	float total = 0;
	for (auto element : histogram){
		total += element;
	}
	return total / histogram.size();
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
	xHistogram = abs(smoothfilter(derivative(smoothfilter(xHistogram))));
	yHistogram = abs(smoothfilter(derivative(smoothfilter(yHistogram))));
	int xLeft = 0, yLeft = 0,xMid = 0, yMid = 0, xRight = 0, yRight = 0;
	float xHistogramAverage = 5*getAverageVector(xHistogram), yHistogramAverage = 5*getAverageVector(yHistogram);
	//Eerste linker piek zoeken
	for (int x = 0; x < xHistogram.size(); x++){
		if (xHistogram.at(x) > xHistogramAverage){
			xLeft = x;
			break;
		}
	}
	//Eerste rechter piek zoeken
	for (int x = xHistogram.size() - 1; x >= 0; x--){
		if (xHistogram.at(x) > xHistogramAverage){
			xRight = x;
			break;
		}
	}
	//Midden v h hoofd
	xMid = (xRight + xLeft)/2;
	//Hoogte van hoofd
	for (int y = 0; y < xHistogram.size() - 1; y++){
		if (yHistogram.at(y) > yHistogramAverage){
			yMid = y;
			break;
		}
	}
	std::cout << "x average: " << xHistogramAverage << '\n';
	std::cout << "x left: " << xLeft << "  x mid: " << xMid << "  x right: " << xRight << '\n';
	std::cout << "y left: " << yLeft << "  y mid: " << yMid << "  y right: " << yRight << '\n';
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