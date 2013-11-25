/************************************************************************/
/* 骨骼动画类
	authored by 肖驰
	@	2013年11月21日19:12:25											*/
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
			//! 获取当前节点的变换矩阵
			virtual mat4 getCurrentTranslateMat()=0;
			//! 获取最终变化矩阵
			virtual mat4 getFinalTranslateMat()=0;
			//! 设置当前位置
			virtual void setCurrentFrame(f32 fPos)=0;
			//! 获取骨骼节点的最大关键帧位置
			virtual f32 getMaxFrame()=0;
			//! 获取骨骼名
			virtual const char* getBoneName()=0;
			//! 获取骨骼索引位置
			virtual const u32 getBoneIdx()=0;
		};
		class IBoneAnimator{
		public:
			//! 获取动画一帧的时间
			virtual f32 getPerFrameTime()=0;
			//! 获取当前动画位置
			virtual f32 getCurrentFramePos()=0;
			//! 获取动画帧数
			virtual u32 getNumFrames()=0;
			//! 设置当前位置
			virtual void setCurrentFrame(f32 fPos)=0;
			//! 找到指定骨骼
			virtual shared_ptr<IBone> findBones(const char* bonename)=0;
			//! 获取骨骼变换矩阵的缓冲区首地址
			virtual void* getUniformMatrixBuffer()=0;
			//! 获取骨骼数量
			virtual u32 getUniformMatrixSize()=0;
		};
	}
}