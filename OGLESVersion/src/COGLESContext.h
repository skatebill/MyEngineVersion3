#pragma once
#include<drawBasement/IDrawContext.h>

namespace xc{
	namespace drawBasement{
		class COGLESContext:public IDrawCotext{
		private:
			rect m_WindowRect;
			colorf m_ClearColor;
			void initial();
		public:
			explicit COGLESContext(rect wr);
			~COGLESContext();

			//! 获取坐标系类型
			virtual EnumCoordinateType getCoordinateType(){
				return RIGHT_HAND;
			}
			//! 清空深度缓存
			virtual void clearDepthBuffer();
			//! 清空屏幕颜色
			virtual void clearScreenColor(colorf c);
			//! 提交后备缓冲的数据到屏幕
			virtual void presentData();
			//! 获取窗口大小
			virtual rect getWindowRect();
			//! 使绘制目标转入指定的离屏纹理
			virtual bool pushRenderTexture(IDrawRenderTexture* tex);
			//! 弹出rtt
			virtual bool popRenderTexture();
			void clean();
		};
	}
}