#pragma once
#include <service/file/IFileService.h>
namespace xc{
	namespace fileservice{
		class CFileService:public IFileService{
		public:
			explicit CFileService();

			~CFileService();

			//! ���ļ�����ͼƬ
			virtual shared_ptr<IImage> createImageFromFile(const char* filename);
			//! ��ȡ�ļ�
			virtual shared_ptr<IFile> createReadableFile(const wchar_t* filename);

		};
	}
}