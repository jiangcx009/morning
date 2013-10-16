// ISP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	img_proc_api_t   img;
	SING8 *pathname = "C:\\Users\\Administrator\\Documents\\GitHub\\morning\\data\\luna.bmp";
	SING8 *savepath = "copy.bmp";

	double start,end;

	start = (double)clock()/CLK_TCK;

	display();

	isp_proc(&img, pathname, savepath);

	end = (double)clock()/CLK_TCK;
	printf("run time is : %2f seconds\n", (double)(end-start)/(double)CLOCKS_PER_SEC);

	return 0;
}

