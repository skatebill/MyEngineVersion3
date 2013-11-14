#include"MyApp.h"
#include "irrMath.h"
namespace xc{
	namespace app{
		//! ����¼�
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
		//! �����¼�
		void myapp::onKeyEvent(KeyEvent key,int keyCode){
		}
		//! ��ʼ��
		void myapp::onInitialData(){
			m_Context = this->getSite()->getDrawFactory()->createDrawContext(getExtraData());
			mScreenColor = color::RED;

		}
		//! ����
		void myapp::onCleanup(){

		}
		//! ����
		void myapp::onRender(){
			m_Context->clearScreenColor(mScreenColor);
			m_Context->presentData();
		}
	}
}