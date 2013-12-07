#include "COGLESFactory.h"
#include"COGLESContext.h"
#include"program/COGLESProgramFactory.h"
#include"COGLESCanvas.h"
#include"COGLESBuffer.h"
#include"COGLESTexture.h"
namespace xc{
	namespace drawBasement{

		COGLESFactory::COGLESFactory(){
			m_ProgramFactory = shared_ptr<IProgramFactory>(new COGLESProgramFactory);
			m_TextureFactory = shared_ptr<IDrawTextureFactory>(new COGLESTextureFactory);
		}

		//! 创建指定类型的着色器
		IProgramFactory* COGLESFactory::getProgramFactory(){
			return m_ProgramFactory.get();
		}
		//! 创建绘制器
		shared_ptr<ICanvas> COGLESFactory::createCanvas(shared_ptr<IDrawCotext> context,shared_ptr<viewer::IMatStack> matStack){
			return shared_ptr<ICanvas>(new COGLESCanvas(context,matStack));
		}
		//! 创建顶点缓冲区
		shared_ptr<IDrawBuffer> COGLESFactory::createVertexBuffer(){
			return shared_ptr<IDrawBuffer>(new COGLESBuffer);
		}
		//! 创建索引缓冲区
		shared_ptr<IDrawIndexBuffer> COGLESFactory::createIndexBuffer(){
			return shared_ptr<IDrawIndexBuffer>(new COGLESIndexBuffer);
		}
		//! 获取纹理工厂
		IDrawTextureFactory* COGLESFactory::getTextureFactory(){
			return m_TextureFactory.get();
		}
		//! 创建绘制上下文
		shared_ptr<IDrawCotext> COGLESFactory::createDrawContext(rect data){
			m_DrawContext =  shared_ptr<IDrawCotext>(new COGLESContext(data));
			return m_DrawContext;
		}
		shared_ptr<IDrawCotext> COGLESFactory::getDrawContext(){
			return m_DrawContext;
		}

		//! 创建绘制用VBO
		shared_ptr<IDrawVertexBufferOBject> COGLESFactory::createVertexBufferObject(shared_ptr<IDrawBuffer> vbuf,
			shared_ptr<IDrawIndexBuffer> ibuf,
			shared_ptr<IDrawBuffer> buf1,
			shared_ptr<IDrawBuffer> buf2,
			shared_ptr<IDrawBuffer> buf3,
			shared_ptr<IDrawBuffer> buf4){
				COGLESVertexBufferObject* r = new COGLESVertexBufferObject;
				r->initialStart();
				r->addVertexBuf(vbuf);
				r->bindIndexBuf(ibuf);
				if(buf1!=0) r->addVertexBuf(buf1);
				if(buf2!=0) r->addVertexBuf(buf2);
				if(buf3!=0) r->addVertexBuf(buf3);
				if(buf4!=0) r->addVertexBuf(buf4);
				r->initialEnd();
				return shared_ptr<IDrawVertexBufferOBject>(r);
		}
	}
}