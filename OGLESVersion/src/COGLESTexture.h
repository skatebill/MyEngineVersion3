#include <drawBasement/IDrawTexture.h>
#include "GLES2\gl2.h"
namespace xc{
	namespace drawBasement{
		class COGLESTexture:public IDrawTexture2D{
		private:
			rect m_TextureSize;
			GLuint m_TextureHandle;
		public:
			explicit COGLESTexture();
			~COGLESTexture();

			//! 获取纹理大小
			virtual rect getTextureSize();
			//! 使用纹理
			void use(int pos);
			//! 使用完毕
			void unUse();
			//! 设置纹理大小
			void setTextureSize(rect size);

		};

		class COGLESTextureFactory:public IDrawTextureFactory{
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