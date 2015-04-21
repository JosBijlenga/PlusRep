#include "RGBImageStudent.h"
#include <array>
#include <vector>
RGBImageStudent::RGBImageStudent() : RGBImage() {

}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage(other.getWidth(), other.getHeight()) {
	int tmpMax = other.getWidth()*other.getHeight();
	thePicture = new RGB[tmpMax];
	for (int x = 0; x < tmpMax; x++){
		thePicture[x] = other.getPixel(x);
	}
}


RGBImageStudent::RGBImageStudent(const int width, const int height) : RGBImage(width, height) {
	thePicture = new RGB[width*height];
}

RGBImageStudent::~RGBImageStudent() {
	delete [] thePicture;
}

void RGBImageStudent::set(const int width, const int height) {
	RGB* newImage = new RGB[width*height];
	int oldSize = this->getHeight() * this->getWidth();
	for (int i = 0; (oldSize ? i<width*height : i < oldSize); i++){
		newImage[i] = (oldSize ? RGB{} : thePicture[i]);
	}
	RGBImage::set(width, height);
	RGB * tmp = thePicture;
	delete [] tmp;
	thePicture = newImage;
}

void RGBImageStudent::set(const RGBImageStudent &other) {
	RGBImage::set(other.getWidth(), other.getHeight());
	RGB * tmp = thePicture;
	delete [] tmp;
	thePicture = new RGB[other.getWidth() * other.getHeight()];
	int maxSize = other.getWidth() * other.getHeight();
	for (int i = 0; i < maxSize; i++){
		thePicture[i] = other.getPixel(i);
	}
}

void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
	thePicture[x+(y*RGBImage::getWidth())] = pixel;
}

void RGBImageStudent::setPixel(int i, RGB pixel) {
	thePicture[i] = pixel;
}

RGB RGBImageStudent::getPixel(int x, int y) const {
	return thePicture[x+(y*RGBImage::getWidth())];
}

RGB RGBImageStudent::getPixel(int i) const {
	return thePicture[i];
}