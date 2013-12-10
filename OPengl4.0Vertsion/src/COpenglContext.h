#pragma once
#include<drawBasement/IDrawContext.h>
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

			//! ��ȡ����ϵ����
			virtual EnumCoordinateType getCoordinateType(){
				return RIGHT_HAND;
			}
			//! �����Ȼ���
			virtual void clearDepthBuffer();
			//! �����Ļ��ɫ
			virtual void clearScreenColor(colorf c);
			//! �ύ�󱸻�������ݵ���Ļ
			virtual void presentData();
			//! ��ȡ���ڴ�С
			virtual rect getWindowRect();
			//! ʹ����Ŀ��ת��ָ������������
			virtual bool pushRenderTexture(IDrawRenderTexture* tex);

			//! ����
			virtual bool popRenderTexture();

			void clean();
		};
	}
}