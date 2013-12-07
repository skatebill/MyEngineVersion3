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
			//! ����rtt
			virtual bool popRenderTexture();
			void clean();
		};
	}
}