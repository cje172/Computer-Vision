#include <stdio.h>
#include <math.h>

int main()
{
	/* 
		[gray - scale ���� ����]
		- ��� ���� �̸� : ��sample gray image.raw��
		- ������ ũ�� : 256 x 256
		- ���� �߽� : (128, 128)
		- ���� ��� ���簢��
			ũ�� = 32 x 32, �� �� = 0
		- �� ��
			������ < 40 : 0
			40 <= ������ < 80 : 64
			80 <= ������ < 120 : 128
			120 <= ������ : 255
	*/

	int i, j;
	double a, b;
	unsigned char OrgImg[256][256];

	errno_t err;
	FILE *outfile = NULL;

	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++)
		{
			a = pow((i - 128), 2);
			b = pow((j - 128), 2);

			// ���� �������� ���� ���� ����
			if (a + b < pow(40, 2))
				OrgImg[i][j] = 0;
			else if (a + b < pow(80, 2))
				OrgImg[i][j] = 64;
			else if (a + b < pow(120, 2))
				OrgImg[i][j] = 128;
			else
				OrgImg[i][j] = 255;

			// ���� ��� ���簢��
			if ((i <= 32) && (j <= 32))
				OrgImg[i][j] = 0;
		}
	}

	// �ϵ��ũ�� �������� ����
	err = fopen_s(&outfile, "sample gray image.raw", "wb");
	fwrite(OrgImg, sizeof(char), 256 * 256, outfile);
	fclose(outfile);

	return 0;
}