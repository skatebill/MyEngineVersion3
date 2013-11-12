#pragma once
#include"IImage.h"
#include<MyTypes.h>
namespace xc{
	namespace fileservice{
		class IFileService{
		public:
			//! ���ļ�����ͼƬ
			virtual shared_ptr<IImage> createImageFromFile(const char* filename)=0;
		};
	}
}