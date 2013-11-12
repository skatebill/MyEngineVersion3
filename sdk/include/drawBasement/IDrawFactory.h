#pragma once
#include "IDrawBuffers.h"
#include "IDrawContext.h"
#include "IDrawer3D.h"
#include "IDrawProgram.h"
#include "IDrawTexture.h"
#include "IDrawContext.h"
#include "MyTypes.h"
namespace xc{
	namespace drawBasement{
		class IDrawFactory{
		public:
			//! 创建指定类型的着色器
			virtual IProgramFactory* getProgramFactory()=0;
			//! 创建绘制器
			virtual shared_ptr<IDrawer3D> createDrawer()=0;
			//! 创建顶点缓冲区
			virtual shared_ptr<IDrawBuffer> createVertexBuffer()=0;
			//! 创建索引缓冲区
			virtual shared_ptr<IDrawIndexBuffer> createIndexBuffer()=0;
			//! 获取纹理工厂
			virtual IDrawTextureFactory* getTextureFactory()=0;
			//! 创建绘制上下文
			virtual shared_ptr<IDrawCotext> createDrawContext(void* data)=0;
		};
	}
}