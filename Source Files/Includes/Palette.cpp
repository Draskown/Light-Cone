#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "Palette.h"

using namespace cv;

void palette(VideoCapture& cap, Mat& image) {
	while (true) {
		cap.read(image);

		Mat temp;

		Vec3d pixel;

		resize(image, temp, Size(6, 1));

		Mat palette = Mat::zeros(Size(300, 70), CV_8UC3);

		for (int i = 0; i < 6; i++)
		{
			pixel = temp.at<Vec3b>(0, i);
			rectangle(palette, Point(50*i,0), Point(50 * i + 49, palette.rows), Scalar(pixel[0], pixel[1], pixel[2]), -1);
		}
		imshow("image", image);
		imshow("palette", palette);

		waitKey(1);
	}
}