#include"MyApp.h"

namespace xc{
	namespace app{

		//! ����¼�
		void myapp::onMouseEvent(EnumMouse mouse,MouseEvent event,vector2di pos){

		}
		//! �����¼�
		void myapp::onKeyEvent(KeyEvent key,int keyCode){

		}
		//! ��ʼ��
		void myapp::onInitialData(){
			m_Context = this->getSite()->getDrawFactory()->createDrawContext(getExtraData());
		}
		//! ����
		void myapp::onCleanup(){

		}
		//! ����
		void myapp::onRender(){
			m_Context->clearScreenColor(xc::color::RED);
			m_Context->presentData();
		}
	}
}