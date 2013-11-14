#include<IDrawFactory.h>
namespace xc{
	namespace drawBasement{
		class COpenglFactory:public IDrawFactory{
		private:
			shared_ptr<IDrawTextureFactory> m_TextureFactory;
			shared_ptr<IProgramFactory> m_ProgramFactory;
		public:
			explicit COpenglFactory();

			//! ����ָ�����͵���ɫ��
			virtual IProgramFactory* getProgramFactory();
			//! ����������
			virtual shared_ptr<IDrawer3D> createDrawer(shared_ptr<IDrawCotext> context);
			//! �������㻺����
			virtual shared_ptr<IDrawBuffer> createVertexBuffer();
			//! ��������������
			virtual shared_ptr<IDrawIndexBuffer> createIndexBuffer();
			//! ��ȡ������
			virtual IDrawTextureFactory* getTextureFactory();
			//! ��������������
			virtual shared_ptr<IDrawCotext> createDrawContext(void* data);

		};
	}
}