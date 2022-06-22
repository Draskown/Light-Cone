#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "Circles.h"

using namespace cv;
using namespace std;

float round_d(double val) {
	return ceil(val * 1000.0) / 1000.0;
}

void circles() {
	Mat image150, image50, image, procImg;
	int upper = 255, lower = 114;
	double scale = 0.7, size = 0.03, FOV = 55.0, res = 1920.0;

	for (int i = 0; i < 3; i++) {
		if (i == 1) {
			image = imread("D:/Other/Desktop/Ucheba/HS/QIA/Project/150.jpg");
			lower = 66;
			upper = 87;
			size = 0.07;
		}
		else if (i == 2) {
			image = imread("D:/Other/Desktop/Ucheba/HS/QIA/Project/Test.jpg");
			lower = 87;
			size = 0.05;
		} else
			image = imread("D:/Other/Desktop/Ucheba/HS/QIA/Project/50.jpg");

		image = image(Rect(100, 700, 800, 700));
		cvtColor(image, procImg, COLOR_BGR2GRAY);
		medianBlur(procImg, procImg, 7);

		Mat mask;
		vector<Vec3f> circles;

		inRange(procImg, Scalar(lower), Scalar(upper), mask);
		HoughCircles(mask, circles, HOUGH_GRADIENT, 1,
			400, 200, 10, 90/2, 120/2);

		for (size_t i = 0; i < circles.size(); i++) {
			Vec3i c = circles[i];
			double radius = c[2];

			putText(image,
				to_string(round_d(size / 2.0 / tan(radius * FOV / res / 360.0 * 2.0 * 22.0 / 7.0))) + " cm",
				Point(image.cols / 2 - 100, 150),
				FONT_HERSHEY_COMPLEX,
				1.0,
				Scalar(173, 0, 255),
				2);

			circle(image,
				Point(c[0], c[1]),
				radius,
				Scalar(255, 0, 200),
				2,
				LINE_AA);
		}

		circles.clear();
		resize(image, image, Size(), scale, scale);

		if (i == 1)
			image.copyTo(image150);
		else if (i == 0)
			image.copyTo(image50);
	}

	imshow("circle150", image150);
	imshow("circle50", image50);
	imshow("circle test", image);

	waitKey(0);
	destroyAllWindows();
}