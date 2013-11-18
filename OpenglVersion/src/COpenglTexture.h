#include <IDrawTexture.h>
#include "gl\glew.h"
namespace xc{
	namespace drawBasement{
		class COpenglTexture:public IDrawTexture2D{
		private:
			rect m_TextureSize;
			GLuint m_TextureHandle;
		public:
			explicit COpenglTexture();
			~COpenglTexture();

			//! 获取纹理大小
			virtual rect getTextureSize();
			//! 使用纹理
			void use(int pos);
			//! 使用完毕
			void unUse();
			//! 设置纹理大小
			void setTextureSize(rect size);

		};

		class COpenglTextureFactory:public IDrawTextureFactory{
		public:
			//! 创建纹理
			virtual shared_ptr<IDrawTexture2D> createTexture();
			//! 创建Rtt纹理
			virtual shared_ptr<IDrawRenderTexture> createRenderTexture();
			//! 通过文件创建纹理
			virtual shared_ptr<IDrawTexture2D> createTextureFromImage(fileservice::IImage* image);

		};
	}
}