#include<drawBasement/IDrawFactory.h>
#include <drawBasement/CModel.hpp>
#include <windows.h>
namespace xc{
	namespace drawBasement{
		class COpenglFactory:public IDrawFactory{
		private:
			shared_ptr<IDrawTextureFactory> m_TextureFactory;
			shared_ptr<IProgramFactory> m_ProgramFactory;
			shared_ptr<IDrawCotext> m_DrawContext;
		public:
			explicit COpenglFactory();

			//! 创建指定类型的着色器
			virtual IProgramFactory* getProgramFactory();
			//! 创建绘制器
			virtual shared_ptr<ICanvas> createCanvas(shared_ptr<IDrawCotext> context,shared_ptr<viewer::IMatStack> matStack);
			//! 创建顶点缓冲区
			virtual shared_ptr<IDrawBuffer> createVertexBuffer();
			//! 创建索引缓冲区
			virtual shared_ptr<IDrawIndexBuffer> createIndexBuffer();
			//! 获取纹理工厂
			virtual IDrawTextureFactory* getTextureFactory();
			//! 创建绘制上下文
			virtual shared_ptr<IDrawCotext> createDrawContext(HWND data);
			//! 创建绘制上下文
			virtual shared_ptr<IDrawCotext> getDrawContext();
			//! 创建绘制用VBO
			virtual shared_ptr<IDrawVertexBufferOBject> createVertexBufferObject(shared_ptr<IDrawBuffer> vbuf,
				shared_ptr<IDrawIndexBuffer> ibuf,
				shared_ptr<IDrawBuffer> buf1=0,
				shared_ptr<IDrawBuffer> buf2=0,
				shared_ptr<IDrawBuffer> buf3=0,
				shared_ptr<IDrawBuffer> buf4=0);

			//! 创建模型
			virtual shared_ptr<IModel> createModel(){
				return shared_ptr<IModel>(new CModel);
			}
			//////////////////////////////////////////////////////////////////////////
			virtual xc::particlesystem::IParticleFactory* getParticleFacotry(){
				return 0;
			}
		};
	}
}