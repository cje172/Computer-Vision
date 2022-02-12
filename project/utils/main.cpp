#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void mask_setTo();
void mask_copyTo();
void time_inverse();
void useful_func();

int main(void)
{
	//mask_setTo();
	//mask_copyTo();
	//time_inverse();
	//useful_func();
}

// 마스크 연산 - 마스크 영상을 이용한 픽셀 값 설정
void mask_setTo()
{
	Mat src = imread("lenna.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);

	if (src.empty() || mask.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	src.setTo(Scalar(0, 255, 255), mask);

	imshow("src", src);
	imshow("mask", mask);

	waitKey();
	destroyAllWindows();
}

// 마스크 연산 - 마스크 영상을 이용하여 픽셀 값의 일부분만 복사
void mask_copyTo()
{
	Mat src = imread("airplane.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);
	Mat dst = imread("field.bmp", IMREAD_COLOR);

	if (src.empty() || mask.empty() || dst.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("dst_before", dst);

	src.copyTo(dst, mask);

	imshow("src", src);
	imshow("dst", dst);
	imshow("mask", mask);

	waitKey(0);
	destroyAllWindows();
}

// 영상의 반전 시간 측정
void time_inverse()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	TickMeter tm;
	tm.start();

	int64 t1 = getTickCount();

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i);
		}
	}

	tm.stop();
	cout << "Image inverse took " << tm.getTimeMilli() << "ms." << endl;

	int64 t2 = getTickCount();
	cout << "Image inverse took " << (t2 - t1) * 1000 / getTickFrequency() << "ms. [using tick count]" << endl;
}

// 유용한 OpenCV 함수 사용
void useful_func()
{
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);
	cout << "Sum: " << (int)sum(img)[0] << endl;
	cout << "Mean: " << (int)mean(img)[0] << endl;

	Mat img2 = imread("lenna.bmp");
	cout << "Sum: " << sum(img2) << endl;
	cout << "Mean: " << mean(img2) << endl;

	double minVal, maxVal;
	Point minPos, maxPos;
	minMaxLoc(img, &minVal, &maxVal, &minPos, &maxPos);

	cout << "minVal: " << minVal << " at " << minPos << endl;
	cout << "maxVal: " << maxVal << " at " << maxPos << endl;

	Mat src = Mat_<float>({ 1,5 }, { -1.f, -0.5f, 0.f, 0.5f, 1.f });
	Mat dst;
	normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
	cout << "src: " << src << endl;
	cout << "dst(MinMax): " << dst << endl;

	normalize(src, dst, 1,
						0,
			NORM_L1, CV_32FC1);
	cout << "dst(NORM_L1): " << dst << endl;

	cout << "cvRound(2.5): " << cvRound(2.5) << endl;
	cout << "cvRound(2.51): " << cvRound(2.51) << endl;
	cout << "cvRound(3.4999): " << cvRound(3.4999) << endl;
	cout << "cvRound(3.5): " << cvRound(3.5) << endl;

	cout << "cvCeil(3.4): " << cvCeil(3.4) << endl;
	cout << "cvFloor(3.6): " << cvFloor(3.6) << endl;
}