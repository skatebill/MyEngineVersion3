#pragma once
#include <drawBasement/IDrawFactory.h>
#include<tools/MyTypes.h>
#include<service/file/IFileService.h>
#include<viewer/IViewFactory.h>
#include<service/phraser/IPhraseSerivce.h>
namespace xc{
	class ISite{
	public:
		//! 获取绘制工厂
		virtual shared_ptr<drawBasement::IDrawFactory> getDrawFactory()=0;
		//! 获取文件服务
		virtual shared_ptr<fileservice::IFileService> getFileService()=0;
		//! 获取View工厂
		virtual shared_ptr<viewer::IViewerFactory> getViewerFactory()=0;
		//! 获取模型解析工厂
		virtual shared_ptr<phraser::IPhraserService> getPhraser()=0;
	};
	class ISiteEdieable:public ISite{
	private:
		shared_ptr<drawBasement::IDrawFactory> mDrawFactory;
		shared_ptr<fileservice::IFileService> mFileServie;
		shared_ptr<viewer::IViewerFactory> mViewerFactory;
		shared_ptr<phraser::IPhraserService> mPhraser;
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


		//! 安装View工厂
		void installViewerFactory(shared_ptr<viewer::IViewerFactory> f){
			mViewerFactory=f;
		}

		//! 获取View工厂
		virtual shared_ptr<viewer::IViewerFactory> getViewerFactory(){
			return mViewerFactory;
		}

		//! 安装View工厂
		void installPhraser(shared_ptr<phraser::IPhraserService> f){
			mPhraser=f;
		}
		virtual shared_ptr<phraser::IPhraserService> getPhraser(){
			return mPhraser;
		}

	};
}