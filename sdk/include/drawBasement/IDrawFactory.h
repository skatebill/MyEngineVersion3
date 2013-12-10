#pragma once
#include "IDrawBuffers.h"
#include "IDrawContext.h"
#include "ICanvas.h"
#include "IDrawProgram.h"
#include "IDrawTexture.h"
#include "IDrawContext.h"
#include "IModel.h"
#include <tools/MyTypes.h>
#include<viewer/IMatrixStack.h>
#include<drawBasement/particlesystem/IParticleFactory.h>
namespace xc{
	namespace drawBasement{
		class IDrawFactory{
		public:
			//! 创建指定类型的着色器
			virtual IProgramFactory* getProgramFactory()=0;
			//! 创建绘制器
			virtual shared_ptr<ICanvas> createCanvas(shared_ptr<IDrawCotext> context,shared_ptr<viewer::IMatStack> matStack)=0;
			//! 创建顶点缓冲区
			virtual shared_ptr<IDrawBuffer> createVertexBuffer()=0;
			//! 创建索引缓冲区
			virtual shared_ptr<IDrawIndexBuffer> createIndexBuffer()=0;
			//! 获取纹理工厂
			virtual IDrawTextureFactory* getTextureFactory()=0;
			//! 创建绘制用VBO
			virtual shared_ptr<IDrawVertexBufferOBject> createVertexBufferObject(shared_ptr<IDrawBuffer> vbuf,
																				shared_ptr<IDrawIndexBuffer> ibuf,
																				shared_ptr<IDrawBuffer> buf1=0,
																				shared_ptr<IDrawBuffer> buf2=0,
																				shared_ptr<IDrawBuffer> buf3=0,
																				shared_ptr<IDrawBuffer> buf4=0)=0;
			//! 创建绘制上下文
			//virtual shared_ptr<IDrawCotext> createDrawContext(void* data)=0;
			//! 获得绘制上下文，一般一个app也只有一个绘制context
			virtual shared_ptr<IDrawCotext> getDrawContext()=0;

			//////////////////////////////////////////////////////////////////////////
			//! 创建模型
			virtual shared_ptr<IModel> createModel()=0;
			//////////////////////////////////////////////////////////////////////////
			virtual xc::particlesystem::IParticleFactory* getParticleFacotry()=0;
		};
	}
}