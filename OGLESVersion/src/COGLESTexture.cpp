#include "COGLESTexture.h"

namespace xc{
	namespace drawBasement{
		COGLESTexture::COGLESTexture(){
			glGenTextures(1,&m_TextureHandle);
		}
		COGLESTexture::~COGLESTexture(){
			glDeleteTextures(1,&m_TextureHandle);
		}
		//! 获取纹理大小
		rect COGLESTexture::getTextureSize(){
			return m_TextureSize;
		}
		//! 使用纹理
		void COGLESTexture::use(int pos){
			glActiveTexture(GL_TEXTURE0+pos);
			glBindTexture(GL_TEXTURE_2D,m_TextureHandle);
		}
		//! 使用完毕
		void COGLESTexture::unUse(){
			glBindTexture(GL_TEXTURE_2D,0);
		}
		//! 设置纹理大小
		void COGLESTexture::setTextureSize(rect size){
			m_TextureSize = size;
		}

		//! 创建纹理
		shared_ptr<IDrawTexture2D> COGLESTextureFactory::createTexture(){
			return shared_ptr<IDrawTexture2D>(new COGLESTexture);
		}
		//! 创建Rtt纹理
		shared_ptr<IDrawRenderTexture> COGLESTextureFactory::createRenderTexture(){
			return 0;
		}

		shared_ptr<IDrawTexture2D> COGLESTextureFactory::createTextureFromImage(fileservice::IImage* image)
		{
			COGLESTexture* tex = new COGLESTexture;
			tex->setTextureSize(rect(0,0,image->getWitdh(),image->getHeight()));
			tex->use(0);
			GLuint colorType=GL_RGB;
			if(image->hasAlpha()) 
				colorType=GL_RGBA;
			glTexImage2D(GL_TEXTURE_2D,0,colorType,image->getWitdh(),image->getHeight(),0,colorType,GL_UNSIGNED_BYTE,image->getData());
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glGenerateMipmap(GL_TEXTURE_2D);
			return shared_ptr<IDrawTexture2D>(tex);
		}
	}
}