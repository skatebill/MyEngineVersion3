/************************************************************************/
/* 骨骼动画类
	authored by 肖驰
	@	2013年11月21日19:12:25											*/
/************************************************************************/
#pragma once
#include<MyTypes.h>
namespace xc{
	namespace drawBasement{
		class IBone{
		private:
			//! 获取父骨骼
			virtual IBone* getParent()=0;
			//! 获取当前节点的变换矩阵
			virtual mat4 getCurrentTranslateMat()=0;
		};
		class IBoneAnimetor{
		public:
			//! 获取动画帧数
			virtual u32 getNumFrames()=0;
			//! 设置当前帧数
			virtual void setCurrentFrame(f32 fPos)=0;
		};
	}
}