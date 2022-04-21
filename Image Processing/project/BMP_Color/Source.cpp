#include <stdio.h>
#include <windows.h>
#include <math.h>
#define WIDTHBYTES(bits) (((bits)+31)/32*4)		// 영상의 가로줄은 4 바이트의 배수
#define BYTE unsigned char

int main()
{
	/*
		[color 비트맵 영상 생성]
		- 출력 파일 이름:“sample color image.bmp”
		- 컬러 모드: true color 이미지
		- 영상의 크기: 256 x 256
		- 원의 중심: (128, 128)
		- 좌측 상단 정사각형
			크기 = 32 x 32, 컬러 값 = black
		- 컬러 값
			반지름 < 40 : blue
			40 <= 반지름 < 80 : green
			80 <= 반지름 < 120 : red
			120 <= 반지름 : 어두운 흰색(R = G = B = 200)
	*/

	errno_t err;
	FILE *outfile;
	double a, b;
	int i, j;

	// Color 비트맵 영상 생성
	BITMAPFILEHEADER hf;	// 파일정보헤드 변수 선언
	BITMAPINFOHEADER hInfo;		// 영상정보헤드 변수 선언

	int rwsize = WIDTHBYTES(24 * 256);
	BYTE *OutImg = new BYTE[rwsize * 256];		// 저장할 영상메모리 할당
	BYTE *ColorImg = new BYTE[rwsize * 256];

	// 영상헤드 설정
	hInfo.biSize = sizeof(BITMAPINFOHEADER);
	hInfo.biWidth = 256;
	hInfo.biHeight = 256;
	hInfo.biPlanes = 1;  // 비트 플레인 수
	hInfo.biBitCount = 24;  // 픽셀당 비트수
	hInfo.biCompression = 0;  // 압축 유무
	hInfo.biSizeImage = rwsize * 256;  // 영상의 크기
	hInfo.biXPelsPerMeter = 0;  // 가로 해상도
	hInfo.biYPelsPerMeter = 0;  // 세로 해상도
	hInfo.biClrUsed = hInfo.biClrImportant = 0; // 팔레트의 색깔 수,  비트맵 표시에 반드시 필요한 색깔 수

	// 파일헤드 설정
	hf.bfType = 0x4D42;
	hf.bfOffBits = 54;
	hf.bfSize = hf.bfOffBits + hInfo.biSizeImage;


	for (i = 0; i < hInfo.biHeight; i++)
		for (j = 0; j < hInfo.biWidth; j++)
		{
			a = pow((i - 128), 2);
			b = pow((j - 128), 2);

			// 원의 반지름에 따른 컬러값 설정
			if (a + b < pow(40, 2))
			{
				ColorImg[i*rwsize + 3 * j + 2] = 0;  // R
				ColorImg[i*rwsize + 3 * j + 1] = 0;  // G
				ColorImg[i*rwsize + 3 * j] = 255;  // B
			}
			else if (a + b < pow(80, 2))
			{
				ColorImg[i*rwsize + 3 * j + 2] = 0;  // R
				ColorImg[i*rwsize + 3 * j + 1] = 255;  // G
				ColorImg[i*rwsize + 3 * j] = 0;  // B
			}
			else if (a + b < pow(120, 2))
			{
				ColorImg[i*rwsize + 3 * j + 2] = 255;  // R
				ColorImg[i*rwsize + 3 * j + 1] = 0;  // G
				ColorImg[i*rwsize + 3 * j] = 0;  // B
			}
			else
			{
				ColorImg[i*rwsize + 3 * j + 2] = 200;  // R
				ColorImg[i*rwsize + 3 * j + 1] = 200;  // G
				ColorImg[i*rwsize + 3 * j] = 200;  // B
			}

			// 좌측 상단 정사각형
			if ((i <= 32) && (j <= 32))
				ColorImg[i*rwsize + 3 * j + 2] = ColorImg[i*rwsize + 3 * j + 1] = ColorImg[i*rwsize + 3 * j] = 0;
		}


	// 거꾸로 저장된 이미지 반전시키기
	for (i = 0; i < hInfo.biHeight; i++)
	{
		for (j = 0; j < hInfo.biWidth; j++)
		{
			OutImg[i * rwsize + 3 * j + 2] = ColorImg[(hInfo.biHeight - i - 1) * rwsize + 3 * j + 2];
			OutImg[i * rwsize + 3 * j + 1] = ColorImg[(hInfo.biHeight - i - 1) * rwsize + 3 * j + 1];
			OutImg[i * rwsize + 3 * j] = ColorImg[(hInfo.biHeight - i - 1) * rwsize + 3 * j];
		}
	}


	// 영상 출력
	err = fopen_s(&outfile, "sample color image.bmp", "wb");		// 출력할 파일을 오픈
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);		// 파일헤드 출력
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);		// 영상헤드 출력
	fwrite(OutImg, sizeof(char), hInfo.biSizeImage, outfile);	// 영상데이터 출력
	fclose(outfile);

	delete[] OutImg;
	delete[] ColorImg;

	return 0;
}