#include "stdafx.h"

int readbmp(img_proc_api_t *img, char *pathname)
{
	if (!(img->fp = fopen(pathname, "rb"))){
		fprintf(stderr, "error to open file\n");
		return -1;
	}

	readbmpheader(img);

	readimgcfg(img);

	readimgdata(img);

	fclose(img->fp);

	return 0;
}

int savebmp(img_proc_api_t *img, char *savepath)
{
	if ( !(img->fp = fopen(savepath, "wb"))) {
		fprintf(stderr, "error to open file %s\n", *savepath);
		return -1;
	}

	writebmpheader(img);
	writeimgdata(img);
	
	fclose(img->fp);

	return 0;
}

int readbmpheader(img_proc_api_t *img)
{
	int ret = 0;

	if ( (ret = fread( (tagBITMAPFILEHEADER *)(&(img->tagbmpheader.bmpfileheader)), \
		sizeof(BITMAPFILEHEADER), 1, img->fp)) == -1) {
			printf("read bmp file header failed!\n");
			return -1;
	}

	if ( (ret = fread( (tagBITMAPINFOHEADER *)(&(img->tagbmpheader.bmpinfoheader)), \
		sizeof(BITMAPINFOHEADER), 1, img->fp)) == -1) {
			printf("read bmp info header failed!\n");
			return -1;
	}

	return 0;
}

int readimgcfg(img_proc_api_t *img)
{
	img->width = img->tagbmpheader.bmpinfoheader.biWidth;
	img->height = img->tagbmpheader.bmpinfoheader.biHeight;
	img->biBitCount = img->tagbmpheader.bmpinfoheader.biBitCount;
	img->llinebyte = ((img->width * img->biBitCount + 31)>>5)<<2;
	img->size = img->llinebyte * img->height;

	return 0;
}

int readimgdata(img_proc_api_t *img)
{
	int ret = 0;

	if (8 == img->biBitCount) {
		img->tagbmpheader.bmpQuad = (tagRGBQUAD *)malloc(sizeof(tagRGBQUAD) * 256);
		if ( img->imgdata == NULL) {
			printf("malloc memory failed!\n");
			return -1;
		}

		if ( (ret = fread( (tagRGBQUAD *)(img->tagbmpheader.bmpQuad), sizeof(tagRGBQUAD), \
			256, img->fp)) == -1) {				
				printf("read bmp quard failed!\n");
				return -1;
		}
	}

	img->imgdata = (SING8 *)malloc(img->size * sizeof(SING8));
	if ( img->imgdata == NULL) {	
		printf("malloc memory failed!\n");
		return -1;
	}

	if ( (ret = fread( (SING8 *)img->imgdata, 1, img->size, img->fp)) == -1) {
		printf("read bmp data failed!\n");
		return -1;
	}

	return 0;
}

int writebmpheader(img_proc_api_t *img)
{
	int ret = 0;

	if ( (ret = fwrite( (tagBITMAPFILEHEADER *)&(img->tagbmpheader.bmpfileheader), \
		sizeof(tagBITMAPFILEHEADER), 1, img->fp)) == -1) {
			printf("write bmp file header failed!\n");
			return -1;
	} 

	if ( (ret = fwrite( (tagBITMAPINFOHEADER *)(&(img->tagbmpheader.bmpinfoheader)), \
		sizeof(BITMAPINFOHEADER), 1, img->fp)) == -1) {
			printf("write bmp info header failed!\n");
			return -1;
	}

	return 0;
}

int writeimgdata(img_proc_api_t *img)
{
	int ret = 0;

	if (8 == img->biBitCount) {
		if ( (ret = fwrite( (tagRGBQUAD *)(img->tagbmpheader.bmpQuad), sizeof(tagRGBQUAD), \
			256, img->fp)) == -1) {
				printf("read bmp quard failed!\n");
				return -1;
		}
	}

	if ( (ret = fwrite( img->imgdata, 1, img->size, img->fp)) == -1) {
		printf("read bmp data failed!\n");
		return -1;
	}

	fflush(img->fp);

	return 0;
}