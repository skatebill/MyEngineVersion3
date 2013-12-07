#pragma once
#include<drawBasement/IDrawFactory.h>
#include <drawBasement/CModel.hpp>
namespace xc{
	namespace drawBasement{
		class COGLESFactory:public IDrawFactory{
		private:
			shared_ptr<IDrawTextureFactory> m_TextureFactory;
			shared_ptr<IProgramFactory> m_ProgramFactory;
			shared_ptr<IDrawCotext> m_DrawContext;
		public:
			explicit COGLESFactory();

			//! ����ָ�����͵���ɫ��
			virtual IProgramFactory* getProgramFactory();
			//! ����������
			virtual shared_ptr<ICanvas> createCanvas(shared_ptr<IDrawCotext> context,shared_ptr<viewer::IMatStack> matStack);
			//! �������㻺����
			virtual shared_ptr<IDrawBuffer> createVertexBuffer();
			//! ��������������
			virtual shared_ptr<IDrawIndexBuffer> createIndexBuffer();
			//! ��ȡ������
			virtual IDrawTextureFactory* getTextureFactory();
			//! ��������������
			virtual shared_ptr<IDrawCotext> createDrawContext(rect data);
			//! ��ȡ����������
			virtual shared_ptr<IDrawCotext> getDrawContext();
			//! ����������VBO
			virtual shared_ptr<IDrawVertexBufferOBject> createVertexBufferObject(shared_ptr<IDrawBuffer> vbuf,
				shared_ptr<IDrawIndexBuffer> ibuf,
				shared_ptr<IDrawBuffer> buf1=0,
				shared_ptr<IDrawBuffer> buf2=0,
				shared_ptr<IDrawBuffer> buf3=0,
				shared_ptr<IDrawBuffer> buf4=0);

			//! ����ģ��
			virtual shared_ptr<IModel> createModel(){
				return shared_ptr<IModel>(new CModel);
			}
		};
	}
}