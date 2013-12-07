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
		//! �ύ�󱸻�������ݵ���Ļ
		void COGLESContext::presentData(){
			
		}
		//! �����Ļ��ɫ
		void COGLESContext::clearScreenColor(colorf c){
			if(m_ClearColor != c){
				m_ClearColor = c;
				glClearColor(m_ClearColor.r,m_ClearColor.g,m_ClearColor.b,m_ClearColor.a);
			}
			glClear(GL_COLOR_BUFFER_BIT);
		}
		//! ��ȡ���ڴ�С
		rect COGLESContext::getWindowRect(){
			return m_WindowRect;
		}
		//! ʹ����Ŀ��ת��ָ������������
		bool COGLESContext::pushRenderTexture(IDrawRenderTexture* tex){
			return true;
		}
		//! ʹ����Ŀ��ת��ָ������������
		bool COGLESContext::popRenderTexture(){
			return true;
		}
		//! �����Ȼ�����ɫ
		void COGLESContext::clearDepthBuffer(){
			glClear(GL_DEPTH_BUFFER_BIT);
		}


	}
}