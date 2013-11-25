/************************************************************************/
/* ����������
	authored by Ф��
	@	2013��11��21��19:12:25											*/
/************************************************************************/
#pragma once
#include<MyTypes.h>
#include<tools/CobjContainer.hpp>
#include <vector>
#include<exception>
#include <algorithm>
namespace xc{
	namespace drawBasement{
		class IBone{
		public:
			//! ��ȡ��ǰ�ڵ�ı任����
			virtual mat4 getCurrentTranslateMat()=0;
			//! ��ȡ���ձ仯����
			virtual mat4 getFinalTranslateMat()=0;
			//! ���õ�ǰλ��
			virtual void setCurrentFrame(f32 fPos)=0;
			//! ��ȡ�����ڵ�����ؼ�֡λ��
			virtual f32 getMaxFrame()=0;
			//! ��ȡ������
			virtual const char* getBoneName()=0;
			//! ��ȡ��������λ��
			virtual const u32 getBoneIdx()=0;
		};
		class IBoneAnimator{
		public:
			//! ��ȡ����һ֡��ʱ��
			virtual f32 getPerFrameTime()=0;
			//! ��ȡ��ǰ����λ��
			virtual f32 getCurrentFramePos()=0;
			//! ��ȡ����֡��
			virtual u32 getNumFrames()=0;
			//! ���õ�ǰλ��
			virtual void setCurrentFrame(f32 fPos)=0;
			//! �ҵ�ָ������
			virtual shared_ptr<IBone> findBones(const char* bonename)=0;
			//! ��ȡ�����任����Ļ������׵�ַ
			virtual void* getUniformMatrixBuffer()=0;
			//! ��ȡ��������
			virtual u32 getUniformMatrixSize()=0;
		};
	}
}