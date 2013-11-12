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

		//! ����ָ�����͵���ɫ��
		IProgramFactory* COpenglFactory::getProgramFactory(){
			return m_ProgramFactory.get();
		}
		//! ����������
		shared_ptr<IDrawer3D> COpenglFactory::createDrawer(){
			return shared_ptr<IDrawer3D>(new COpenglDrawer);
		}
		//! �������㻺����
		shared_ptr<IDrawBuffer> COpenglFactory::createVertexBuffer(){
			return shared_ptr<IDrawBuffer>(new COpenglBuffer);
		}
		//! ��������������
		shared_ptr<IDrawIndexBuffer> COpenglFactory::createIndexBuffer(){
			return shared_ptr<IDrawIndexBuffer>(new COpenglIndexBuffer);
		}
		//! ��ȡ������
		IDrawTextureFactory* COpenglFactory::getTextureFactory(){
			return m_TextureFactory.get();
		}
		//! ��������������
		shared_ptr<IDrawCotext> COpenglFactory::createDrawContext(void* data){
			HWND* h = (HWND*)data;
			return shared_ptr<IDrawCotext>(new COpenglContext(*h));
		}
	}
}