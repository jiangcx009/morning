#include "stdafx.h"
#include "isp_api.h"

void readbmp(UNSG8 *filenm, UNSG8 *input_buff)
{
	FILE *fp;
	
	if(!(fp = fopen(filenm, "rb")))
	{
		fprintf(stderr, "error to open file %s\n", *filenm);
		exit(-1);
	}

	fseek(fp, sizeof(tagBITMAPFILEHEADER), SEEK_CUR);
	
}