#pragma once
#include<service/file/IFile.h>
#include<filesystem>
namespace xc{
	namespace fileservice{
		class CFile:public IFile{
		private:
			std::ifstream mFile;
			std::tr2::sys::wpath mPath;
			unsigned long mFileSize;
			bool mIsopened;
		public:
			CFile(const wchar_t* filename){
				mPath = std::tr2::sys::wpath(filename);
				if(!std::tr2::sys::exists(mPath))
				{
					throw std::exception("file not exsists");
				}
				mFileSize = (unsigned long)std::tr2::sys::file_size(mPath);
				mIsopened=false;
			}
			~CFile(){
				close();
			}
			inline void checkOpened(){
				if(!mIsopened){
					throw std::exception("file not opened");
				}
			}
			//! 文件大小
			virtual unsigned long getFileSize(){
				return mFileSize;
			}
			//! 读取文件
			virtual void read(char* buf,int size){
				//checkOpened();
				mFile.read(buf,size);
			}
			//! 跳转读取位置
			virtual void seekTo(EnumSeekPos pos){
				//checkOpened();
				switch (pos)
				{
				case xc::fileservice::ESP_BEGIN:
					mFile.seekg(0,std::ios_base::beg);
					break;
				case xc::fileservice::ESP_END:
					mFile.seekg(std::ios_base::end);
					break;
				default:
					break;
				}
			}
			//! 根据当前位置跳转读取位置
			virtual void seekBy(int offset){
				//checkOpened();
				mFile.seekg(offset);
			}
			//! 获取文件名
			virtual string getFileName(){
				return string(mPath.filename().c_str());
			}
			//! 获取文件位置名
			virtual string getAbsolutePath(){
				return string(std::tr2::sys::system_complete(mPath).file_string().c_str());
			}
			//! 打开文件
			virtual void open(){
				if(!mFile.is_open()){
					mFile.open(mPath,std::ios_base::binary);
				}
				mIsopened=true;
			}
			//! 关闭文件
			virtual void close(){
				if(mFile.is_open()) mFile.close();
				mIsopened=false;
			}
		};
	}
}