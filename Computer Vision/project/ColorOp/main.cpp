#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void color_op();
void color_inverse();
void color_grayscale();
void color_split();

int main(void)
{
	//color_op();
	//color_inverse();
	//color_grayscale();
	//color_split();
	
	return 0;
}

// 컬러 영상의 픽셀 값 참조
void color_op()
{
	Mat img = imread("butterfly.jpg", IMREAD_COLOR);

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Vec3b& pixel = img.at<Vec3b>(0 /* y */, 0 /* x */);
	uchar b1 = pixel[0];
	uchar g1 = pixel[1];
	uchar r1 = pixel[2];

	cout << "at (0,0): " << pixel << " " << (int)b1 << " " << (int)g1 << " " << (int)r1 << endl;

	Vec3b* ptr = img.ptr<Vec3b>(0 /* y */);
	uchar b2 = ptr[0][0];
	uchar g2 = ptr[0][1];
	uchar r2 = ptr[0][2];

	cout << "ptr (0,0): " << *ptr << " " << (int)b2 << " " << (int)g2 << " " << (int)r2 << endl;
}

// 컬러 영상의 픽셀 값 반전
void color_inverse()
{
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);
			Vec3b& p2 = dst.at<Vec3b>(j, i);

			p2[0] = 255 - p1[0]; // B
			p2[1] = 255 - p1[1]; // G
			p2[2] = 255 - p1[2]; // R
		}
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

// 컬러 영상을 그레이스케일 영상으로 변환
void color_grayscale()
{
	Mat src = imread("butterfly.jpg");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);

	imshow("src", src);
	imshow("dst", dst);

	Mat dst2 = imread("butterfly.jpg", IMREAD_GRAYSCALE);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}

// BGR 컬러 영상의 채널 나누기
void color_split()
{
	Mat src = imread("candies.png");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	imshow("src", src);
	imshow("B_plane", bgr_planes[0]);
	imshow("G_plane", bgr_planes[1]);
	imshow("R_plane", bgr_planes[2]);

	waitKey();
	destroyAllWindows();
}