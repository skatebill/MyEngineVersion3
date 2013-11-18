#pragma once
#include<MyTypes.h>
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
			virtual bool setRenderTexture(IDrawRenderTexture* tex)=0;
		};
	}
}