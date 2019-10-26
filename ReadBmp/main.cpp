#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <wchar.h>

struct my_RGB
{
	BYTE r;
	BYTE g;
	BYTE b;
};

void main()
{
	int number = 0;

	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	FILE *p_source;
	FILE *p_out;
	my_RGB img[27][80];
	char filename[20];
	char fileout[30];
	p_out = fopen("text.txt", "w");

	while (1)
	{
		memset(filename, 0, sizeof(filename));
		if (number < 10)
		{
			sprintf(filename, "BadApple_0000%d.bmp", number);
		}
		else if (number < 100)
		{
			sprintf(filename, "BadApple_000%d.bmp", number);
		}
		else if (number < 1000)
		{
			sprintf(filename, "BadApple_00%d.bmp", number);
		}
		else if (number < 10000)
		{
			sprintf(filename, "BadApple_0%d.bmp", number);
		}
		//sprintf(fileout, "text\\BadText_%d.txt", number);

		p_source = fopen(filename, "rb");
		
		if (p_source == NULL)
		{
			break;
		}

		fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, p_source);
		fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, p_source);

		int size = infoHeader.biWidth*infoHeader.biHeight;
		fread(img, sizeof(my_RGB), size, p_source);
		//fread(NULL, 2, 1, p_source);
		int gray = 0;

		for (int i = 26; i >= 0; i--)
		{
			for (int j = 0; j < 80; j++)
			{
				gray = (img[i][j].b + img[i][j].g + img[i][j].r) / 3;
				if (gray < 32)
				{
					fprintf(p_out, " ");
					//printf(" ");
				}
				else if (gray < 64)
				{
					fprintf(p_out, "-");
					//printf(";");
				}
				else if (gray < 96)
				{
					fprintf(p_out, "=");
					//printf("-");
				}
				else if (gray < 128)
				{
					fprintf(p_out, ";");
					//printf("=");
				}
				else if (gray < 160)
				{
					fprintf(p_out, "Z");
					//printf("Z");
				}
				else if (gray < 192)
				{
					fprintf(p_out, "N");
					//printf("N");
				}
				else if (gray < 224)
				{
					fprintf(p_out, "M");
					//printf("M");
				}
				else if (gray < 256)
				{
					fprintf(p_out, "$");
					//printf("$");
				}
				else
				{
					fprintf(p_out, "$");
					//printf("$");
				}
			}
			fprintf(p_out, "\n");
		}
		printf("%d\n", number);

		fclose(p_source);
		

		number++;
	}
	fclose(p_out);
}