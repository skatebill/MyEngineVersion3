#include"COGLESContext.h"
#include <exception>
#include <GLES2/gl2.h>
namespace xc{
	namespace drawBasement{

		COGLESContext::COGLESContext(rect wr):m_WindowRect(wr){
			initial();
		}
		COGLESContext::~COGLESContext(){
			clean();

		}

		void COGLESContext::initial(){
			glClearColor(m_ClearColor.r,m_ClearColor.g,m_ClearColor.b,m_ClearColor.a);
			//glEnable(GL_DEPTH_TEST);
		}
		void COGLESContext::clean(){

		}
		//! 提交后备缓冲的数据到屏幕
		void COGLESContext::presentData(){
			
		}
		//! 清空屏幕颜色
		void COGLESContext::clearScreenColor(colorf c){
			if(m_ClearColor != c){
				m_ClearColor = c;
				glClearColor(m_ClearColor.r,m_ClearColor.g,m_ClearColor.b,m_ClearColor.a);
			}
			glClear(GL_COLOR_BUFFER_BIT);
		}
		//! 获取窗口大小
		rect COGLESContext::getWindowRect(){
			return m_WindowRect;
		}
		//! 使绘制目标转入指定的离屏纹理
		bool COGLESContext::pushRenderTexture(IDrawRenderTexture* tex){
			return true;
		}
		//! 使绘制目标转入指定的离屏纹理
		bool COGLESContext::popRenderTexture(){
			return true;
		}
		//! 清空深度缓存颜色
		void COGLESContext::clearDepthBuffer(){
			glClear(GL_DEPTH_BUFFER_BIT);
		}


	}
}