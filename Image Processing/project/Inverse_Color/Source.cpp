#include <stdio.h>

int main()
{
	int i, j;
	unsigned char OrgImg[256][256];

	// 디스크에서 영상데이터 읽기
	errno_t err;
	FILE *infile = NULL;
	FILE *outfile = NULL;

	err = fopen_s(&infile, "coin.raw", "rb");

	if (err != 0) // 성공적으로 열면 err은 0 반환
	{
		printf("File open error!!");
		return -1;
	}
	fread(OrgImg, sizeof(char), 256 * 256, infile);
	fclose(infile);

	// 역상계산을 위한 영상처리
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++)
		{
			OrgImg[i][j] = 255 - OrgImg[i][j];
		}
	}

	// 하드디스크에 영상데이터 쓰기
	err = fopen_s(&outfile, "coin_inv.raw", "wb");
	//fwrite(OrgImg, sizeof(char), 256 * 256, outfile);

	// Colorize
	unsigned char C1[256][256], C2[256][256];

	for (i = 0; i < 256; i++)
		for (j = 0; j < 256; j++)
		{
			C1[i][j] = 0;
			C2[i][j] = 0;
		}
	fwrite(C1, sizeof(unsigned char), 256 * 256, outfile);
	fwrite(OrgImg, sizeof(char), 256 * 256, outfile);
	fwrite(C2, sizeof(unsigned char), 256 * 256, outfile);
	fclose(outfile);

	return 0;
}