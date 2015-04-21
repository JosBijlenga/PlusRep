#include "IntensityImageStudent.h"

IntensityImageStudent::IntensityImageStudent() : IntensityImage() {
	
}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) : IntensityImage(other.getWidth(), other.getHeight()) {
	int tmpMax = other.getWidth()*other.getHeight();
	thePicture = new Intensity[tmpMax];
	for (int x = 0; x < tmpMax; x++){
		thePicture[x] = other.getPixel(x);
	}
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) : IntensityImage(width, height) {
	thePicture = new Intensity[width*height];
}

IntensityImageStudent::~IntensityImageStudent() {
	delete thePicture;
}

void IntensityImageStudent::set(const int width, const int height) {
	Intensity* newImage = new Intensity[width*height];
	int oldSize = this->getHeight() * this->getWidth();
	for (int i = 0; i < oldSize; i++){
		newImage[i] = thePicture[i];
	}
	IntensityImage::set(width, height);
	Intensity * tmp = thePicture;
	delete tmp;
	thePicture = newImage;
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	IntensityImage::set(other.getWidth(), other.getHeight());
	Intensity * tmp = thePicture;
	delete tmp;
	thePicture = new Intensity[other.getWidth() * other.getHeight()];
	int maxSize = other.getWidth() * other.getHeight();
	for (int i = 0; i < maxSize; i++){
		thePicture[i] = other.getPixel(i);
	}
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	thePicture[x + (y*IntensityImage::getWidth())] = pixel;
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	thePicture[i] = pixel;
}

Intensity IntensityImageStudent::getPixel(int x, int y) const {
	return thePicture[x + (y*IntensityImage::getWidth())];
}

Intensity IntensityImageStudent::getPixel(int i) const {
	return thePicture[i];
}