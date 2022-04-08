#include <stdio.h>
#include <math.h>

int main()
{
	/* 
		[gray - scale 영상 생성]
		- 출력 파일 이름 : “sample gray image.raw”
		- 영상의 크기 : 256 x 256
		- 원의 중심 : (128, 128)
		- 좌측 상단 정사각형
			크기 = 32 x 32, 명도 값 = 0
		- 명도 값
			반지름 < 40 : 0
			40 <= 반지름 < 80 : 64
			80 <= 반지름 < 120 : 128
			120 <= 반지름 : 255
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

			// 원의 반지름에 따른 명도값 설정
			if (a + b < pow(40, 2))
				OrgImg[i][j] = 0;
			else if (a + b < pow(80, 2))
				OrgImg[i][j] = 64;
			else if (a + b < pow(120, 2))
				OrgImg[i][j] = 128;
			else
				OrgImg[i][j] = 255;

			// 좌측 상단 정사각형
			if ((i <= 32) && (j <= 32))
				OrgImg[i][j] = 0;
		}
	}

	// 하드디스크에 영상데이터 쓰기
	err = fopen_s(&outfile, "sample gray image.raw", "wb");
	fwrite(OrgImg, sizeof(char), 256 * 256, outfile);
	fclose(outfile);

	return 0;
}