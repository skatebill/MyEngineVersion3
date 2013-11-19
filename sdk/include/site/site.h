#pragma once
#include <IDrawFactory.h>
#include<MyTypes.h>
#include<service/file/IFileService.h>
#include<viewer/IViewFactory.h>
#include<service/phraser/IPhraseSerivce.h>
namespace xc{
	class ISite{
	public:
		//! ��ȡ���ƹ���
		virtual shared_ptr<drawBasement::IDrawFactory> getDrawFactory()=0;
		//! ��ȡ�ļ�����
		virtual shared_ptr<fileservice::IFileService> getFileService()=0;
		//! ��ȡView����
		virtual shared_ptr<viewer::IViewerFactory> getViewerFactory()=0;
		//! ��ȡģ�ͽ�������
		virtual shared_ptr<phraser::IPhraserService> getPhraser()=0;
	};
	class ISiteEdieable:public ISite{
	private:
		shared_ptr<drawBasement::IDrawFactory> mDrawFactory;
		shared_ptr<fileservice::IFileService> mFileServie;
		shared_ptr<viewer::IViewerFactory> mViewerFactory;
		shared_ptr<phraser::IPhraserService> mPhraser;
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


		//! ��װView����
		void installViewerFactory(shared_ptr<viewer::IViewerFactory> f){
			mViewerFactory=f;
		}

		//! ��ȡView����
		virtual shared_ptr<viewer::IViewerFactory> getViewerFactory(){
			return mViewerFactory;
		}

		//! ��װView����
		void installPhraser(shared_ptr<phraser::IPhraserService> f){
			mPhraser=f;
		}
		virtual shared_ptr<phraser::IPhraserService> getPhraser(){
			return mPhraser;
		}

	};
}