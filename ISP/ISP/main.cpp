// ISP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	img_proc_api_t   img;
	char *pathname = "C:\\Users\\Administrator\\Documents\\GitHub\\morning\\data\\face.bmp";
	char *savepath = "copy.bmp";

	readbmp(&img, pathname);
	savebmp(&img, savepath);

	

	return 0;
}

