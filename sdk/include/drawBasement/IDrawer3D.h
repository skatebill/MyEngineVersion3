//////////////////////////////////////////////////////////////////////////
//
//		3d绘制器的接口
//		可以使用给定的program resource context 绘制3d内容
//		author by 肖驰 @ 2013年11月3日2:42:15
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDrawBuffers.h"
#include "IDrawContext.h"
namespace xc{
	namespace drawBasement{

		class IDrawer3D{
		public:
			//! 指定绘制用的program 
			//! 绘制指定物体
			virtual void draw(IDrawBuffer* vbuf,IDrawIndexBuffer* ibuf,IDrawCotext* context)=0;
			//! 绘制指定物体
			void draw(shared_ptr<IDrawBuffer> vbuf,shared_ptr<IDrawIndexBuffer> ibuf,shared_ptr<IDrawCotext> context){
				draw(vbuf.get(),ibuf.get(),context.get());
			}
		};
	}
}