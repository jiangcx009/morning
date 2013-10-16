#ifndef __DATATYPE_H__
#define __DATATYPE_H__

typedef unsigned int	UNSG32;
typedef unsigned short  UNSG16;
typedef unsigned char	UNSG8;
typedef char			SING8;

typedef struct _tagBMPHeader
{
	tagBITMAPFILEHEADER bmpfileheader;
	tagBITMAPINFOHEADER bmpinfoheader;
	tagRGBQUAD			*bmpQuad;
}tagBMPHeader;

typedef struct _tagRGB2YUV422_Table
{
	UNSG16  ya[256];
	UNSG16  yb[256];
	UNSG16  yc[256];

	UNSG16  ua[256];
	UNSG16  ub[256];
	UNSG16  uc[256];

	UNSG16  va[256];
	UNSG16  vb[256];
	UNSG16  vc[256];
}tagRGB2YUV422_Table;

#endif