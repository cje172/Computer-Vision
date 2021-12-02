#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void MatOp1();
void MatOp2();
void MatOp3();
void MatOp4();
void MatOp5();
void MatOp6();
void MatOp7();

int main()
{
	// MatOp1();
	// MatOp2();
	// MatOp3();
	// MatOp4();
	// MatOp5();
	// MatOp6();
	// MatOp7();

	return 0;
}

void MatOp1()
{
	Mat img1;

	Mat img2(480, 640, CV_8UC1);
	Mat img3(480, 640, CV_8UC3);
	Mat img4(Size(640, 480), CV_8UC3);

	Mat img5(480, 640, CV_8UC1, Scalar(128));
	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255));

	imshow("image5", img5);
	imshow("image6", img6);
	waitKey();

	Mat mat1 = Mat::zeros(3, 3, CV_32SC1);
	Mat mat2 = Mat::ones(3, 3, CV_32FC1);
	Mat mat3 = Mat::eye(3, 3, CV_32FC1);

	cout << "mat1: \n" << mat1 << endl;
	cout << "mat2: \n" << mat2 << endl;
	cout << "mat3: \n" << mat3 << endl;

	float data[] = { 1,2,3,4,5,6 };
	Mat mat4(2, 3, CV_32FC1, data);

	cout << "mat4(1): \n" << mat4 << endl;

	Mat_<float> mat5_(2, 3);
	mat5_ << 1, 2, 3, 4, 5, 6;
	Mat mat5 = mat5_;
	cout << "mat5_: \n" << mat5_ << endl;
	cout << "mat5(1): \n" << mat5 << endl;

	mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
	Mat mat6 = Mat_<float>({ 2,3 }, { 1,2,3,4,5,6 });

	cout << "mat5(2): \n" << mat5 << endl;
	cout << "mat6: \n" << mat6 << endl;

	mat4.create(5, 5, CV_8UC3);
	mat5.create(4, 4, CV_32FC1);

	mat4 = Scalar(255, 0, 0);
	mat5.setTo(1.f);

	cout << "mat4(2): \n" << mat4 << endl;
	cout << "mat5(3): \n" << mat5 << endl << endl;

	destroyAllWindows();
}

void MatOp2()
{
	Mat img1 = imread("dog.bmp");

	Mat img2 = img1; // shallow copy
	Mat img3;
	img3 = img1; // shallow copy

	Mat img4 = img1.clone(); // deep copy
	Mat img5;
	img1.copyTo(img5); // deep copy

	img1.setTo(Scalar(0, 255, 255)); // yellow

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);
	imshow("img5", img5);

	waitKey();
	destroyAllWindows();
}

void MatOp3()
{
	Mat img1 = imread("cat.bmp");

	if (img1.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat img2 = img1(Rect(220, 120, 340, 240));
	Mat img3 = img1(Rect(220, 120, 340, 240)).clone();

	Mat img4 = img1(Range(120, 120 + 240), Range(220, 220 + 340));
	imshow("img4_before", img4);

	img2 = ~img2;

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);

	imshow("img4_after", img4);
	imshow("img5", img1.rowRange(100, 200));
	imshow("img6", img1.colRange(400, 600));

	waitKey();
	destroyAllWindows();
}

void MatOp4()
{
	Mat mat1 = Mat::zeros(3, 4, CV_8UC1);

	for (int j = 0; j < mat1.rows; j++) {
		for (int i = 0; i < mat1.cols; i++) {
			mat1.at<uchar>(j, i)++;
		}
	}

	uchar& v1 = mat1.at<uchar>(1, 2);
	v1 = 5;
	mat1.at<uchar>(1, 3) = 7;
	cout << "mat1(at): \n" << mat1 << endl;

	for (int j = 0; j < mat1.rows; j++) {
		uchar* p = mat1.ptr<uchar>(j);
		for (int i = 0; i < mat1.cols; i++) {
			p[i]++;
		}
	}

	for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it) {
		(*it)++;
	}

	cout << "mat1(final):\n" << mat1 << endl << endl;
}

