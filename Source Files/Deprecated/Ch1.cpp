#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int mx, my, countdown = -1, flag_down = 0;
float w = 250, h = 350;

Point2f dst[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };

string text = "0, 0";

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if ((event == EVENT_MOUSEMOVE) && (flags == EVENT_FLAG_LBUTTON)) {
		flag_down = 1;
		mx = x; my = y;
	}

	if (event == EVENT_LBUTTONUP)
	{
		if (countdown < 3)
			countdown++;
		else
			countdown = 0;

		flag_down = 0;

		mx = x; my = y;

		switch (countdown)
		{
		case -1:
			text = "0, 0";
			break;
		case 0:
			text = "w, 0";
			break;
		case 1:
			text = "0, h";
			break;
		default:
			text = "w, h";
			break;
		}
	}

}

void main() {

	Mat img = imread("D:/Other/Desktop/Screenshot_1.png");
	Mat img2, matrix, imgWarp;

	Point2f src[4];

	namedWindow("W");

	setMouseCallback("W", CallBackFunc, NULL);

	while (true) {
		img.copyTo(img2);
		putText(
			img2,
			text, 
			Point(20, 20), 
			FONT_HERSHEY_DUPLEX, 
			0.6, 
			Scalar(255, 255, 255));		

		if (src[0].x != 0)
			for (int i = 0; i < 4; i++)
				circle(img2, src[i], 10, Scalar(177, 0, 255), FILLED);

		if (flag_down)
			circle(img2, Point(mx, my), 10, Scalar(177, 0, 255), FILLED);
		else
			src[countdown] = Point2f(mx, my);

		if (countdown == 3) {
			matrix = getPerspectiveTransform(src, dst);
			warpPerspective(img, imgWarp, matrix, Point(w, h));
			imshow("Image Wrap", imgWarp);
			text = "0, 0";
		}

		imshow("W", img2);
		waitKey(1);
	}
}