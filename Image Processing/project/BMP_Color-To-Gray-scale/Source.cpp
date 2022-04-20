#include <stdio.h>
#include <windows.h>
#define WIDTHBYTES(bits) (((bits)+31)/32*4)		// 영상의 가로줄은 4 바이트의 배수
#define BYTE unsigned char

int main()
{
	/*
	color영상을 gray-scale영상으로 변환하기
	- 입력 파일: “pshop256.bmp”(256 colors, indexed color mode)
	- 출력 파일: “pshop256_gray.bmp”
	- 방법: 컬러 화소의 Green 성분을 명도 값으로 취함
	*/

	errno_t err;
	FILE *infile;
	FILE *outfile;

	err = fopen_s(&infile, "pshop256.bmp", "rb");		// 입력할 파일을 오픈
	if (err != 0)
	{
		printf("File open error!!");
		return -1;
	}

	BITMAPFILEHEADER hf;	// 파일정보헤드 변수 선언
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, infile);	// 파일헤드를 읽음
	if (hf.bfType != 0x4D42) exit(1);
	BITMAPINFOHEADER hInfo;		// 영상정보헤드 변수 선언
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, infile);		// 영상헤드를 읽음

	// 256컬러 이하의 경우는 취급하지 않음
	if (hInfo.biBitCount < 8)
	{
		printf("Bad File format!!");
		return -1;
	}

	RGBQUAD *pRGB = new RGBQUAD[hInfo.biClrUsed];
	fread(pRGB, sizeof(RGBQUAD), hInfo.biClrUsed, infile);	// 팔레트를 파일에서 읽음


	// 영상데이터를 저장할 메모리 할당
	BYTE *lpImg = new BYTE[hInfo.biSizeImage];		// 저장할 영상메모리 할당
	fread(lpImg, sizeof(char), hInfo.biSizeImage, infile);
	fclose(infile);

	// 크기 계산, 메모리 할당
	int rwsize = WIDTHBYTES(hInfo.biBitCount * hInfo.biWidth);
	BYTE *lpOutImg = new BYTE[rwsize * hInfo.biHeight];
	int index, R, G, B, i, j;

	for (i = 0; i < hInfo.biHeight; i++)
	{
		for (j = 0; j < hInfo.biWidth; j++)
		{
			index = lpImg[i*rwsize + j];	// 영상데이터는 팔레트의 인덱스임
			G = pRGB[index].rgbGreen;	// G

			lpOutImg[i * rwsize + j] = (BYTE)G;	 // G값을 출력 화소의 명도 값으로 저장 
		}
	}

	// 그레이스케일 영상의 팔레트로 변경
	for (i = 0; i < 256; i++)
	{
		pRGB[i].rgbBlue = i;
		pRGB[i].rgbGreen = i;
		pRGB[i].rgbRed = i;
	}

	err = fopen_s(&outfile, "pshop256_gray.bmp", "wb");	// 출력할 파일을 오픈
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);
	fwrite(pRGB, sizeof(RGBQUAD), hInfo.biClrUsed, outfile);
	fwrite(lpOutImg, sizeof(char), rwsize * hInfo.biHeight, outfile);

	fclose(outfile);

	// 메모리 해제
	if (hInfo.biClrUsed != 0) delete[] pRGB;
	delete[] lpImg;
	delete[] lpOutImg;

	return 0;
}

