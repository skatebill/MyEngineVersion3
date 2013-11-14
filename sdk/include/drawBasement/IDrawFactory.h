#pragma once
#include "IDrawBuffers.h"
#include "IDrawContext.h"
#include "IDrawer3D.h"
#include "IDrawProgram.h"
#include "IDrawTexture.h"
#include "IDrawContext.h"
#include "MyTypes.h"
namespace xc{
	namespace drawBasement{
		class IDrawFactory{
		public:
			//! ����ָ�����͵���ɫ��
			virtual IProgramFactory* getProgramFactory()=0;
			//! ����������
			virtual shared_ptr<IDrawer3D> createDrawer(shared_ptr<IDrawCotext> context)=0;
			//! �������㻺����
			virtual shared_ptr<IDrawBuffer> createVertexBuffer()=0;
			//! ��������������
			virtual shared_ptr<IDrawIndexBuffer> createIndexBuffer()=0;
			//! ��ȡ������
			virtual IDrawTextureFactory* getTextureFactory()=0;
			//! ��������������
			virtual shared_ptr<IDrawCotext> createDrawContext(void* data)=0;
		};
	}
}