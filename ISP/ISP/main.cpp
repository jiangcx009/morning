// ISP.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	img_proc_api_t   img;
	SING8 *pathname = "C:\\Users\\Administrator\\Documents\\GitHub\\morning\\data\\luna.bmp";
	SING8 *savepath = "copy.bmp";

	display();

	isp_proc(&img, pathname, savepath);
	

	return 0;
}

