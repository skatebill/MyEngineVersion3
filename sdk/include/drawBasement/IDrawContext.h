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
			//! 获取坐标系类型
			virtual EnumCoordinateType getCoordinateType()=0;
			//! 提交后备缓冲的数据到屏幕
			virtual void presentData()=0;
			//! 清空屏幕颜色
			virtual void clearScreenColor(colorf c)=0;
			//! 清空深度缓存
			virtual void clearDepthBuffer()=0;
			//! 获取窗口大小
			virtual rect getWindowRect()=0;
			//! 使绘制目标转入指定的离屏纹理
			virtual bool setRenderTexture(IDrawRenderTexture* tex)=0;
		};
	}
}