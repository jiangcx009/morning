#include "stdafx.h"
#include "isp_api.h"

int bmp2yuv422(img_proc_api_t *img, UNSG8 *pyuv422)
{
	int i, j;
	int y, u, v;
	int r, g, b;
	int yuv_llinetype;
	tagRGB2YUV422_Table rgb2yuv_table;

	FILE *fp = fopen("test.yuv", "wb");

	yuv_llinetype = ((img->width * 16 + 31)>>5)<<2;
	pyuv422 = (UNSG8 *)malloc(yuv_llinetype * img->height * sizeof(UNSG8));
	if (!pyuv422) {
		printf("malloc error!\n");
		return -1;
	}

	table_init(&rgb2yuv_table);

	for(i=0; i<img->height; i++) {
		for(j=0; j<img->width; j++) {
			b = img->imgdata[i*img->llinebyte + 3*j];
			g = img->imgdata[i*img->llinebyte + 3*j + 1];
			r = img->imgdata[i*img->llinebyte + 3*j + 2];

			//y = 0.299 * r + 0.587 * g + 0.114 * b;
			//u = -0.147 * r - 0.289 * g + 0.436 * b + 128;
			//v = 0.615 * r - 0.515 * g - 0.100 * b + 128;
			y = rgb2yuv_table.ya[r] + rgb2yuv_table.yb[g] + rgb2yuv_table.yc[b];
			u = -rgb2yuv_table.ua[r] - rgb2yuv_table.ub[g] + rgb2yuv_table.uc[b] + 128;
			v = rgb2yuv_table.va[r] - rgb2yuv_table.vb[g] - rgb2yuv_table.vc[b] + 128;

			pyuv422[((img->height - i - 1)*yuv_llinetype + 2 * j)] = ((2*j) & 0x02)?((UNSG8)v):((UNSG8)u);
			pyuv422[((img->height - i - 1)*yuv_llinetype + 2 * j) + 1] = (UNSG8)y;
			
		}
	}

	fwrite(pyuv422, yuv_llinetype*img->height, 1, fp);

	free(pyuv422);
	fclose(fp);

	return 0;
}

/*	Y = 0.299 * R + 0.587 * G + 0.114 * B;
	Y = (R * 299 + G * 587 + B * 114) / 1000;
	这个式子好像还有点复杂，可以再砍掉一个除法运算。
	前面的算式D可以这样写：
	0.299=299/1000=1224/4096
	所以 D = (R * 1224) / 4096
	Y=(R*1224)/4096+(G*2404)/4096+(B*467)/4096
	再简化为：
	Y=(R*1224+G*2404+B*467)/4096
*/
void table_init(tagRGB2YUV422_Table *rgb2yuv_table)
{
	int i;

	for(i=0; i<256; i++) {
		rgb2yuv_table->ya[i] = (i*1224)>>12;
		rgb2yuv_table->yb[i] = (i*2404)>>12;
		rgb2yuv_table->yc[i] = (i*467)>>12;
					 
		rgb2yuv_table->ua[i] = (i*602)>>12;
		rgb2yuv_table->ub[i] = (i*1183)>>12;
		rgb2yuv_table->uc[i] = (i*1785)>>12;
					 
		rgb2yuv_table->va[i] = (i*2519)>>12;
		rgb2yuv_table->vb[i] = (i*2109)>>12;
		rgb2yuv_table->vc[i] = (i*409)>>12;

	}
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
		case '4':
			img_filter(img, MEDIA_FILTER);
			break;
		case 'q':
			printf("Are you sure to quit?(y/n):");

			fflush(stdin);
			if ( (userchoice = getchar()) == 'y')
				return ;
			else {
				printf("continue input you choice:");
				break;
			}
		default:			
			break;			
		}
	}
}

int img_filter(img_proc_api_t *img, int Filter_type)
{
	switch(Filter_type) {
	case MEDIA_FILTER:
		printf("media filter\n");
		break;
	case MEAN_FILTER:
		printf("mean filter\n");
		break;
	case BILATERAL_FILTER:
		printf("bilateral filter\n");
		break;
	default:
		break;
	}

	return 0;
}

void media_filter(UNSG8 *pSrcImg, UNSG8 *pResImg, UNSG32 width, UNSG32 height)
{

}
