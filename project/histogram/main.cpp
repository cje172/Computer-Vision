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

// 그레이스케일 영상의 히스토그램 구하기
Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);

	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0,256 };
	const float* ranges[] = { graylevel };

	calcHist(&img,  // 입력영상의 배열 또는 입력영상의 주소
		1,			// 입력영상의 개수
		channels,	// 히스토그래믈 구할 채널을 나타내는 정수형 배열 
		noArray(),  // 마스크 영상, Mat(0/noArray() => 입력영상 전체의 히스토그램
		hist,		// 출력 히스토그램, CV_32F(float) 깊이를 사용함
		dims,		// 출력 히스토그램의 차원
		histSize,	// 출력 히스토그램의 각 차원의 빈 개수를 나타내는 배열
		ranges		// 출력 히스토그램의 각 차원의 픽셀 값의 범위
					// * 등간격 히스토그램 => [최소값, 최대값)
					// * 비등간격 히스토그램 => 각 빈 값의 범위를 나타내는 histSize[i]+1 개의 실수로 구성

	);

	return hist;
}

// 그레이스케일 영상의 히스토그램 그래프 구하기
Mat getGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	double histMax;
	minMaxLoc(hist, 0 /* min value */, &histMax /* max value */);

	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		line(imgHist,
			Point(i, 100), //시작점
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), //끝점
			Scalar(0)	//선의 색깔
		);
	}
	return imgHist;
}

// 히스토그램 구성
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

// 히스토그램 스트레칭
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

// 히스토그램 평활화
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