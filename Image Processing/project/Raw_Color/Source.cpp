#include <stdio.h>
#include <math.h>

int main()
{
	/*
		[color ���� ����]
		- ��� ���� �̸�: ��sample color image.raw��
		- ������ ũ��: 256 x 256
		- ���� �߽�: (128, 128)
		- ���� ��� ���簢��
			ũ�� = 32 x 32, �÷� �� = black
		- �÷� ��
			������ < 40: blue
			40 <= ������ < 80 : green
			80 <= ������ < 120 : red
			120 <= ������: white
		- "planar format"���� ���� 
			��, R/G/B image plate ������ ����
	*/

	int i, j;
	double a, b;
	unsigned char R[256][256], G[256][256], B[256][256];

	errno_t err;
	FILE *outfile = NULL;

	for (i = 0; i < 256; i++)
		for (j = 0; j < 256; j++)
		{
			a = pow((i - 128), 2);
			b = pow((j - 128), 2);

			// ���� �������� ���� �÷��� ����
			if (a + b < pow(40, 2))
			{
				R[i][j] = 0;
				G[i][j] = 0;
				B[i][j] = 255;
			}
			else if (a + b < pow(80, 2))
			{
				R[i][j] = 0;
				G[i][j] = 255;
				B[i][j] = 0;
			}
			else if (a + b < pow(120, 2))
			{
				R[i][j] = 255;
				G[i][j] = 0;
				B[i][j] = 0;

			}
			else
			{
				R[i][j] = 255;
				G[i][j] = 255;
				B[i][j] = 255;
			}

			// ���� ��� ���簢��
			if ((i <= 32) && (j <= 32))
				R[i][j] = G[i][j] = B[i][j] = 0;
		}

	// �ϵ��ũ�� �������� ����
	err = fopen_s(&outfile, "sample color image.raw", "wb");

	fwrite(R, sizeof(unsigned char), 256 * 256, outfile);
	fwrite(G, sizeof(char), 256 * 256, outfile);
	fwrite(B, sizeof(unsigned char), 256 * 256, outfile);
	fclose(outfile);

	return 0;
}