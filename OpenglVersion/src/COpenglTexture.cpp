#include "COpenglTexture.h"

namespace xc{
	namespace drawBasement{
		COpenglTexture::COpenglTexture(){
			glGenTextures(1,&m_TextureHandle);
		}
		COpenglTexture::~COpenglTexture(){
			glDeleteTextures(1,&m_TextureHandle);
		}
		//! 获取纹理大小
		rect COpenglTexture::getTextureSize(){
			return m_TextureSize;
		}
		//! 使用纹理
		void COpenglTexture::use(GLuint pos){
			glActiveTexture(GL_TEXTURE0+pos);
			glBindTexture(GL_TEXTURE_2D,m_TextureHandle);
		}
		//! 使用完毕
		void COpenglTexture::unUse(){
			glBindTexture(GL_TEXTURE_2D,0);
		}
		//! 设置纹理大小
		void COpenglTexture::setTextureSize(rect size){
			m_TextureSize = size;
		}

		//! 创建纹理
		shared_ptr<IDrawTexture2D> COpenglTextureFactory::createTexture(){
			return shared_ptr<IDrawTexture2D>(new COpenglTexture);
		}
		//! 创建Rtt纹理
		shared_ptr<IDrawRenderTexture> COpenglTextureFactory::createRenderTexture(){
			return 0;
		}

		shared_ptr<IDrawTexture2D> COpenglTextureFactory::createTextureFromImage(fileservice::IImage* image)
		{
			COpenglTexture* tex = new COpenglTexture;
			tex->setTextureSize(rect(0,0,image->getWitdh(),image->getHeight()));
			tex->use(0);
			GLuint colorType=GL_RGB;
			if(image->hasAlpha()) colorType=GL_RGBA;
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