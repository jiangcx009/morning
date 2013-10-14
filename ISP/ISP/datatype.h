#ifndef __DATATYPE_H__
#define __DATATYPE_H__

typedef unsigned int	UNSG32;
typedef unsigned char	UNSG8;
typedef char			SING8;

typedef struct _tagBMPHeader
{
	tagBITMAPFILEHEADER bmpfileheader;
	tagBITMAPINFOHEADER bmpinfoheader;
	tagRGBQUAD			*bmpQuad;
}tagBMPHeader;


#endif