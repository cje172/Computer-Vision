#include <stdio.h>
#include <windows.h>
#define WIDTHBYTES(bits) (((bits)+31)/32*4)		// 영상의 가로줄은 4 바이트의 배수
#define BYTE unsigned char

int main()
{
	/* 흑백 BMP형식의 영상 입력 후 역상을 구해 디스크에 저장 */
	errno_t err;
	FILE *infile;
	FILE *outfile;

	err = fopen_s(&infile, "talent.bmp", "rb");		// 입력할 파일을 오픈
	if (err != 0)
	{
		printf("File open error!!");
		return -1;
	}

	// BMP 헤드정보의 입력
	BITMAPFILEHEADER hf;	// 파일정보헤드 변수 선언
	BITMAPINFOHEADER hInfo;		// 영상정보헤드 변수 선언
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, infile);	// 파일정보헤드 읽음
	if (hf.bfType != 0X4D42) exit(1);	// 파일 타입이 "BM"인지 검사
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, infile);		// 영상정보헤드 읽음
	if (hInfo.biBitCount != 8)	// 흑백 파일이 아닐 때
	{
		printf("Bad File format!!");
		return -1;
	}

	// 팔레트 정보의 입력
	RGBQUAD hRGB[256];		// 팔레트 정보를 위한 배열(흑백파일)
	fread(hRGB, sizeof(RGBQUAD), 256, infile);		// 팔레트 입력

	// 메모리 할당
	BYTE *lpImg = new BYTE[hInfo.biSizeImage];		// 저장할 영상메모리 할당
	fread(lpImg, sizeof(char), hInfo.biSizeImage, infile);		// 영상데이터 읽음
	fclose(infile);		// 오픈했던 파일 닫아줌

	int rwsize = WIDTHBYTES(hInfo.biBitCount*hInfo.biWidth);

	// 역상의 이미지 구하기
	for (int i = 0; i < hInfo.biHeight; i++)
	{
		for (int j = 0; j < hInfo.biWidth; j++)
		{
			lpImg[i*rwsize + j] = 255 - lpImg[i*rwsize + j];
		}
	}

	// 영상 출력
	err = fopen_s(&outfile, "OutImg.bmp", "wb");	// 출력할 파일을 오픈
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);		// 파일헤드 출력
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);		// 영상헤드 출력

	fwrite(hRGB, sizeof(RGBQUAD), 256, outfile);	// 팔레트 출력

	fwrite(lpImg, sizeof(char), hInfo.biSizeImage, outfile);	// 영상데이터 출력
	fclose(outfile);	// 파일 닫아줌

	// 메모리 해제
	delete[]lpImg;

	return 0;
}