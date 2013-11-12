#include"COpenglContext.h"
#include <exception>
#include <GL/glew.h>
namespace xc{
	namespace drawBasement{

		COpenglContext::COpenglContext(HWND hwnd):m_Hwnd(hwnd){
			initial();
		}
		COpenglContext::~COpenglContext(){
			clean();

		}

		void COpenglContext::initial(){
			::RECT wr;
			
			if(!GetWindowRect(m_Hwnd,&wr)){
				return;
			}
			m_WindowRect.UpperLeftCorner.X=0;
			m_WindowRect.UpperLeftCorner.Y=0;

			m_WindowRect.LowerRightCorner.X=wr.right-wr.left;
			m_WindowRect.LowerRightCorner.Y=wr.bottom-wr.top;

			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
				PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
				32,                        //Colordepth of the framebuffer.
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				24,                        //Number of bits for the depthbuffer
				8,                        //Number of bits for the stencilbuffer
				0,                        //Number of Aux buffers in the framebuffer.
				PFD_MAIN_PLANE,
				0,
				0, 0, 0
			};
			m_DC = GetDC(m_Hwnd);
			int  r = ChoosePixelFormat(m_DC,&pfd);
			if(!r)
			{
				throw std::exception("error choosing pixelformat");
				return;
			}
			if(!SetPixelFormat(m_DC,r,&pfd)){
				throw std::exception("error set pixelformat");
				return;
			}
			m_RC = wglCreateContext(m_DC);
			if(m_RC == nullptr){
				throw std::exception("error create context");
				return;
			}
			wglMakeCurrent(m_DC,m_RC);
			glewInit();
			glClearColor(m_ClearColor.r,m_ClearColor.g,m_ClearColor.b,m_ClearColor.a);
		}
		void COpenglContext::clean(){
			wglMakeCurrent(m_DC,NULL);
			if(m_RC != nullptr) wglDeleteContext(m_RC);

		}
		//! 提交后备缓冲的数据到屏幕
		void COpenglContext::presentData(){
			SwapBuffers(m_DC);
		}
		//! 清空屏幕颜色
		void COpenglContext::clearScreenColor(colorf c){
			if(m_ClearColor != c){
				m_ClearColor = c;
				glClearColor(m_ClearColor.r,m_ClearColor.g,m_ClearColor.b,m_ClearColor.a);
			}
			glClear(GL_COLOR_BUFFER_BIT);
		}
		//! 获取窗口大小
		rect COpenglContext::getWindowRect(){
			return m_WindowRect;
		}
		//! 使绘制目标转入指定的离屏纹理
		bool COpenglContext::setRenderTexture(IDrawRenderTexture* tex){
			return true;
		}
		//! 清空深度缓存颜色
		void COpenglContext::clearDepthBuffer(){
			glClear(GL_DEPTH_BUFFER_BIT);
		}


	}
}