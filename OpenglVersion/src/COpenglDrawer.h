#pragma once
#include <IDrawer3D.h>
namespace xc{
	namespace drawBasement{
		class COpenglDrawer:public IDrawer3D{
		private:
			shared_ptr<IDrawCotext> mContext;
		public:
			COpenglDrawer(shared_ptr<IDrawCotext> context){
				mContext = context;
			}
			//! 指定绘制用的program 
			//! 绘制指定物体
			virtual void draw(IDrawBuffer* vbuf,IDrawIndexBuffer* ibuf);
		};
	}
}