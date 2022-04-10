#include <stdio.h>
#include <windows.h>
#define WIDTHBYTES(bits) (((bits)+31)/32*4)		// ������ �������� 4 ����Ʈ�� ���
#define BYTE unsigned char

int main()
{
	/* ��� BMP������ ���� �Է� �� ������ ���� ��ũ�� ���� */
	errno_t err;
	FILE *infile;
	FILE *outfile;

	err = fopen_s(&infile, "talent.bmp", "rb");		// �Է��� ������ ����
	if (err != 0)
	{
		printf("File open error!!");
		return -1;
	}

	// BMP ��������� �Է�
	BITMAPFILEHEADER hf;	// ����������� ���� ����
	BITMAPINFOHEADER hInfo;		// ����������� ���� ����
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, infile);	// ����������� ����
	if (hf.bfType != 0X4D42) exit(1);	// ���� Ÿ���� "BM"���� �˻�
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, infile);		// ����������� ����
	if (hInfo.biBitCount != 8)	// ��� ������ �ƴ� ��
	{
		printf("Bad File format!!");
		return -1;
	}

	// �ȷ�Ʈ ������ �Է�
	RGBQUAD hRGB[256];		// �ȷ�Ʈ ������ ���� �迭(�������)
	fread(hRGB, sizeof(RGBQUAD), 256, infile);		// �ȷ�Ʈ �Է�

	// �޸� �Ҵ�
	BYTE *lpImg = new BYTE[hInfo.biSizeImage];		// ������ ����޸� �Ҵ�
	fread(lpImg, sizeof(char), hInfo.biSizeImage, infile);		// �������� ����
	fclose(infile);		// �����ߴ� ���� �ݾ���

	int rwsize = WIDTHBYTES(hInfo.biBitCount*hInfo.biWidth);

	// ������ �̹��� ���ϱ�
	for (int i = 0; i < hInfo.biHeight; i++)
	{
		for (int j = 0; j < hInfo.biWidth; j++)
		{
			lpImg[i*rwsize + j] = 255 - lpImg[i*rwsize + j];
		}
	}

	// ���� ���
	err = fopen_s(&outfile, "OutImg.bmp", "wb");	// ����� ������ ����
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);		// ������� ���
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);		// ������� ���

	fwrite(hRGB, sizeof(RGBQUAD), 256, outfile);	// �ȷ�Ʈ ���

	fwrite(lpImg, sizeof(char), hInfo.biSizeImage, outfile);	// �������� ���
	fclose(outfile);	// ���� �ݾ���

	// �޸� ����
	delete[]lpImg;

	return 0;
}