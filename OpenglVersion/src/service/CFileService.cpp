#include "CFileService.h"
#include "CFreeImage.h"
#include <filesystem>
namespace xc{
	namespace fileservice{

		CFileService::CFileService(){
			FreeImage_Initialise();
		}
		CFileService::~CFileService(){
			FreeImage_DeInitialise();
		}

		//! 从文件创建图片
		 shared_ptr<IImage> CFileService::createImageFromFile(const char* filename){
			 if(!std::tr2::sys::exists(std::tr2::sys::path(filename)))
				 throw std::exception("no such image ");

			 CFreeImage* image = new CFreeImage;
			 FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename, 0);
			 FIBITMAP *dib(0);
			 //pointer to the image data

			 if(fif == FIF_UNKNOWN) 
				 fif = FreeImage_GetFIFFromFilename(filename);

			 if(fif == FIF_UNKNOWN)
				 throw std::exception("not supported image");

			 if(FreeImage_FIFSupportsReading(fif))
				 dib = FreeImage_Load(fif, filename);
			 if(!dib){
				 throw std::exception("error load image");
			 }
			 image->dib=dib;

			 //retrieve the image data
			 image->m_Data = FreeImage_GetBits(dib);
			 //get the image width and height
			 image->m_Width = FreeImage_GetWidth(dib);
			 image->m_Height = FreeImage_GetHeight(dib);
			 FREE_IMAGE_COLOR_TYPE t = FreeImage_GetColorType(dib);
			 if(t == FIC_RGBALPHA){
				 image->m_HasAlpha=true;
			 }
			 return shared_ptr<IImage>(image);
		}
	}
}