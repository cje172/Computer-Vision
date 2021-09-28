#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void PointOp();
void SizeOp();
void RectOp();
void RotatedRectOp();

int main()
{
	// 1. 영상을 화면에 출력
	cout << "Hello OpenCV " << CV_VERSION << endl;

	Mat img;
	img = imread("lenna.bmp");

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("image");
	imshow("image", img);

	namedWindow("image2", WINDOW_NORMAL);
	moveWindow("image2", 100, 100);
	imshow("image2", img);

	waitKey();

	// 2. 기본 자료형 클래스 활용
	// Point_, Size_, Rect_, RotatedRect 클래스

	PointOp();
	SizeOp();
	RectOp();
	RotatedRectOp();

	return 0;
}

void PointOp()
{
	Point pt1;
	pt1.x = 5; pt1.y = 10;
	Point pt2(10, 30);

	Point pt3 = pt1 + pt2;
	Point pt4 = pt1 * 2;
	int d1 = pt1.dot(pt2);
	bool b1 = (pt1 == pt2);

	cout << "pt1: " << pt1 << endl;
	cout << "pt2: " << pt2 << endl;

	cout << "dot product: " << d1 << endl;
	cout << "cross product: " << pt1.cross(pt2) << endl << endl;
}

void SizeOp()
{
	Size sz1, sz2(10, 20);
	sz1.width = 5; sz1.height = 10;

	Size sz3 = sz1 + sz2;
	Size sz4 = sz1 * 2;
	int area1 = sz4.area();

	cout << "sz3: " << sz3 << endl;
	cout << "sz4: " << sz4 << endl;

	cout << "area(sz4): " << area1 << endl << endl;
}

void RectOp()
{
	Rect rc1;
	Rect rc2(10, 10, 60, 40);

	Rect rc3 = rc1 + Size(50, 40);
	Rect rc4 = rc2 + Point(10, 10);

	Rect rc5 = rc3 & rc4;
	Rect rc6 = rc3 | rc4;

	cout << "rc5: " << rc5 << endl;
	cout << "rc6: " << rc6 << endl;

	cout << "rc3: " << rc3 << endl;
	cout << "rc4: " << rc4 << endl << endl;
}

void RotatedRectOp()
{
	RotatedRect rr1(Point2f(40, 30), Size2f(40, 20), 30.f);

	Point2f pts[4];
	rr1.points(pts);

	Rect br = rr1.boundingRect();

	for (int i = 0; i < 4; i++)
		cout << "pts[" << i << "]: " << pts[i] << endl;
	cout << "br: " << br << endl;
	Rect2f br_f = rr1.boundingRect2f();
	cout << "br_f: " << br_f << endl << endl;
}
