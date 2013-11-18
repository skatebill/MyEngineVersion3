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
			//	接口
			//  UI 事件
			//! 初始化窗口信息
			virtual void onInitialWindow(std::function<void(const wchar_t*)> namefun,std::function<void(unsigned int,unsigned int)> sizeFun){
				namefun(L"测试用");
				sizeFun(800,600);
			}
			//! 鼠标事件
			virtual void onMouseEvent(EnumMouse mouse,MouseEvent event,vector2di pos);
			//! 键盘事件
			virtual void onKeyEvent(KeyEvent key,int keyCode);
			//! 初始化
			virtual void onInitialData();
			//! 销毁
			virtual void onCleanup();
			//! 绘制
			virtual void onRender();

		};
	}
}
#define CLASS_REG xc::app::myapp