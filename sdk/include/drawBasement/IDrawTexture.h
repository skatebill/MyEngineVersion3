#pragma once
#include<tools/MyTypes.h>
#include<service/file/IImage.h>
namespace xc{
	namespace drawBasement{

		//! 绘制用纹理
		class IDrawTexture2D{
		public:
			//! 获取纹理大小
			virtual rect getTextureSize()=0;
			//! 在指定位置使用纹理
			virtual void use(int slot)=0;
		};
		//! rtt用离屏纹理
		class IDrawRenderTexture:public IDrawTexture2D{
		public:

		};
		class IDrawTextureFactory{
		public:
			//! 创建纹理
			virtual shared_ptr<IDrawTexture2D> createTexture()=0;
			//! 创建Rtt纹理
			virtual shared_ptr<IDrawRenderTexture> createRenderTexture()=0;
			//! 通过文件创建纹理
			virtual shared_ptr<IDrawTexture2D> createTextureFromImage(fileservice::IImage* image)=0;
		};
	}
}