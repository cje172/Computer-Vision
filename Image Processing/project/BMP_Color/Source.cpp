#include <stdio.h>
#include <windows.h>
#include <math.h>
#define WIDTHBYTES(bits) (((bits)+31)/32*4)		// ������ �������� 4 ����Ʈ�� ���
#define BYTE unsigned char

int main()
{
	/*
		[color ��Ʈ�� ���� ����]
		- ��� ���� �̸�:��sample color image.bmp��
		- �÷� ���: true color �̹���
		- ������ ũ��: 256 x 256
		- ���� �߽�: (128, 128)
		- ���� ��� ���簢��
			ũ�� = 32 x 32, �÷� �� = black
		- �÷� ��
			������ < 40 : blue
			40 <= ������ < 80 : green
			80 <= ������ < 120 : red
			120 <= ������ : ��ο� ���(R = G = B = 200)
	*/

	errno_t err;
	FILE *outfile;
	double a, b;
	int i, j;

	// Color ��Ʈ�� ���� ����
	BITMAPFILEHEADER hf;	// ����������� ���� ����
	BITMAPINFOHEADER hInfo;		// ����������� ���� ����

	int rwsize = WIDTHBYTES(24 * 256);
	BYTE *OutImg = new BYTE[rwsize * 256];		// ������ ����޸� �Ҵ�
	BYTE *ColorImg = new BYTE[rwsize * 256];

	// ������� ����
	hInfo.biSize = sizeof(BITMAPINFOHEADER);
	hInfo.biWidth = 256;
	hInfo.biHeight = 256;
	hInfo.biPlanes = 1;  // ��Ʈ �÷��� ��
	hInfo.biBitCount = 24;  // �ȼ��� ��Ʈ��
	hInfo.biCompression = 0;  // ���� ����
	hInfo.biSizeImage = rwsize * 256;  // ������ ũ��
	hInfo.biXPelsPerMeter = 0;  // ���� �ػ�
	hInfo.biYPelsPerMeter = 0;  // ���� �ػ�
	hInfo.biClrUsed = hInfo.biClrImportant = 0; // �ȷ�Ʈ�� ���� ��,  ��Ʈ�� ǥ�ÿ� �ݵ�� �ʿ��� ���� ��

	// ������� ����
	hf.bfType = 0x4D42;
	hf.bfOffBits = 54;
	hf.bfSize = hf.bfOffBits + hInfo.biSizeImage;


	for (i = 0; i < hInfo.biHeight; i++)
		for (j = 0; j < hInfo.biWidth; j++)
		{
			a = pow((i - 128), 2);
			b = pow((j - 128), 2);

			// ���� �������� ���� �÷��� ����
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

			// ���� ��� ���簢��
			if ((i <= 32) && (j <= 32))
				ColorImg[i*rwsize + 3 * j + 2] = ColorImg[i*rwsize + 3 * j + 1] = ColorImg[i*rwsize + 3 * j] = 0;
		}


	// �Ųٷ� ����� �̹��� ������Ű��
	for (i = 0; i < hInfo.biHeight; i++)
	{
		for (j = 0; j < hInfo.biWidth; j++)
		{
			OutImg[i * rwsize + 3 * j + 2] = ColorImg[(hInfo.biHeight - i - 1) * rwsize + 3 * j + 2];
			OutImg[i * rwsize + 3 * j + 1] = ColorImg[(hInfo.biHeight - i - 1) * rwsize + 3 * j + 1];
			OutImg[i * rwsize + 3 * j] = ColorImg[(hInfo.biHeight - i - 1) * rwsize + 3 * j];
		}
	}


	// ���� ���
	err = fopen_s(&outfile, "sample color image.bmp", "wb");		// ����� ������ ����
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);		// ������� ���
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);		// ������� ���
	fwrite(OutImg, sizeof(char), hInfo.biSizeImage, outfile);	// �������� ���
	fclose(outfile);

	delete[] OutImg;
	delete[] ColorImg;

	return 0;
}