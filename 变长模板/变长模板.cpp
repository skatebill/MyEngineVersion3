// 变长模板.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<freeImage/FreeImage.h>
int _tmain(int argc, _TCHAR* argv[])
{
	const char* filename = "1.jpg";
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename, 0);
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);

	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(filename);

	if(fif == FIF_UNKNOWN)
		return 1;

	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if((bits == 0) || (width == 0) || (height == 0))
		return 1;
	return 0;
}

