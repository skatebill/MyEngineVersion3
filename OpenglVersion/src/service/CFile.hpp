#pragma once
#include<service/file/IFile.h>
#include<boost/filesystem.hpp>
namespace xc{
	namespace fileservice{
		class CFile:public IFile{
		private:
			std::ifstream mFile;
			
			boost::filesystem::path mPath;
			unsigned long mFileSize;
			bool mIsopened;
		public:
			CFile(const char* filename){
				mPath = boost::filesystem::path(filename);
				if(!boost::filesystem::exists(mPath))
				{
					throw std::exception("file not exsists");
				}
				mFileSize = (unsigned long)boost::filesystem::file_size(mPath);
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
				return string(boost::filesystem::system_complete(mPath).c_str());
			}
			//! 打开文件
			virtual void open(){
				if(!mFile.is_open()){
					mFile.open(mPath.c_str(),std::ios_base::binary);
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