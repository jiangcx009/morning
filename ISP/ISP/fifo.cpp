#include "stdafx.h"

void readbmp(img_proc_api_t *img, char *pathname)
{
	FILE *fp;
	int ret;

	if (!(fp = fopen(pathname, "rb"))){
		fprintf(stderr, "error to open file %s\n", *pathname);
		exit(-1);
	}

	if ( (ret = fread( (tagBITMAPFILEHEADER *)(&(img->tagbmpheader.bmpfileheader)), sizeof(BITMAPFILEHEADER), \
		1, fp)) == -1) {

			printf("read bmp file header failed!\n");
			exit(-1);
	}

	if ( (ret = fread( (tagBITMAPINFOHEADER *)(&(img->tagbmpheader.bmpinfoheader)), sizeof(BITMAPINFOHEADER),\
		1, fp)) == -1) {

			printf("read bmp info header failed!\n");
			exit(-1);
	}

	img->width = img->tagbmpheader.bmpinfoheader.biWidth;
	img->height = img->tagbmpheader.bmpinfoheader.biHeight;
	img->biBitCount = img->tagbmpheader.bmpinfoheader.biBitCount;
	img->llinebyte = (img->width * img->biBitCount + 7)/8;
	img->size = img->llinebyte * img->height;

	if (8 == img->biBitCount) {
		img->bmpdata = (SING8 *)malloc(sizeof(tagRGBQUAD) * 256);
		if ( img->bmpdata == NULL)
			printf("malloc memory failed!\n");

		if ( (ret = fread( (tagRGBQUAD *)(&(img->tagbmpheader.bmpQuad)), sizeof(tagRGBQUAD), \
			256, fp)) == -1) {
				
				printf("read bmp quard failed!\n");
				exit(-1);
		}
	}
	else {
		img->bmpdata = (SING8 *)malloc(img->size * sizeof(SING8));
		if ( img->bmpdata == NULL)	
			printf("malloc memory failed!\n");

		if ( (ret = fread( (SING8 *)img->bmpdata, 1, 
			img->size, fp)) == -1) {

				printf("read bmp data failed!\n");
				exit(-1);
		}
	}

	fclose(fp);
}

void savebmp(img_proc_api_t *img, char *savepath)
{

}