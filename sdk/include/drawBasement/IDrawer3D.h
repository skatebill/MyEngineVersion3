//////////////////////////////////////////////////////////////////////////
//
//		3d�������Ľӿ�
//		����ʹ�ø�����program resource context ����3d����
//		author by Ф�� @ 2013��11��3��2:42:15
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDrawBuffers.h"
#include "IDrawContext.h"
namespace xc{
	namespace drawBasement{

		class IDrawer3D{
		public:
			//! ָ�������õ�program 
			//! ����ָ������
			virtual void draw(IDrawBuffer* vbuf,IDrawIndexBuffer* ibuf,IDrawCotext* context)=0;
			//! ����ָ������
			void draw(shared_ptr<IDrawBuffer> vbuf,shared_ptr<IDrawIndexBuffer> ibuf,shared_ptr<IDrawCotext> context){
				draw(vbuf.get(),ibuf.get(),context.get());
			}
		};
	}
}