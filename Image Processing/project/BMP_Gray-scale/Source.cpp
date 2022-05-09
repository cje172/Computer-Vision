#include <stdio.h>
#include <windows.h>
#include <math.h>
#define WIDTHBYTES(bits) (((bits)+31)/32*4)		// ������ �������� 4 ����Ʈ�� ���
#define BYTE unsigned char

int main()
{
	// Gray-scale ��Ʈ�� ���� ����
	errno_t err;
	FILE *outfile;
	double a, b;
	int i, j;

	BITMAPFILEHEADER hf;  // ����������� ���� ����
	BITMAPINFOHEADER hInfo;  // ����������� ���� ����
	RGBQUAD hRGB[256];  // �ȷ�Ʈ ������ ���� �迭(�������)

	int rwsize = WIDTHBYTES(8 * 256);
	BYTE *OutImg = new BYTE[rwsize * 256];  // ������ ����޸� �Ҵ�
	BYTE *GrayImg = new BYTE[rwsize * 256];

	// ������� ����
	hInfo.biSize = sizeof(BITMAPINFOHEADER);
	hInfo.biWidth = 256;
	hInfo.biHeight = 256;
	hInfo.biPlanes = 1;  // ��Ʈ �÷��� ��
	hInfo.biBitCount = 8;  // �ȼ��� ��Ʈ��
	hInfo.biCompression = 0;  // ���� ����
	hInfo.biSizeImage = rwsize * 256;  // ������ ũ��
	hInfo.biXPelsPerMeter = 0;  // ���� �ػ�
	hInfo.biYPelsPerMeter = 0;  // ���� �ػ�
	hInfo.biClrUsed = hInfo.biClrImportant = 0;  // �ȷ�Ʈ�� ���� ��, ��Ʈ�� ǥ�ÿ� �ݵ�� �ʿ��� ���� ��

	// ������� ����
	hf.bfType = 0x4D42;
	hf.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(hRGB);
	hf.bfSize = hf.bfOffBits + hInfo.biSizeImage;

	// �׷��̽����� ������ �ȷ�Ʈ ����
	for (int i = 0; i < 256; i++)
	{
		hRGB[i].rgbBlue = i;
		hRGB[i].rgbGreen = i;
		hRGB[i].rgbRed = i;
	}


	// ���� �������� ���� ���� ����
	for (i = 0; i < hInfo.biHeight; i++)
	{
		for (j = 0; j < hInfo.biWidth; j++)
		{
			a = pow((i - 128), 2);
			b = pow((j - 128), 2);

			if (a + b < pow(40, 2))
				GrayImg[i * rwsize + j] = 0;
			else if (a + b < pow(80, 2))
				GrayImg[i * rwsize + j] = 64;
			else if (a + b < pow(120, 2))
				GrayImg[i * rwsize + j] = 128;
			else
				GrayImg[i * rwsize + j] = 200;

			// ���� ��� ���簢��
			if ((i <= 32) && (j <= 32))
				GrayImg[i * rwsize + j] = 0;
		}
	}

	// �Ųٷ� ����� �̹��� ������Ű��
	for (i = 0; i < hInfo.biHeight; i++)
	{
		for (j = 0; j < hInfo.biWidth; j++)
		{
			OutImg[i * hInfo.biWidth + j] = GrayImg[(hInfo.biHeight - i - 1) * rwsize + j];
		}
	}

	// ���� ���
	err = fopen_s(&outfile, "sample gray image.bmp", "wb");  // ����� ������ ����
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);  // ������� ���
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);  // ������� ���
	fwrite(hRGB, sizeof(RGBQUAD), 256, outfile);  // �ȷ�Ʈ ���
	fwrite(OutImg, sizeof(char), hInfo.biSizeImage, outfile);  // �������� ���
	fclose(outfile);

	delete[] OutImg;
	delete[] GrayImg;

	return 0;
}