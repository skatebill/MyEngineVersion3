//////////////////////////////////////////////////////////////////////////
//
//		3d绘制器的接口
//		可以使用给定的program resource context 绘制3d内容
//		author by 肖驰 @ 2013年11月3日2:42:15
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDrawBuffers.h"
#include "IDrawContext.h"
#include <viewer/ICamera.h>
#include <viewer/IMatrixStack.h>
namespace xc{
	namespace drawBasement{
		enum EnumProjectionType{
			type_ortho,
			type_perspective
		};
		class ICanvas{
		public:
			//! 设置投影方式
			virtual void setProjectionType(EnumProjectionType type,float perspective_angle)=0;
			//! 为canvas绑定camera
			virtual void attachCamera(shared_ptr<viewer::ICamera> cam)=0;
			//! 设置canvas的大小
			virtual void setCanvasRect(recti r)=0;
			//! 获取canvas的大小
			virtual recti getCanvasRect()=0;
			//! 获取投影矩阵
			virtual mat4 getProjectionMatrix()=0;
			//! 获取观察矩阵
			virtual mat4 getViewMatrix()=0;
			//! 获取世界变换矩阵
			virtual mat4 getWorldTranslateMatrix()=0;
			//! 获取矩阵变化器
			virtual viewer::IMatStack* getMatStack()=0;
			//! 指定绘制用的program 
			//! 绘制指定物体
			virtual void draw(IDrawBuffer* vbuf,IDrawIndexBuffer* ibuf)=0;
			//! 绘制指定物体
			void draw(shared_ptr<IDrawBuffer> vbuf,shared_ptr<IDrawIndexBuffer> ibuf){
				draw(vbuf.get(),ibuf.get());
			}
		};
	}
}