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

			//! ��ȡ�����С
			virtual rect getTextureSize();
			//! ʹ������
			void use(int pos);
			//! ʹ�����
			void unUse();
			//! ���������С
			void setTextureSize(rect size);

		};

		class COGLESTextureFactory:public IDrawTextureFactory{
		public:
			//! ��������
			virtual shared_ptr<IDrawTexture2D> createTexture();
			//! ����Rtt����
			virtual shared_ptr<IDrawRenderTexture> createRenderTexture();
			//! ͨ���ļ���������
			virtual shared_ptr<IDrawTexture2D> createTextureFromImage(fileservice::IImage* image);

		};
	}
}