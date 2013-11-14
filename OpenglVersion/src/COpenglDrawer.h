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
			//! ָ�������õ�program 
			//! ����ָ������
			virtual void draw(IDrawBuffer* vbuf,IDrawIndexBuffer* ibuf);
		};
	}
}