#ifndef __ISP_API_H__
#define __ISP_API_H__

#include "datatype.h"

typedef struct img_proc_api_t
{
	tagBMPHeader    tagbmpheader;
	UNSG32			width;
	UNSG32			height;
	UNSG32			size;
	UNSG32			biBitCount;
	UNSG32			llinebyte;  //4×Ö½Ú¶ÔÆë
	UNSG8			*imgdata;

	FILE			*fp;
};

int readbmp(img_proc_api_t *img, char *pathname);
int savebmp(img_proc_api_t *img, char *pathname);
int readbmpheader(img_proc_api_t *img);
int readimgcfg(img_proc_api_t *img);
int readimgdata(img_proc_api_t *img);
int writebmpheader(img_proc_api_t *img);
int writeimgdata(img_proc_api_t *img);
void display();
void isp_proc(img_proc_api_t *img, SING8 *pathname, SING8 *savepath);
void table_init(tagRGB2YUV422_Table *rgb2yuv_table);

#endif