#ifndef __ISP_API_H__
#define __ISP_API_H__

#include "datatype.h"

typedef struct img_proc_api_t
{
	tagBMP          tagbmp;
	UNSG32			width;
	UNSG32			height;
	UNSG32			size;
	FILE	        *fpin;
	FILE			*fpout;
};

void readbmp(img_proc_api_t *img, char *pathname);
//void savebmp(UNSG8 *filenm, UNSG8 *output_buff);

#endif