#pragma once
#include<service/file/IFile.h>
#include<filesystem>
namespace xc{
	namespace fileservice{
		class CFile:public IFile{
		private:
			std::ifstream mFile;
			std::tr2::sys::path mPath;
			unsigned long mFileSize;
			bool mIsopened;
		public:
			CFile(const char* filename){
				mPath = std::tr2::sys::path(filename);
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
			//! �ļ���С
			virtual unsigned long getFileSize(){
				return mFileSize;
			}
			//! ��ȡ�ļ�
			virtual void read(char* buf,int size){
				//checkOpened();
				mFile.read(buf,size);
			}
			//! ��ת��ȡλ��
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
			//! ���ݵ�ǰλ����ת��ȡλ��
			virtual void seekBy(int offset){
				//checkOpened();
				mFile.seekg(offset);
			}
			//! ��ȡ�ļ���
			virtual string getFileName(){
				return string(mPath.filename().c_str());
			}
			//! ��ȡ�ļ�λ����
			virtual string getAbsolutePath(){
				return string(std::tr2::sys::system_complete(mPath).file_string().c_str());
			}
			//! ���ļ�
			virtual void open(){
				if(!mFile.is_open()){
					mFile.open(mPath,std::ios_base::binary);
				}
				mIsopened=true;
			}
			//! �ر��ļ�
			virtual void close(){
				if(mFile.is_open()) mFile.close();
				mIsopened=false;
			}
		};
	}
}