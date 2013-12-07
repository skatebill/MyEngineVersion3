#pragma once
#include<tools/MyTypes.h>
#include<service/file/IImage.h>
namespace xc{
	namespace drawBasement{

		//! ����������
		class IDrawTexture2D{
		public:
			//! ��ȡ�����С
			virtual rect getTextureSize()=0;
			//! ��ָ��λ��ʹ������
			virtual void use(int slot)=0;
		};
		//! rtt����������
		class IDrawRenderTexture:public IDrawTexture2D{
		public:

		};
		class IDrawTextureFactory{
		public:
			//! ��������
			virtual shared_ptr<IDrawTexture2D> createTexture()=0;
			//! ����Rtt����
			virtual shared_ptr<IDrawRenderTexture> createRenderTexture()=0;
			//! ͨ���ļ���������
			virtual shared_ptr<IDrawTexture2D> createTextureFromImage(fileservice::IImage* image)=0;
		};
	}
}