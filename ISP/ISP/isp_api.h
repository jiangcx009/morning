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
	UNSG32			llinebyte;
	SING8			*bmpdata;
};

void readbmp(img_proc_api_t *img, char *pathname);
void savebmp(img_proc_api_t *img, char *pathname, SING8 *imgdata);

#endif