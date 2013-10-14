#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////
//* define input picture paragram
///////////////////////////////////////////////
#define RAW_FILE "./pic.raw"
#define BMP_FILE "./pic.bmp"
#define LENGTH 1920
#define HIGHT 1080

#pragma pack(1)
///////////////////////////////////////////////
// * define bmp interpolation pattern 
// * GRBG 1
// * BGGR 2
// * GBRG 3
// * RGGB 4
///////////////////////////////////////////////
#define PATTERN 1			

int main()
{
	FILE *raw_fp = fopen(RAW_FILE,"rb");
	FILE *bmp_fp = fopen(BMP_FILE,"wb");

	char line_buf0[HIGHT][LENGTH];
	char bgr_buf0[HIGHT][LENGTH*3];
	int b,i,j,k,l;
	typedef struct bmp_header
	{
	unsigned short bfType;						//文件标识 2字节 必须为BM 
	unsigned int bfSize;						//文件大小 4字节 
	unsigned short bfReserved1;					//保留，每字节以"00"填写 2字节 
	unsigned short bfReserved2;					//同上 2字节 
	unsigned int bfOffBits;						//记录图像数据区的起始位置(图象数据相对于文件头字节的偏移量)。 4字节
	unsigned int biSize;						//表示本结构的大小 4字节 
	int biWidth;								//位图的宽度  4字节 
	int bitHeight;								//位图的高度  4字节 
	unsigned short biPlanes;					//永远为1 ,   2字节 
	unsigned short biBitCount;					//位图的位数  分为1 4 8 16 24 32   2字节
	unsigned int biCompression;					//压缩说明   4字节  
	unsigned int biSizeImage;					
	int biXPelsPerMeter;						//用象素/米表示的水平分辨率   4字节 
	int biYPelsPerMeter;						//用象素/米表示的垂直分辨率   4字节 
	unsigned int biClrUsed;						//位图使用的颜色索引数   4字节 
	unsigned int biClrImportant;				
	}bmp_header;

	bmp_header bmp_header0;
	bmp_header0.bfType = 0x00004d42;
	bmp_header0.bfSize = 0x005eec36;
	bmp_header0.bfReserved1 = 0x0000;
	bmp_header0.bfReserved2 = 0x0000;
	bmp_header0.bfOffBits = 0x00000036;
	bmp_header0.biSize = 0x00000028;
	bmp_header0.biWidth = 0x00000780;
	bmp_header0.bitHeight = 0x00000438;
	bmp_header0.biPlanes = 0x0001;
	bmp_header0.biBitCount = 0x0018;
	bmp_header0.biCompression = 0x00000000;
	bmp_header0.biSizeImage = 0x005eec00;
	bmp_header0.biXPelsPerMeter = 0x00000000;
	bmp_header0.biYPelsPerMeter = 0x00000000;
	bmp_header0.biClrUsed = 0x000000000;
	bmp_header0.biClrImportant = 0x00000000;

	printf("%d",sizeof(unsigned short));

	fwrite(&bmp_header0,1,54,bmp_fp);

	for(b=0;b<HIGHT;b++)
	{
		for(i=0;i<LENGTH;i++)
		{
		fread(&line_buf0[b][i],1,1,raw_fp);
		}
	}

	for(j=0;j<(HIGHT-1);j++)
	{
		if(j%2)
		{
			for(k=0;k<(LENGTH-1);k++)
			{
				if(k%2)
				{
					bgr_buf0[j][k*3]   =  line_buf0[j][k+1];									//B
					bgr_buf0[j][k*3+1] = (line_buf0[j][k] + line_buf0[j+1][k+1])/2;				//G
					bgr_buf0[j][k*3+2] =  line_buf0[j+1][k];									//R
				}else
				{						   
					bgr_buf0[j][k*3]   =  line_buf0[j][k];										//B
					bgr_buf0[j][k*3+1] = (line_buf0[j][k+1] + line_buf0[j+1][k])/2;				//G
					bgr_buf0[j][k*3+2] =  line_buf0[j+1][k+1];									//R
				}
			}
		}else
		{
			for(k=0;k<(LENGTH-1);k++)
			{
				if(k%2)
				{
					bgr_buf0[j][k*3]   =  line_buf0[j+1][k+1];								//B
					bgr_buf0[j][k*3+1] = (line_buf0[j][k+1] + line_buf0[j+1][k])/2;			//G
					bgr_buf0[j][k*3+2] =  line_buf0[j][k];									//R
				}else
				{						   
					bgr_buf0[j][k*3]   =  line_buf0[j+1][k];								//B
					bgr_buf0[j][k*3+1] = (line_buf0[j][k] + line_buf0[j+1][k+1])/2;			//G
					bgr_buf0[j][k*3+2] =  line_buf0[j][k+1];								//R
				}
			}
		}
	}

	for(l=0;l<HIGHT;l++)
	{
	fwrite(&bgr_buf0[l],LENGTH*3,1,bmp_fp);
	}
	fclose(raw_fp);
	fclose(bmp_fp);
	return 0;
}