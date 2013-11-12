#pragma once
#include<IDrawContext.h>
#include <windows.h>

namespace xc{
	namespace drawBasement{
		class COpenglContext:public IDrawCotext{
		private:
			HWND m_Hwnd;
			rect m_WindowRect;
			HDC m_DC;
			HGLRC m_RC;
			colorf m_ClearColor;
			void initial();
		public:
			explicit COpenglContext(HWND hwnd);
			~COpenglContext();

			//! 清空深度缓存
			virtual void clearDepthBuffer();
			//! 清空屏幕颜色
			virtual void clearScreenColor(colorf c);
			//! 提交后备缓冲的数据到屏幕
			virtual void presentData();
			//! 获取窗口大小
			virtual rect getWindowRect();
			//! 使绘制目标转入指定的离屏纹理
			virtual bool setRenderTexture(IDrawRenderTexture* tex);
			void clean();
		};
	}
}