#include "stdafx.h"

void readbmp(img_proc_api_t *img, char *pathname)
{
	FILE *fp;
	int ret;

	if (!(fp = fopen(pathname, "rb"))){
		fprintf(stderr, "error to open file %s\n", *pathname);
		exit(-1);
	}

	if ( (ret = fread( (tagBITMAPFILEHEADER *)(&(img->tagbmpheader.bmpfileheader)), \
		sizeof(BITMAPFILEHEADER), 1, fp)) == -1) {

			printf("read bmp file header failed!\n");
			exit(-1);
	}

	if ( (ret = fread( (tagBITMAPINFOHEADER *)(&(img->tagbmpheader.bmpinfoheader)), \
		sizeof(BITMAPINFOHEADER), 1, fp)) == -1) {

			printf("read bmp info header failed!\n");
			exit(-1);
	}

	img->width = img->tagbmpheader.bmpinfoheader.biWidth;
	img->height = img->tagbmpheader.bmpinfoheader.biHeight;
	img->biBitCount = img->tagbmpheader.bmpinfoheader.biBitCount;
	img->llinebyte = ((img->width * img->biBitCount + 31)>>5)<<2;
	img->size = img->llinebyte * img->height;

	if (8 == img->biBitCount) {
		img->tagbmpheader.bmpQuad = (tagRGBQUAD *)malloc(sizeof(tagRGBQUAD) * 256);
		if ( img->bmpdata == NULL) {
			printf("malloc memory failed!\n");
			exit(-1);
		}

		if ( (ret = fread( (tagRGBQUAD *)(img->tagbmpheader.bmpQuad), sizeof(tagRGBQUAD), \
			256, fp)) == -1) {
				
				printf("read bmp quard failed!\n");
				exit(-1);
		}
	}
	
	img->bmpdata = (SING8 *)malloc(img->size * sizeof(SING8));
	if ( img->bmpdata == NULL) {	
		printf("malloc memory failed!\n");
		exit(-1);
	}

	if ( (ret = fread( (SING8 *)img->bmpdata, 1, img->size, fp)) == -1) {

			printf("read bmp data failed!\n");
			exit(-1);
	}
	

	fclose(fp);
}

void savebmp(img_proc_api_t *img, char *savepath, SING8 *imgdata)
{
	FILE *fp;
	int ret;

	if ( !(fp = fopen(savepath, "wb"))) {
		fprintf(stderr, "error to open file %s\n", *savepath);
		exit(-1);
	}

	if ( (ret = fwrite( (tagBITMAPFILEHEADER *)&(img->tagbmpheader.bmpfileheader), \
		sizeof(tagBITMAPFILEHEADER), 1, fp)) == -1) {

			printf("write bmp file header failed!\n");
			exit(-1);
	} 

	if ( (ret = fwrite( (tagBITMAPINFOHEADER *)(&(img->tagbmpheader.bmpinfoheader)), \
		sizeof(BITMAPINFOHEADER), 1, fp)) == -1) {

			printf("write bmp info header failed!\n");
			exit(-1);
	}

	if (8 == img->biBitCount) {
		if ( (ret = fwrite( (tagRGBQUAD *)(img->tagbmpheader.bmpQuad), sizeof(tagRGBQUAD), \
		256, fp)) == -1) {

			printf("read bmp quard failed!\n");
			exit(-1);
		}
	}
	
	if ( (ret = fwrite( imgdata, 1, img->size, fp)) == -1) {

			printf("read bmp data failed!\n");
			exit(-1);
	}
	
	fflush(fp);

	fclose(fp);
}