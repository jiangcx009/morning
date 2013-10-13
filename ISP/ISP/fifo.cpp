#include "stdafx.h"

void readbmp(img_proc_api_t *img, char *pathname)
{
	FILE *fp;

	if (!(fp = fopen(pathname, "rb"))){
		fprintf(stderr, "error to open file %s\n", *pathname);
		exit(-1);
	}

	if (fread( (tagBITMAPFILEHEADER *)(&(img->tagbmp.bmpfileheader)), 1, \
		sizeof(BITMAPFILEHEADER), fp) != sizeof(BITMAPFILEHEADER)) {

			printf("read bmp file header failed!\n");
			exit(-1);
	}

	if (fread( (tagBITMAPINFOHEADER *)(&(img->tagbmp.bmpinfoheader)), 1, \
		sizeof(BITMAPINFOHEADER), fp) != sizeof(BITMAPINFOHEADER)) {

			printf("read bmp info header failed!\n");
			exit(-1);
	}

	img->width = img->tagbmp.bmpinfoheader.biWidth;
	img->height = img->tagbmp.bmpinfoheader.biHeight;
	img->size = img->width * img->height * 3;

	if (fread( (tagRGBQUAD *)(&(img->tagbmp.bmpQuad)), 1, \
		sizeof(tagRGBQUAD), fp) != sizeof(tagRGBQUAD)) {
			
			printf("read bmp quard failed!\n");
			exit(-1);
	}

	img->tagbmp.bmpdata = (SING8 *)malloc(img->size * sizeof(SING8));
	if ( img->tagbmp.bmpdata == NULL) {
		
			printf("malloc memory failed!\n");
	}

	if (fread( (SING8 *)img->tagbmp.bmpdata, 1, 
		img->size, fp) != img->size) {

			printf("read bmp data failed!\n");
			exit(-1);
	}

	fclose(fp);
}

void savebmp(img_proc_api_t *img, char *savepath)
{

}