#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img1 = imread("lenna.bmp", IMREAD_REDUCED_COLOR_2);

	imshow("img1_before", img1);

	Mat img2 = img1.clone();

	Mat img3 = img2(Rect(0, 0, 256, 25));
	Mat img4 = img2(Rect(0, 256 - 25, 256, 25));
	Mat img5 = img2(Rect(0, 0, 25, 256));
	Mat img6 = img2(Rect(256 - 25, 0, 25, 256));

	Mat img7 = img2(Rect(50, 50, 156, 25));
	Mat img8 = img2(Rect(50, 256 - 75, 156, 25));
	Mat img9 = img2(Rect(50, 50, 25, 156));
	Mat img10 = img2(Rect(256 - 75, 50, 25, 156));

	img3.setTo(Scalar(0, 255, 0));
	img4.setTo(Scalar(0, 255, 0));
	img5.setTo(Scalar(0, 255, 0));
	img6.setTo(Scalar(0, 255, 0));

	img7.setTo(Scalar(255, 0, 0));
	img8.setTo(Scalar(255, 0, 0));
	img9.setTo(Scalar(255, 0, 0));
	img10.setTo(Scalar(255, 0, 0));

	imshow("img1_after", img2);

	waitKey();
	destroyAllWindows();

	return 0;
}