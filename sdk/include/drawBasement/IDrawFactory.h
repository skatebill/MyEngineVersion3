#pragma once
#include "IDrawBuffers.h"
#include "IDrawContext.h"
#include "ICanvas.h"
#include "IDrawProgram.h"
#include "IDrawTexture.h"
#include "IDrawContext.h"
#include "MyTypes.h"
#include<viewer/IMatrixStack.h>
namespace xc{
	namespace drawBasement{
		class IDrawFactory{
		public:
			//! ����ָ�����͵���ɫ��
			virtual IProgramFactory* getProgramFactory()=0;
			//! ����������
			virtual shared_ptr<ICanvas> createCanvas(shared_ptr<IDrawCotext> context,shared_ptr<viewer::IMatStack> matStack)=0;
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