#include"MyApp.h"

namespace xc{
	namespace app{

		//! 鼠标事件
		void myapp::onMouseEvent(EnumMouse mouse,MouseEvent event,vector2di pos){

		}
		//! 键盘事件
		void myapp::onKeyEvent(KeyEvent key,int keyCode){

		}
		//! 初始化
		void myapp::onInitialData(){
			m_Context = this->getSite()->getDrawFactory()->createDrawContext(getExtraData());
		}
		//! 销毁
		void myapp::onCleanup(){

		}
		//! 绘制
		void myapp::onRender(){
			m_Context->clearScreenColor(xc::color::RED);
			m_Context->presentData();
		}
	}
}