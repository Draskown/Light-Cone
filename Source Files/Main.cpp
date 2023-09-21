#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "Includes/Circles.h"
#include "Includes/Linear.h"
#include "Includes/Mask.h"

#include "Includes/Palette.h"

using namespace std;
using namespace cv;

#define LOG(x) cout << "\n" + to_string(x) + "\n" << endl

string FILENAME = "Resources/Video.mp4";

void main() {
	VideoCapture cap;
	cap.open(FILENAME);
	Mat image;

	//linear(cap, image, FILENAME);
	//mask(image);
	//circles();

	palette(cap, image);

	cap.release();
	destroyAllWindows();
}