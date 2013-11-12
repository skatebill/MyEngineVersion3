#pragma once
#include <IDrawFactory.h>
#include<MyTypes.h>
#include<service/file/IFileService.h>
namespace xc{
	class ISite{
	public:
		//! 获取绘制工厂
		virtual shared_ptr<drawBasement::IDrawFactory> getDrawFactory()=0;
		//! 获取文件服务
		virtual shared_ptr<fileservice::IFileService> getFileService()=0;
	};
	class ISiteEdieable:public ISite{
	private:
		shared_ptr<drawBasement::IDrawFactory> mDrawFactory;
		shared_ptr<fileservice::IFileService> mFileServie;
	public:
		//! 获取绘制工厂
		shared_ptr<drawBasement::IDrawFactory> getDrawFactory(){
			return mDrawFactory;
		}

		//! 安装绘制工厂
		void installDrawFactory(shared_ptr<drawBasement::IDrawFactory> f){
			mDrawFactory=f;
		}

		//! 获取文件服务
		virtual shared_ptr<fileservice::IFileService> getFileService(){
			return mFileServie;
		}

		//! 安装绘制工厂
		void installFileService(shared_ptr<fileservice::IFileService> f){
			mFileServie=f;
		}



	};
}