#pragma once
#include <IDrawFactory.h>
#include<MyTypes.h>
#include<service/file/IFileService.h>
namespace xc{
	class ISite{
	public:
		//! ��ȡ���ƹ���
		virtual shared_ptr<drawBasement::IDrawFactory> getDrawFactory()=0;
		//! ��ȡ�ļ�����
		virtual shared_ptr<fileservice::IFileService> getFileService()=0;
	};
	class ISiteEdieable:public ISite{
	private:
		shared_ptr<drawBasement::IDrawFactory> mDrawFactory;
		shared_ptr<fileservice::IFileService> mFileServie;
	public:
		//! ��ȡ���ƹ���
		shared_ptr<drawBasement::IDrawFactory> getDrawFactory(){
			return mDrawFactory;
		}

		//! ��װ���ƹ���
		void installDrawFactory(shared_ptr<drawBasement::IDrawFactory> f){
			mDrawFactory=f;
		}

		//! ��ȡ�ļ�����
		virtual shared_ptr<fileservice::IFileService> getFileService(){
			return mFileServie;
		}

		//! ��װ���ƹ���
		void installFileService(shared_ptr<fileservice::IFileService> f){
			mFileServie=f;
		}



	};
}