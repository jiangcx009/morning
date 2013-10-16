#include "stdafx.h"
#include "isp_api.h"

int bmp2yuv422(img_proc_api_t *img, UNSG8 *pyuv422)
{
	int i, j;
	double y, u, v;
	double r, g, b;
	int yuv_llinetype;

	FILE *fp = fopen("test.yuv", "wb");

	yuv_llinetype = ((img->width * 16 + 31)>>5)<<2;
	pyuv422 = (UNSG8 *)malloc(yuv_llinetype * img->height * sizeof(UNSG8));

	if (!pyuv422) {
		printf("malloc error!\n");
		return -1;
	}

	for(i=0; i<img->height; i++) {
		for(j=0; j<img->width; j++) {
			b = img->imgdata[i*img->llinebyte + 3*j];
			g = img->imgdata[i*img->llinebyte + 3*j + 1];
			r = img->imgdata[i*img->llinebyte + 3*j + 2];

			y = 0.299 * r + 0.587 * g + 0.114 * b;
			u = -0.147 * r - 0.289 * g + 0.436 * b + 128;
			v = 0.615 * r - 0.515 * g - 0.100 * b + 128;

			pyuv422[((img->height - i - 1)*yuv_llinetype + 2 * j)] = ((2*j) & 0x02)?((UNSG8)v):((UNSG8)u);
			pyuv422[((img->height - i - 1)*yuv_llinetype + 2 * j) + 1] = (UNSG8)y;
		}
	}

	fwrite(pyuv422, yuv_llinetype*img->height, 1, fp);
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