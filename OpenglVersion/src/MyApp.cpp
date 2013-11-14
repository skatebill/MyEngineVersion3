#include"MyApp.h"
#include "irrMath.h"
namespace xc{
	namespace app{
		//! 鼠标事件
		void myapp::onMouseEvent(EnumMouse mouse,MouseEvent ev,vector2di pos){
			switch (mouse)
			{
			case xc::app::Mouse_L:
				{
					switch (ev)
					{
					case xc::app::Mouse_Click:
						{
							mScreenColor = color::WHITE;
						}
						break;
					case xc::app::Mouse_Down:
						{

						}
						break;
					case xc::app::Mouse_Up:
						{

						}
						break;
					case xc::app::Mouse_DClick:
						{
							mScreenColor = color::BLACK;

						}
						break;
					default:
						break;
					}
				}
				break;
			case xc::app::Mouse_R:
				{
					switch (ev)
					{
					case xc::app::Mouse_Click:
						{
							mScreenColor = color::GREEN;

						}
						break;
					case xc::app::Mouse_Down:
						{

						}
						break;
					case xc::app::Mouse_Up:
						{

						}
						break;
					case xc::app::Mouse_DClick:
						{
							mScreenColor = color::BLUE;

						}
						break;
					default:
						break;
					}				

				}
				break;
			case xc::app::Mouse_M:
				break;
			default:
				break;
			}
		}
		//! 键盘事件
		void myapp::onKeyEvent(KeyEvent key,int keyCode){
		}
		//! 初始化
		void myapp::onInitialData(){
			m_Context = this->getSite()->getDrawFactory()->createDrawContext(getExtraData());
			mScreenColor = color::RED;

		}
		//! 销毁
		void myapp::onCleanup(){

		}
		//! 绘制
		void myapp::onRender(){
			m_Context->clearScreenColor(mScreenColor);
			m_Context->presentData();
		}
	}
}