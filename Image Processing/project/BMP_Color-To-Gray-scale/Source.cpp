#include <stdio.h>
#include <windows.h>
#define WIDTHBYTES(bits) (((bits)+31)/32*4)		// ������ �������� 4 ����Ʈ�� ���
#define BYTE unsigned char

int main()
{
	/*
	color������ gray-scale�������� ��ȯ�ϱ�
	- �Է� ����: ��pshop256.bmp��(256 colors, indexed color mode)
	- ��� ����: ��pshop256_gray.bmp��
	- ���: �÷� ȭ���� Green ������ �� ������ ����
	*/

	errno_t err;
	FILE *infile;
	FILE *outfile;

	err = fopen_s(&infile, "pshop256.bmp", "rb");		// �Է��� ������ ����
	if (err != 0)
	{
		printf("File open error!!");
		return -1;
	}

	BITMAPFILEHEADER hf;	// ����������� ���� ����
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, infile);	// ������带 ����
	if (hf.bfType != 0x4D42) exit(1);
	BITMAPINFOHEADER hInfo;		// ����������� ���� ����
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, infile);		// ������带 ����

	// 256�÷� ������ ���� ������� ����
	if (hInfo.biBitCount < 8)
	{
		printf("Bad File format!!");
		return -1;
	}

	RGBQUAD *pRGB = new RGBQUAD[hInfo.biClrUsed];
	fread(pRGB, sizeof(RGBQUAD), hInfo.biClrUsed, infile);	// �ȷ�Ʈ�� ���Ͽ��� ����


	// �������͸� ������ �޸� �Ҵ�
	BYTE *lpImg = new BYTE[hInfo.biSizeImage];		// ������ ����޸� �Ҵ�
	fread(lpImg, sizeof(char), hInfo.biSizeImage, infile);
	fclose(infile);

	// ũ�� ���, �޸� �Ҵ�
	int rwsize = WIDTHBYTES(hInfo.biBitCount * hInfo.biWidth);
	BYTE *lpOutImg = new BYTE[rwsize * hInfo.biHeight];
	int index, R, G, B, i, j;

	for (i = 0; i < hInfo.biHeight; i++)
	{
		for (j = 0; j < hInfo.biWidth; j++)
		{
			index = lpImg[i*rwsize + j];	// �������ʹ� �ȷ�Ʈ�� �ε�����
			G = pRGB[index].rgbGreen;	// G

			lpOutImg[i * rwsize + j] = (BYTE)G;	 // G���� ��� ȭ���� �� ������ ���� 
		}
	}

	// �׷��̽����� ������ �ȷ�Ʈ�� ����
	for (i = 0; i < 256; i++)
	{
		pRGB[i].rgbBlue = i;
		pRGB[i].rgbGreen = i;
		pRGB[i].rgbRed = i;
	}

	err = fopen_s(&outfile, "pshop256_gray.bmp", "wb");	// ����� ������ ����
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);
	fwrite(pRGB, sizeof(RGBQUAD), hInfo.biClrUsed, outfile);
	fwrite(lpOutImg, sizeof(char), rwsize * hInfo.biHeight, outfile);

	fclose(outfile);

	// �޸� ����
	if (hInfo.biClrUsed != 0) delete[] pRGB;
	delete[] lpImg;
	delete[] lpOutImg;

	return 0;
}

