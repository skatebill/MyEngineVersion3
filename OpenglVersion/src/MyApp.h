#pragma once
#include<application/IApplication.h>
namespace xc{
	namespace app{
		class myapp:public xc::app::IApplication{
		public:
			//////////////////////////////////////////////////////////////////////////
			//	�ӿ�
			//  UI �¼�
			//! ��ʼ��������Ϣ
			virtual void onInitialWindow(std::function<void(const char*)> namefun,std::function<void(unsigned int,unsigned int)> sizeFun){

			}
			//! ����¼�
			virtual void onMouseEvent(EnumMouse mouse,MouseEvent event,vector2di pos){

			}
			//! �����¼�
			virtual void onKeyEvent(KeyEvent key,int keyCode){

			}
			//! ��ʼ��
			virtual void onInitialData(){

			}
			//! ����
			virtual void onCleanup(){

			}

		};
	}
}
#define CLASS_REG xc::app::myapp