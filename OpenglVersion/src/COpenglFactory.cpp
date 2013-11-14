#include "COpenglFactory.h"
#include"COpenglContext.h"
#include"program/COpenglProgramFactory.h"
#include"COpenglDrawer.h"
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
		shared_ptr<IDrawer3D> COpenglFactory::createDrawer(shared_ptr<IDrawCotext> context){
			return shared_ptr<IDrawer3D>(new COpenglDrawer(context));
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
		shared_ptr<IDrawCotext> COpenglFactory::createDrawContext(void* data){
			HWND* h = (HWND*)data;
			return shared_ptr<IDrawCotext>(new COpenglContext(*h));
		}
	}
}