void MatOp5()
{
	Mat img1 = imread("lenna.bmp");

	cout << "Width: " << img1.cols << endl;
	cout << "Height: " << img1.rows << endl;
	cout << "Channels: " << img1.channels() << endl;

	cout << "Depth: " << img1.depth() << endl;
	cout << "ElemSize: " << img1.elemSize() << " bytes" << endl;
	cout << "ElemSize1: " << img1.elemSize1() << " bytes" << endl;
	cout << "Size: " << img1.size << " or " << img1.size() << endl;
	cout << "Size[0]: " << img1.size[0] << ", Size[1]: " << img1.size[1] << endl;
	cout << "Total: " << img1.total() << " = " << img1.size[0] << "x" << img1.size[1] << endl;

	if (img1.type() == CV_8UC1)
		cout << "img1 is a grayscale image." << endl;
	else if (img1.type() == CV_8UC3)
		cout << "img1 is a truecolor image." << endl;

	float data[] = { 2.f, 1.414f, 3.f, 1.732f };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl << endl;
}

void MatOp6()
{
	float data[] = { 1,1,2,3 };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl;

	Mat mat2 = mat1.inv();
	cout << "mat2:\n" << mat2 << endl;

	cout << "mat1.t():\n" << mat1.t() << endl;
	cout << "mat1 + 3:\n" << mat1 + 3 << endl;
	cout << "mat1 + mat2:\n" << mat1 + mat2 << endl;
	cout << "mat1 * mat2:\n" << mat1 * mat2 << endl;

	cout << "mat1 + Scalar(3):\n" << mat1 + Scalar(3) << endl;
	cout << "mat1 * 3:\n" << mat1 * 3 << endl;
	cout << "mat1 / mat2:\n" << mat1 / mat2 << endl;
	cout << "4 / mat1:\n" << 4 / mat1 << endl;
	cout << "mat1.mul(mat2):\n" << mat1.mul(mat2) << endl;

	float data2[] = { 1,2,3,4,5,6 };
	Mat mat3(2, 3, CV_32FC1, data2);
	cout << "mat3:\n" << mat3 << endl;
	cout << "mat3(pseudoinverse by SVD):\n" << mat3.inv(DECOMP_SVD) << endl;
	cout << "pseudoinverse(left inverse)" << endl;
	cout << (((mat3.t()) * mat3).inv()) * (mat3.t()) << endl;
	cout << "pseudoinverse(right inverse)" << endl;
	cout << (mat3.t()) * ((mat3) * (mat3.t())).inv() << endl << endl;
}

void MatOp7()
{
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);

	Mat img1f;
	img1.convertTo(img1f, CV_32FC1);

	Mat img2f;
	img1.convertTo(img2f, CV_32FC1, 1.0 / 255);
	imshow("img1", img1);
	imshow("img1f", img1f);
	imshow("img2f", img2f);
	waitKey();

	uchar data1[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	Mat mat1(3, 4, CV_8UC1, data1);
	Mat mat2 = mat1.reshape(0, 1);

	cout << "mat1:\n" << mat1 << endl;
	cout << "mat2:\n" << mat2 << endl;

	mat2.at<uchar>(0, 2) = 77;
	cout << "mat1(at):\n" << mat1 << endl;
	cout << "mat2(at):\n" << mat2 << endl;

	Mat mat2_1 = mat1.reshape(3, 2);
	cout << "mat2_1:\n" << mat2_1 << endl;
	cout << "mat2_1(channels): " << mat2_1.channels() << endl;
	cout << "mat2_1(size): " << mat2_1.size() << endl;

	mat1.resize(5, 100);
	cout << "mat1:\n" << mat1 << endl;

	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;
	mat1.push_back(mat3);
	cout << "mat1:\n" << mat1 << endl;

	Mat mat3_1 = Mat::ones(3, 4, CV_8UC1) * 128;
	mat1.push_back(mat3_1);
	cout << "mat1:\n" << mat1 << endl;

	Mat mat4(12, 1, CV_8UC1, data1);
	cout << "mat4:\n" << mat4 << endl;
	vector<uchar>mat3_2(2, 50);
	mat4.push_back(mat3_2);
	cout << "mat4:\n" << mat4 << endl;
	mat4.pop_back(3);
	cout << "mat4:\n" << mat4 << endl;

	destroyAllWindows();
}