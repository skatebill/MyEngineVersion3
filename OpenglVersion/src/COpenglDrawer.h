#pragma once
#include <IDrawer3D.h>
namespace xc{
	namespace drawBasement{
		class COpenglDrawer:public IDrawer3D{
		public:
			//! ָ�������õ�program 
			//! ����ָ������
			virtual void draw(IDrawBuffer* vbuf,IDrawIndexBuffer* ibuf,IDrawCotext* context);
		};
	}
}