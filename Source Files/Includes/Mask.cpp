#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "Mask.h"

using namespace cv;

void mask(Mat& image) {
	int lower = 66, upper = 87;
	double scale = 0.7;
	image = imread("D:/Other/Desktop/Ucheba/HS/QIA/Project/Test.jpg");
	image = image(Rect(100, 700, 800, 700));

	resize(image, image, Size(), scale, scale);
	cvtColor(image, image, COLOR_BGR2GRAY);
	medianBlur(image, image, 5);
	namedWindow("Tracks", (640, 200));
	createTrackbar("Min", "Tracks", &lower, 255);
	createTrackbar("Max", "Tracks", &upper, 255);

	Mat mask;
	while (true) {
		inRange(image, Scalar(lower), Scalar(upper), mask);

		imshow("mask_orig", image);
		imshow("mask", mask);

		waitKey(1);
	}
}