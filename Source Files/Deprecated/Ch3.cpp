#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void main() {

	VideoCapture cap = VideoCapture(0);
	cap.set(CAP_PROP_AUTO_EXPOSURE, 0);
	cap.set(CAP_PROP_EXPOSURE, -6.0);
	Mat img, initial_img, diff_img, initial_gray, img_gray;

	int diff_high_cap = 160000, diff_low_cap = 95000;
	int frames = 0, covered_frames = 0, flushing_frames = 0, limit = 60;
	int flag = 0, difference = 0;
	string text;

	while (true) {
		cap.read(img);

		if (frames == 0)
			img.copyTo(initial_img);

		frames++;

		if (frames == limit){
			frames = 0;

			cvtColor(initial_img, initial_gray, COLOR_BGR2GRAY);
			cvtColor(img, img_gray, COLOR_BGR2GRAY);

			subtract(initial_gray, img_gray, diff_img);
			difference = countNonZero(diff_img);

			cout << difference << endl;

			if ((difference > diff_high_cap || difference < diff_low_cap) && flag == 0)
				flag = 1;
			else if ((difference > diff_high_cap || difference < diff_low_cap) && flag == 1)
				flag = 2;
			else if (difference < diff_high_cap && difference > diff_low_cap && flag == 2)
				flag = 0;
		}

		switch (flag)
		{
		case 1:
			text = "Someone";
			break;
		case 2:
			text = "Flushing";
			break;
		default:
			text = "Nothing";
			break;
		}

		putText(img, text, Point(5,30), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 0), 2);
		imshow("image", img);

		waitKey(1);
	}
}