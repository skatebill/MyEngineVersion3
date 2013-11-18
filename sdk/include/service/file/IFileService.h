#pragma once
#include"IImage.h"
#include"IFile.h"
#include<MyTypes.h>

namespace xc{
	namespace fileservice{
		class IFileService{
		public:
			//! ���ļ�����ͼƬ
			virtual shared_ptr<IImage> createImageFromFile(const char* filename)=0;
			//! ��ȡ�ļ�
			virtual shared_ptr<IFile> createReadableFile(const wchar_t* filename)=0;
		};
	}
}