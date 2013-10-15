#include "stdafx.h"
#include "isp_api.h"

int bmp2yuv422(img_proc_api_t *img, UNSG8 *pyuv422)
{
	int i, j;
	double y, u, v;
	double r, g, b;

	FILE *fp = fopen("test.yuv", "wb");

	pyuv422 = (UNSG8 *)malloc(img->size * sizeof(UNSG8));
	if (!pyuv422) {
		printf("malloc error!\n");
		return -1;
	}

	for(i=0; i<img->height; i++) {
		for(j=0; j<img->width; j++) {
			b = img->imgdata[3*(i*img->width + j)];
			g = img->imgdata[3*(i*img->width + j) + 1];
			r = img->imgdata[3*(i*img->width + j) + 2];

			y = 0.299 * r + 0.587 * g + 0.114 * b;
			u = -0.147 * r - 0.289 * g + 0.436 * b + 128;
			v = 0.615 * r - 0.515 * g - 0.100 * b + 128;

			pyuv422[2*((img->height - i - 1)*img->width + j)] = (j & 1)?((UNSG8)v):((UNSG8)u);
			pyuv422[2*((img->height - i - 1)*img->width + j) + 1] = (UNSG8)y;
		}
	}

	fwrite(pyuv422, img->width*img->height*2, 1, fp);
	fclose(fp);

	return 0;
}

void table_init()
{

}

void isp_proc(img_proc_api_t *img, SING8 *pathname, SING8 *savepath)
{
	char userchoice;
	UNSG8 *pyuv422 = NULL;	

	while ( userchoice = getchar()) {
		switch (userchoice) {
		case '1':
			readbmp(img, pathname);
			break;
		case '2':
			savebmp(img, savepath);
			break;
		case '3':
			bmp2yuv422(img, pyuv422);
			break;
		case 'q':
			printf("Are you sure to quit?(y/n):");

			fflush(stdin);
			if ( (userchoice = getchar()) == 'y')
				return ;

			break;
		default:			
			break;			
		}
	}
}

void getuserselection(char userchoice)
{
	
}