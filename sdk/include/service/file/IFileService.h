#pragma once
#include"IImage.h"
#include<MyTypes.h>
namespace xc{
	namespace fileservice{
		class IFileService{
		public:
			//! 从文件创建图片
			virtual shared_ptr<IImage> createImageFromFile(const char* filename)=0;
		};
	}
}