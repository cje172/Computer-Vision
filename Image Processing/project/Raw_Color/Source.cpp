#include <stdio.h>
#include <math.h>

int main()
{
	/*
		[color 영상 생성]
		- 출력 파일 이름: “sample color image.raw”
		- 영상의 크기: 256 x 256
		- 원의 중심: (128, 128)
		- 좌측 상단 정사각형
			크기 = 32 x 32, 컬러 값 = black
		- 컬러 값
			반지름 < 40: blue
			40 <= 반지름 < 80 : green
			80 <= 반지름 < 120 : red
			120 <= 반지름: white
		- "planar format"으로 저장 
			즉, R/G/B image plate 순서로 저장
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

			// 원의 반지름에 따른 컬러값 설정
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

			// 좌측 상단 정사각형
			if ((i <= 32) && (j <= 32))
				R[i][j] = G[i][j] = B[i][j] = 0;
		}

	// 하드디스크에 영상데이터 쓰기
	err = fopen_s(&outfile, "sample color image.raw", "wb");

	fwrite(R, sizeof(unsigned char), 256 * 256, outfile);
	fwrite(G, sizeof(char), 256 * 256, outfile);
	fwrite(B, sizeof(unsigned char), 256 * 256, outfile);
	fclose(outfile);

	return 0;
}