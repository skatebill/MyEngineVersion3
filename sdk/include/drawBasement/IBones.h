/************************************************************************/
/* ����������
	authored by Ф��
	@	2013��11��21��19:12:25											*/
/************************************************************************/
#pragma once
#include<MyTypes.h>
namespace xc{
	namespace drawBasement{
		class IBone{
		private:
			//! ��ȡ������
			virtual IBone* getParent()=0;
			//! ��ȡ��ǰ�ڵ�ı任����
			virtual mat4 getCurrentTranslateMat()=0;
		};
		class IBoneAnimetor{
		public:
			//! ��ȡ����֡��
			virtual u32 getNumFrames()=0;
			//! ���õ�ǰ֡��
			virtual void setCurrentFrame(f32 fPos)=0;
		};
	}
}