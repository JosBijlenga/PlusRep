#include "StudentLocalization.h"

bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {
	features.putFeature(Feature{ Feature::FEATURE_HEAD_TOP       , Point2D < double > {0, 0} });
	features.putFeature(Feature{ Feature::FEATURE_HEAD_RIGHT_SIDE, Point2D < double > {0, 0} });
	features.putFeature(Feature{ Feature::FEATURE_HEAD_RIGHT_SIDE, Point2D < double > {0, 0} });
	return false;
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