#include <stdio.h>

int main()
{
	int i, j;
	unsigned char OrgImg[256][256];

	// 디스크에서 영상데이터 읽기
	errno_t err;
	FILE *infile = NULL;
	FILE *outfile = NULL;

	err = fopen_s(&infile, "Lenna.raw", "rb");

	if (err != 0) // 성공적으로 열면 err은 0 반환
	{
		printf("File open error!!");
		return -1;
	}
	fread(OrgImg, sizeof(char), 256 * 256, infile);
	fclose(infile);

	// Solarize
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++)
		{
			if (OrgImg[i][j] > 128)
			{
				OrgImg[i][j] = 510 - 2 * OrgImg[i][j];
			}
		}
	}

	// 하드디스크에 영상데이터 쓰기
	err = fopen_s(&outfile, "solarized image.raw", "wb");
	fwrite(OrgImg, sizeof(char), 256 * 256, outfile);
	fclose(outfile);

	return 0;
}