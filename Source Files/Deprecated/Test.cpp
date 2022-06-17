#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void main() {

	/*
	VideoCapture cap(0);
	Mat img;

	cap.read(img);

	Mat frame(img.rows, img.cols*2, CV_8UC3);
	Mat imgGray3(img.rows, img.cols, CV_8UC3);

	int from_to[] = {0,0, 0,1, 0,2};

	while (true) {
		cap.read(img);

		mixChannels(&img, 1, &imgGray3, 1, from_to, 3);

		img.copyTo(frame(Rect(0, 0, img.cols, img.rows)));
		imgGray3.copyTo(frame(Rect(img.cols, 0, imgGray3.cols, imgGray3.rows)));

		imshow("image", frame);

		waitKey(1);
	}
	*/

	VideoCapture cap(0);
	Mat img, crop;

	CascadeClassifier faceCascade;
	faceCascade.load("Resources/hc.xml");

	if (faceCascade.empty()) cout << "Empty XML file" << endl;

	vector<Rect> faces;

	while (true) {
		cap.read(img);

		faceCascade.detectMultiScale(img, faces, 1.1, 10);

		if (faces.empty()) continue;

		for (int i = 0; i < faces.size(); i++)
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 0), 2);

		crop = img(
			Rect(
				faces[0].tl(),
				faces[0].br()));

		imshow("image", crop);

		waitKey(1);
	}

}