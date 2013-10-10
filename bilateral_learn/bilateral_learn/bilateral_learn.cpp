#include <stdio.h>  
#include <stdlib.h>
#include <cv.h>  
#include <cxcore.h>  
#include <highgui.h>  
#include <cvaux.h>//必须引此头文件 
#include <Windows.h>
#include <math.h>

void main()
{
	IplImage *rgbx = NULL;
//	IplImage *pResultImg = NULL;
	CvScalar _cvSrc;

	//fileter size is 15*15
	int filter_size = 2;
	int i, j, k0, k1;
	int keyID;

	float dirta_Dis = 3.0f;
	float dirta_col = 0.1f;

	rgbx = cvLoadImage("D:\\江晨晓\\projects\\bilateral_learn\\hong1.bmp");
	
	if(!rgbx)
		printf("error open!\n");

	IplImage *depthImg_Repair = cvCreateImage(cvGetSize(rgbx), rgbx->depth, rgbx->nChannels);

	int width = rgbx->width;
	int height = rgbx->height;

	//运行时间测试
	LARGE_INTEGER t1,t2,feq;
	QueryPerformanceFrequency(&feq);
	double time_bilateral;

	int step = rgbx->widthStep / sizeof(unsigned char);
//	int channel = 3;

	cvNamedWindow("SrcImg", 1);
	cvNamedWindow("ResultImg", 1);
	cvMoveWindow("SrcImg", 30, 0);
	cvMoveWindow("ResultImg", 1000, 0);

	cvShowImage("ResultImg", rgbx);

/*	_cvSrc = cvGet2D(rgbx,0,0);
	printf("%f  %f  %f\n",_cvSrc.val[0],_cvSrc.val[1],_cvSrc.val[2]);
	printf("%d  %d  %d\n",(unsigned char)rgbx->imageData[0],(unsigned char)rgbx->imageData[1],(unsigned char)rgbx->imageData[2]);

	for(i = 0; i<height;i++)
		for(j=0;j<width;j++)
		{
			_cvSrc = cvGet2D(rgbx,i,j);
			if(_cvSrc.val[0] != (unsigned char)rgbx->imageData[i * step + j * 3 ])
			{
				printf("%d  %d\n",i,j);
				cvSet2D(rgbx,i,j,cvScalar(255,0,0));
				cvShowImage("SrcImg", rgbx);
			}
			depthImg_Repair->imageData[i * step + j *3] = rgbx->imageData[i * step + j * 3 ];
			depthImg_Repair->imageData[i * step + j *3 + 1] = depthImg_Repair->imageData[i * step + j * 3 + 2] = 0;
			printf("%f  %d\n",_cvSrc.val[0], depthImg_Repair->imageData[i * width + j]);
		}
*/
//	start = clock();
	QueryPerformanceCounter(&t1);

//	int i,j,k0,k1;
	int FilterWindow = 7;
	int thre = 9;

	//3*3掩膜
	//float Mask[3][3] = {exp(-1), exp(-0.5), exp(-1), exp(-0.5), 1, exp(-0.5), exp(-1), exp(-0.5), exp(-1)};
#if 1
	for(i = FilterWindow; i < height - FilterWindow; ++i)
	{
		for(j = FilterWindow; j < width - FilterWindow; ++j)
		{
			long Depth_Sum[3] = {0};

			UINT DepthReserver = 0;
			int ValidCount = 0;

			for(k0 = -FilterWindow; k0 <= FilterWindow; ++k0)
			{
				for(k1 = -FilterWindow; k1 <= FilterWindow; ++k1)
				{
					//int diffval = abs((unsigned char)rgbx->imageData[(i * step + j * 3)] - (unsigned char)rgbx->imageData[(i + k1) * step + (j + k0) * 3]) 
					//	+ abs((unsigned char)rgbx->imageData[(i * step + j * 3)  + 1] - (unsigned char)rgbx->imageData[(i + k1) * step + (j + k0) * 3 + 1])
					//	+ abs((unsigned char)rgbx->imageData[(i * step + j * 3)  + 2] - (unsigned char)rgbx->imageData[(i + k1) * step + (j + k0) * 3 + 2]);
					int diffval_R = abs((unsigned char)rgbx->imageData[(i * step + j * 3)] - (unsigned char)rgbx->imageData[(i + k1) * step + (j + k0) * 3]);
					int diffval_G = abs((unsigned char)rgbx->imageData[(i * step + j * 3) + 1] - (unsigned char)rgbx->imageData[(i + k1) * step + (j + k0) * 3 + 1]); 
					int diffval_B = abs((unsigned char)rgbx->imageData[(i * step + j * 3) + 2] - (unsigned char)rgbx->imageData[(i + k1) * step + (j + k0) * 3 + 2]);

//					printf("%d  ",diffval);

					if(diffval_R < thre && diffval_G < thre && diffval_B < thre)
					{
						//Depth_Sum[0] += pdepth[(i + k1) * width + j + k0] & 0x0007;
						//Depth_Sum[1] += pdepth[(i + k1) * width + j + k0 + 1] & 0x0007;
						//Depth_Sum[2] += pdepth[(i + k1) * width + j + k0 + 2] & 0x0007;
						Depth_Sum[0] += (unsigned char)rgbx->imageData[(i + k1) * step + (j + k0) * 3];
						Depth_Sum[1] += (unsigned char)rgbx->imageData[(i + k1) * step + (j + k0) * 3 + 1];
						Depth_Sum[2] += (unsigned char)rgbx->imageData[(i + k1) * step + (j + k0) * 3 + 2];
						ValidCount++;
					}//if
				}
			}//for k0,k1

//			printf("\n");

			Depth_Sum[0] /= ValidCount;
			Depth_Sum[1] /= ValidCount;
			Depth_Sum[2] /= ValidCount;

			depthImg_Repair->imageData[i * step + j * 3] = (unsigned char)Depth_Sum[0];
			depthImg_Repair->imageData[i * step + j * 3 + 1] = (unsigned char)Depth_Sum[1];
			depthImg_Repair->imageData[i * step + j * 3 + 2] = (unsigned char)Depth_Sum[2];

		}
	}
#else
	for(i = filter_size; i < height - filter_size; i++)
		for(j = filter_size; j < width - filter_size; j++)
		{
			float alpha_Dis = 0;
			float alpha_col_R = 0;
			float alpha_col_G = 0;
			float alpha_col_B = 0;

			float New_col_R = 0;
			float New_col_G = 0;
			float New_col_B = 0;

			float Sum_col_R = 0;
			float Sum_col_G = 0;
			float Sum_col_B = 0;

			float Sumw_col_R = 0;
			float Sumw_col_G = 0;
			float Sumw_col_B = 0;

			float index0[3][3] = {0};
			float index1[3][9] = {0};
			int valid_pixels = 0;
			int sum_color = 0;
	
			for(k1 = -filter_size; k1 <= filter_size ; k1++)
			{
				for(k0 = -filter_size; k0 <= filter_size ; k0++)
				{
					int index0 = k0 * k0 + k1 * k1;
					float index1_R = sqrt((float)((unsigned char)rgbx->imageData[(i + k0) * step + (j + k1) * 3 + 0] - (unsigned char)rgbx->imageData[i * step + j * 3 + 0]) * ((unsigned char)rgbx->imageData[(i + k0) * step + (j + k1) * 3 + 0] - (unsigned char)rgbx->imageData[i * step + j * 3 + 0]));
					float index1_G = sqrt((float)((unsigned char)rgbx->imageData[(i + k0) * step + (j + k1) * 3 + 1] - (unsigned char)rgbx->imageData[i * step + j * 3 + 1]) * ((unsigned char)rgbx->imageData[(i + k0) * step + (j + k1) * 3 + 1] - (unsigned char)rgbx->imageData[i * step + j * 3 + 1]));
					float index1_B = sqrt((float)((unsigned char)rgbx->imageData[(i + k0) * step + (j + k1) * 3 + 2] - (unsigned char)rgbx->imageData[i * step + j * 3 + 2]) * ((unsigned char)rgbx->imageData[(i + k0) * step + (j + k1) * 3 + 2] - (unsigned char)rgbx->imageData[i * step + j * 3 + 2]));

					alpha_Dis = exp(-0.5 * index0 / (dirta_Dis * dirta_Dis));
					
					alpha_col_R = exp(-0.5 * (float)index1_R / (dirta_col * dirta_col));
					alpha_col_G = exp(-0.5 * (float)index1_G / (dirta_col * dirta_col));
					alpha_col_B = exp(-0.5 * (float)index1_B / (dirta_col * dirta_col));
					
					New_col_R =  alpha_Dis * alpha_col_R; 
					New_col_G =  alpha_Dis * alpha_col_G; 
					New_col_B =  alpha_Dis * alpha_col_B; 

					//用来归一化
					Sumw_col_R += New_col_R; 
					Sumw_col_G += New_col_G; 
					Sumw_col_B += New_col_B; 

					Sum_col_R += New_col_R * (unsigned char)rgbx->imageData[(i + k0 ) * step + (j + k1) * 3 + 0];
					Sum_col_G += New_col_G * (unsigned char)rgbx->imageData[(i + k0 ) * step + (j + k1) * 3 + 1];
					Sum_col_B += New_col_B * (unsigned char)rgbx->imageData[(i + k0 ) * step + (j + k1) * 3 + 2];
					
				}
			}


			depthImg_Repair->imageData[i * step + j * 3 + 0] = (float)Sum_col_R / (float)Sumw_col_R;
			depthImg_Repair->imageData[i * step + j * 3 + 1] = (float)Sum_col_G / (float)Sumw_col_G;
			depthImg_Repair->imageData[i * step + j * 3 + 2] = (float)Sum_col_B / (float)Sumw_col_B;
			
			
		}
#endif
	QueryPerformanceCounter(&t2);
	
	time_bilateral = ((double)t2.QuadPart - (double)t1.QuadPart)/(double)feq.QuadPart;
	printf("%1.5f\n",time_bilateral);
//	printf("%d  %d  %d\n",(unsigned char)rgbx->imageData[0],(unsigned char)rgbx->imageData[1],(unsigned char)rgbx->imageData[2]);

	cvShowImage("SrcImg",depthImg_Repair);

	cvWaitKey(-1);

	cvReleaseImage(&rgbx);
	cvReleaseImage(&depthImg_Repair);

}