#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void contrast1();
void contrast2();

int main(void)
{
	//contrast1();  //기본적인 영상의 명암비 증가 But, 영상의 밝기 쉽게 포화 단점
	//contrast2();  //효과적인 영상의 명암비 조절 방법 - 중간값 128 기준, 평균 밝기 기준

	return 0;
}

void contrast1()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	float s = 2.f;
	Mat dst = s * src;

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

void contrast2()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;

	imshow("src", src);
	imshow("dst", dst);

	int avg = cvRound(mean(src)[0]);
	cout << avg << endl;
	Mat dst2 = 2 * (src - avg) + avg;
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}