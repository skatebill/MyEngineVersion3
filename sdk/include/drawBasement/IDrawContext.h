#pragma once
#include<tools/MyTypes.h>
#include"IDrawTexture.h"
namespace xc{
	namespace drawBasement{
		enum EnumCoordinateType{
			RIGHT_HAND,
			LEFT_HAND
		};
		class IDrawCotext{
		public:
			//! ��ȡ����ϵ����
			virtual EnumCoordinateType getCoordinateType()=0;
			//! �ύ�󱸻�������ݵ���Ļ
			virtual void presentData()=0;
			//! �����Ļ��ɫ
			virtual void clearScreenColor(colorf c)=0;
			//! �����Ȼ���
			virtual void clearDepthBuffer()=0;
			//! ��ȡ���ڴ�С
			virtual rect getWindowRect()=0;
			//! ʹ����Ŀ��ת��ָ������������
			virtual bool pushRenderTexture(IDrawRenderTexture* tex)=0;
			//! ����һ��rtt
			virtual bool popRenderTexture()=0;
		};
	}
}