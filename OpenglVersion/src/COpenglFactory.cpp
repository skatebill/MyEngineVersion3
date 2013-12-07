#include "COpenglFactory.h"
#include"COpenglContext.h"
#include"program/COpenglProgramFactory.h"
#include"COpenglCanvas.h"
#include"COpenglBuffer.h"
#include"COpenglTexture.h"
namespace xc{
	namespace drawBasement{

		COpenglFactory::COpenglFactory(){
			m_ProgramFactory = shared_ptr<IProgramFactory>(new COpenglProgramFactory);
			m_TextureFactory = shared_ptr<IDrawTextureFactory>(new COpenglTextureFactory);
		}

		//! 创建指定类型的着色器
		IProgramFactory* COpenglFactory::getProgramFactory(){
			return m_ProgramFactory.get();
		}
		//! 创建绘制器
		shared_ptr<ICanvas> COpenglFactory::createCanvas(shared_ptr<IDrawCotext> context,shared_ptr<viewer::IMatStack> matStack){
			return shared_ptr<ICanvas>(new COpenglCanvas(context,matStack));
		}
		//! 创建顶点缓冲区
		shared_ptr<IDrawBuffer> COpenglFactory::createVertexBuffer(){
			return shared_ptr<IDrawBuffer>(new COpenglBuffer);
		}
		//! 创建索引缓冲区
		shared_ptr<IDrawIndexBuffer> COpenglFactory::createIndexBuffer(){
			return shared_ptr<IDrawIndexBuffer>(new COpenglIndexBuffer);
		}
		//! 获取纹理工厂
		IDrawTextureFactory* COpenglFactory::getTextureFactory(){
			return m_TextureFactory.get();
		}
		//! 创建绘制上下文
		shared_ptr<IDrawCotext> COpenglFactory::createDrawContext(HWND data){
			if(m_DrawContext == nullptr){
				m_DrawContext = shared_ptr<IDrawCotext>(new COpenglContext(data));
			}
			return m_DrawContext;
		}
		shared_ptr<IDrawCotext> COpenglFactory::getDrawContext(){
			return m_DrawContext;
		}


		//! 创建绘制用VBO
		shared_ptr<IDrawVertexBufferOBject> COpenglFactory::createVertexBufferObject(shared_ptr<IDrawBuffer> vbuf,
			shared_ptr<IDrawIndexBuffer> ibuf,
			shared_ptr<IDrawBuffer> buf1,
			shared_ptr<IDrawBuffer> buf2,
			shared_ptr<IDrawBuffer> buf3,
			shared_ptr<IDrawBuffer> buf4){
				COpenglVertexBufferObject* r = new COpenglVertexBufferObject;
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