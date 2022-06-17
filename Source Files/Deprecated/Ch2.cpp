#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, imgGray, imgBlur, imgCanny, imgDil;


vector<vector<Point>> contours, conPoly;
vector<Vec4i> hierarchy;
vector<Rect> boundRect;

int corners;
float aspRatio;


void getContours(Mat imgDil, Mat img) {

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	
	conPoly.resize(contours.size());
	
	string *objectType = new string[(int)contours.size()];
	boundRect.resize(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		if (contourArea(contours[i]) > 6000 && contourArea(contours[i]) < 20000)
		{
			approxPolyDP(
				contours[i],
				conPoly[i],
				0.02*arcLength(contours[i], true),
				true
			);

			boundRect[i] = boundingRect(contours[i]);

			if (conPoly[i].size() <= 8)
			{
				corners = (int)conPoly[i].size();

				if (corners == 3)
					objectType[i] = "Triangle";
				else if (corners == 4) {
					
					aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;

					if (aspRatio > 0.95 && aspRatio < 1.05)
						objectType[i] = "Square";
					else
						objectType[i] = "Rect";
				}
				else
					objectType[i] = "Circle";

				drawContours(img, contours, i, Scalar(255, 0, 200), 2);
				putText(
					img, 
					objectType[i], 
					{boundRect[i].x, boundRect[i].y - 10},
					FONT_HERSHEY_DUPLEX, 0.75,
					Scalar(0, 255, 0));
			}

		}
	}

	delete[] objectType;
}


void main() {

	VideoCapture cap(0);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));

	while (true) {
		cap.read(img);

		cvtColor(img, imgGray, COLOR_BGR2GRAY);
		GaussianBlur(imgGray, imgBlur, Size(9,9), 5, 0);
		Canny(imgBlur, imgCanny, 0, 75);
		dilate(imgCanny, imgDil, kernel);

		getContours(imgDil, img);

		imshow("image", img);

		waitKey(1);
	}

}