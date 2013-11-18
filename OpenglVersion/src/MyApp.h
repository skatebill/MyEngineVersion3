#pragma once
#include<application/IApplication.h>
namespace xc{
	namespace app{
		class myapp:public xc::app::IApplication{
		private:
			shared_ptr<drawBasement::IDrawCotext> m_Context;
			colorf mScreenColor;
			shared_ptr<drawBasement::IDrawBuffer> mVertex;
			shared_ptr<drawBasement::IDrawBuffer> mtex;
			shared_ptr<drawBasement::IDrawIndexBuffer> mIndex;
			shared_ptr<drawBasement::IBasedTextureProgramQ> mProg;
			shared_ptr<drawBasement::ICanvas> mCanvas;
			shared_ptr<viewer::ICamera> mCamera;
			shared_ptr<drawBasement::IDrawTexture2D> mtexture;
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