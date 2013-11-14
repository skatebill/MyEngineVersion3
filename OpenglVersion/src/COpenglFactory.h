#include<IDrawFactory.h>
namespace xc{
	namespace drawBasement{
		class COpenglFactory:public IDrawFactory{
		private:
			shared_ptr<IDrawTextureFactory> m_TextureFactory;
			shared_ptr<IProgramFactory> m_ProgramFactory;
		public:
			explicit COpenglFactory();

			//! 创建指定类型的着色器
			virtual IProgramFactory* getProgramFactory();
			//! 创建绘制器
			virtual shared_ptr<IDrawer3D> createDrawer(shared_ptr<IDrawCotext> context);
			//! 创建顶点缓冲区
			virtual shared_ptr<IDrawBuffer> createVertexBuffer();
			//! 创建索引缓冲区
			virtual shared_ptr<IDrawIndexBuffer> createIndexBuffer();
			//! 获取纹理工厂
			virtual IDrawTextureFactory* getTextureFactory();
			//! 创建绘制上下文
			virtual shared_ptr<IDrawCotext> createDrawContext(void* data);

		};
	}
}