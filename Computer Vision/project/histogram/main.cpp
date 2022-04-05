#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat calcGrayHist(const Mat& img);
Mat getGrayHistImage(const Mat& hist);

void histogram_plot();

void histogram_stretching();
void histogram_equalization();

int main(void)
{
	//histogram_plot();

	//histogram_stretching();
	//histogram_equalization();

	return 0;
}

// �׷��̽����� ������ ������׷� ���ϱ�
Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);

	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0,256 };
	const float* ranges[] = { graylevel };

	calcHist(&img,  // �Է¿����� �迭 �Ǵ� �Է¿����� �ּ�
		1,			// �Է¿����� ����
		channels,	// ������׷��� ���� ä���� ��Ÿ���� ������ �迭 
		noArray(),  // ����ũ ����, Mat(0/noArray() => �Է¿��� ��ü�� ������׷�
		hist,		// ��� ������׷�, CV_32F(float) ���̸� �����
		dims,		// ��� ������׷��� ����
		histSize,	// ��� ������׷��� �� ������ �� ������ ��Ÿ���� �迭
		ranges		// ��� ������׷��� �� ������ �ȼ� ���� ����
					// * ��� ������׷� => [�ּҰ�, �ִ밪)
					// * ���� ������׷� => �� �� ���� ������ ��Ÿ���� histSize[i]+1 ���� �Ǽ��� ����

	);

	return hist;
}

// �׷��̽����� ������ ������׷� �׷��� ���ϱ�
Mat getGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	double histMax;
	minMaxLoc(hist, 0 /* min value */, &histMax /* max value */);

	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		line(imgHist,
			Point(i, 100), //������
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), //����
			Scalar(0)	//���� ����
		);
	}
	return imgHist;
}

// ������׷� ����
void histogram_plot()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat hist = calcGrayHist(src);
	Mat hist_img = getGrayHistImage(hist);

	imshow("src", src);
	imshow("srcHist", hist_img);

	waitKey();
	destroyAllWindows();
}

// ������׷� ��Ʈ��Ī
void histogram_stretching()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);

	Mat dst = (src - gmin) * 255 / (gmax - gmin);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));
	
	waitKey();
	destroyAllWindows();
}

// ������׷� ��Ȱȭ
void histogram_equalization()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst;
	equalizeHist(src, dst);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}