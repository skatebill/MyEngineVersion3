#pragma once
#include<application/IApplication.h>
namespace xc{
	namespace app{
		class myapp:public xc::app::IApplication{
		private:
			shared_ptr<drawBasement::IDrawCotext> m_Context;
		public:
			//////////////////////////////////////////////////////////////////////////
			//	�ӿ�
			//  UI �¼�
			//! ��ʼ��������Ϣ
			virtual void onInitialWindow(std::function<void(const wchar_t*)> namefun,std::function<void(unsigned int,unsigned int)> sizeFun){
				namefun(L"������");
				sizeFun(800,600);
			}
			//! ����¼�
			virtual void onMouseEvent(EnumMouse mouse,MouseEvent event,vector2di pos);
			//! �����¼�
			virtual void onKeyEvent(KeyEvent key,int keyCode);
			//! ��ʼ��
			virtual void onInitialData();
			//! ����
			virtual void onCleanup();
			//! ����
			virtual void onRender();

		};
	}
}
#define CLASS_REG xc::app::myapp