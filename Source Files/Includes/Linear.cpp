#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "Linear.h"

using namespace cv;

Mat reverseCheck(Mat& img, std::vector<Mat>& v, VideoCapture& cap, std::string& filename) {
	if (img.empty()) {
		if (v.size() > 1) {
			v.pop_back();
			return v.back();
		}
		else {
			cap.open(filename);
			cap.read(img);
			return img.clone();
		}
	}
	else {
		v.push_back(img.clone());
		return img.clone();
	}
}


void linear(VideoCapture& cap, Mat& img, std::string& filename) {
	
	Mat procImg, image;
	int lower = 50, upper = 255, pixels = 0, distance = 0,
		frameCounter = 0, frameCount = 30, sum = 0, avg = 0;
	// int max = -1, min = 1000;
	int frames[30]{};

	std::vector<Mat> v;

	/*image = imread("D:/Other/Desktop/Ucheba/HS/QIA/Project/180.jpg");
	procImg = image(Rect(0, 100, 352, 300));
	cvtColor(procImg, procImg, COLOR_BGR2GRAY);

	inRange(procImg, Scalar(lower), Scalar(upper), procImg);
	pixels = countNonZero(procImg);

	putText(procImg,
		std::to_string(pixels),
		Point(5, 25),
		FONT_HERSHEY_DUPLEX, 1,
		Scalar(255, 255, 255));

	imshow("window", procImg);
	waitKey(0);*/

	while (true) {
		cap.read(img);
		image = reverseCheck(img, v, cap, filename);
		procImg = image(Rect (0, 100, 352, 300));
		cvtColor(procImg, procImg, COLOR_BGR2GRAY);
		inRange(procImg, Scalar(lower), Scalar(upper), procImg);

		pixels = countNonZero(procImg);
		distance = -0.041 * pixels + 213.595;

		if (frameCounter < frameCount) {
			frames[frameCounter] = distance;
			frameCounter++;
		}
		else {
			sum = 0;
			avg = 0;

			for (int i = 0; i < frameCount-1; i++) {
				sum += frames[i];
				frames[i] = frames[i + 1];
			}
			frames[frameCount-1] = distance;
			sum += distance;
			avg = sum / frameCount;
		}

		/*if (pixels > max)
			max = pixels;

		if (pixels < min)
			min = pixels;*/

		/*putText(image,
				std::to_string(max) + ", " + std::to_string(min),
				Point(5, 25),
				FONT_HERSHEY_DUPLEX, 1,
				Scalar(255, 255, 255));*/

		putText(image,
			std::to_string(avg) + " cm",
			Point(5, 25),
			FONT_HERSHEY_DUPLEX, 1,
			Scalar(255, 255, 255));

		imshow("linear", image);
		waitKey(1);
	}
}