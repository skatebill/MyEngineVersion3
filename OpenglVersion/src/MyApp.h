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
			shared_ptr<drawBasement::IBaseProgramQ> mProg2;
			shared_ptr<drawBasement::ICanvas> mCanvas;
			shared_ptr<viewer::ICamera> mCamera;
			shared_ptr<drawBasement::IDrawTexture2D> mtexture;
			shared_ptr<xc::drawBasement::IDrawVertexBufferOBject> m_VBO;
			shared_ptr<xc::drawBasement::IDrawVertexBufferOBject> m_VBO2;
			shared_ptr<xc::drawBasement::IModel> mModle;
			shared_ptr<drawBasement::IBonedProgramQ> mBoneProg;
		public:
			//////////////////////////////////////////////////////////////////////////
			//	接口
			//  UI 事件
			//! 初始化窗口信息
			virtual void onInitialWindow(std::function<void(const wchar_t*)> namefun,std::function<void(unsigned int,unsigned int)> sizeFun){
				namefun(L"hello world");
				sizeFun(800,600);
			}
			//! 初始化
			virtual void onInitialData();
			//! 销毁
			virtual void onCleanup();
			//! 绘制
			virtual void onRender();

		};

	}
}