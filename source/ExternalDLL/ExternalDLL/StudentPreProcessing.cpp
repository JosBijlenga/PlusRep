#include "StudentPreProcessing.h"
#include "ImageFactory.h"
#include <math.h>

#define BILINIEAR 0

IntensityImage * StudentPreProcessing::nearestNeighbour(const IntensityImage &image) const {
	const int newX = image.getWidth()*3, newY = newX / ((float)image.getWidth() / (float)image.getHeight());
	IntensityImage * newImage = ImageFactory::newIntensityImage(newX, newY);
	float x_ratio = (float)image.getWidth() / newX;
	float y_ratio = (float)image.getHeight() / newY;
	int x2, y2;
	for (int x = 0; x<newX; x++) {
		for (int y = 0; y<newY; y++) {
			x2 = floor(x*x_ratio);
			y2 = floor(y*y_ratio);
			newImage->setPixel(x, y, image.getPixel(x2, y2));
		}
	}
	return newImage;
}

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	IntensityImage * grayImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	int maxSize = image.getHeight()*image.getWidth();
	for (int i = 0; i < maxSize; i++){
		grayImage->setPixel(i, image.getPixel(i).g);
	}
	return grayImage;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	#if BILINIEAR
		return stepScaleImageBilinear(image);
	#else
		return nearestNeighbour(image);
	#endif
}

IntensityImage * StudentPreProcessing::stepScaleImageBilinear(const IntensityImage &image) const{
	const int newX = 200, newY = newX / ((float)image.getWidth() / (float)image.getHeight());
	IntensityImage * newImg = ImageFactory::newIntensityImage(newX, newY);



	return newImg;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	int width = image.getWidth(), height = image.getHeight();
	IntensityImage * newImg = ImageFactory::newIntensityImage(width, height);

	// loop over the old intensityImage
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			// border
			if ((x == 0) || (x == width - 1) ||
				(y == 0) || (y == height - 1) ||
				(x == 1) || (x == width - 2) ||
				(y == 1) || (y == height - 2)
				){
				newImg->setPixel(x, y, 255);
			}
			else{
				// apply mask on current value and calculate new values
				float sum[25];
				
				// row one
				sum[0] = image.getPixel(x - 2, y - 2) * -4.0f;
				sum[1] = image.getPixel(x - 1, y - 2) * -1.0f;
				sum[2] = image.getPixel(x, y - 2) *  0.0f;
				sum[3] = image.getPixel(x + 1, y - 2) * -1.0f;
				sum[4] = image.getPixel(x + 2, y - 2) * -4.0f;

				// row two
				sum[5] = image.getPixel(x - 2, y - 1) * -1.0f;
				sum[6] = image.getPixel(x - 1, y - 1) *  2.0f;
				sum[7] = image.getPixel(x, y - 1) *  3.0f;
				sum[8] = image.getPixel(x + 1, y - 1) *  2.0f;
				sum[9] = image.getPixel(x + 2, y - 1) * -1.0f;

				// row three
				sum[10] = image.getPixel(x - 2, y) *  0.0f;
				sum[11] = image.getPixel(x - 1, y) *  3.0f;
				sum[12] = image.getPixel(x, y) *  4.0f;
				sum[13] = image.getPixel(x + 1, y) *  3.0f;
				sum[14] = image.getPixel(x + 2, y) *  0.0f;

				// row four
				sum[15] = image.getPixel(x - 2, y - 1) * -1.0f;
				sum[16] = image.getPixel(x - 1, y - 1) *  2.0f;
				sum[17] = image.getPixel(x, y - 1) *  3.0f;
				sum[18] = image.getPixel(x + 1, y - 1) *  2.0f;
				sum[19] = image.getPixel(x + 2, y - 1) * -1.0f;

				// row five
				sum[20] = image.getPixel(x - 2, y - 2) * -4.0f;
				sum[21] = image.getPixel(x - 1, y - 2) * -1.0f;
				sum[22] = image.getPixel(x, y - 2) *  0.0f;
				sum[23] = image.getPixel(x + 1, y - 2) * -1.0f;
				sum[24] = image.getPixel(x + 2, y - 2) * -4.0f;
				
				float avg = 0;
				for (int i = 0; i < 25; i++){
					avg += sum[i];
				}
				avg /= 9;

				newImg->setPixel(x, y, (int)avg);
			}
		}
	}

	return newImg;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	int width = image.getWidth(), height = image.getHeight();
	IntensityImage * newImg = ImageFactory::newIntensityImage(width, height);

	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			if (image.getPixel(x, y) < 20 || image.getPixel(x, y) > 140){
				newImg->setPixel(x, y, 255);
			}
			else{
				newImg->setPixel(x, y, 0);
			}
		}
	}
	return newImg;
}