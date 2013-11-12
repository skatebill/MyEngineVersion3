#pragma once
#include<application/IApplication.h>
namespace xc{
	namespace app{
		class myapp:public xc::app::IApplication{
		public:
			//////////////////////////////////////////////////////////////////////////
			//	接口
			//  UI 事件
			//! 初始化窗口信息
			virtual void onInitialWindow(std::function<void(const char*)> namefun,std::function<void(unsigned int,unsigned int)> sizeFun){

			}
			//! 鼠标事件
			virtual void onMouseEvent(EnumMouse mouse,MouseEvent event,vector2di pos){

			}
			//! 键盘事件
			virtual void onKeyEvent(KeyEvent key,int keyCode){

			}
			//! 初始化
			virtual void onInitialData(){

			}
			//! 销毁
			virtual void onCleanup(){

			}

		};
	}
}
#define CLASS_REG xc::app::myapp