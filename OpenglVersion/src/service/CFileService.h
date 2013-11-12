#pragma once
#include <service/file/IFileService.h>
namespace xc{
	namespace fileservice{
		class CFileService:public IFileService{
		public:
			explicit CFileService();

			~CFileService();

			//! 从文件创建图片
			virtual shared_ptr<IImage> createImageFromFile(const char* filename);

		};
	}
}