//////////////////////////////////////////////////////////////////////////
//		绘制管线的着色器接口
//		author by 肖驰 @ 2013年11月3日2:44:18
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MyTypes.h"
#include<IDrawTexture.h>
namespace xc{
	namespace drawBasement{
		enum EnumProgramType
		{
			EPT_BaseType=0,
			EPT_Textured,
			EPT_Normaled
		};
		class IDrawProgram{
		public:
			//! 准备绘制（做一些准备工作）
			virtual void prepareDraw()=0;
			//! 做一些收尾工作
			virtual void endDraw()=0;
			//! 表明是哪一种着色器
			virtual EnumProgramType type()=0;
		};

		class IBaseProgramQ:public IDrawProgram{
		public:
			//! 上传变换矩阵
			virtual void uploadMatrix(mat4f mat)=0;
			//! 上传颜色
			virtual void uploadColor(colorf c)=0;
		};

		class IBaseProgram:public IDrawProgram{
		public:
			//! 上传世界变换矩阵
			virtual void uploadWorldTranslateMatrix(mat4f mat)=0;
			//! 上传投影变换矩阵
			virtual void uploadProjectionMatrix(mat4f mat)=0;
			//! 上传视点变换矩阵
			virtual void uploadViewMatrix(mat4f mat)=0;
			//! 上传颜色
			virtual void uploadColor(colorf c)=0;
		};

		class IBasedTextureProgramQ:public IDrawProgram{
		public:
			//! 上传纹理
			virtual void uploadTexture(IDrawTexture2D* tex)=0;
			//! 上传变换矩阵
			virtual void uploadMatrix(mat4f mat)=0;
		};

		class IProgramFactory{
		public:
			//! 创建最基本的shader
			virtual shared_ptr<IBaseProgram> createBaseProgram()=0;
			//! 创建快速版本的基本shader
			virtual shared_ptr<IBaseProgramQ> createBaseQuickProgram()=0;
			//! 创建快速版本的基本纹理shader
			virtual shared_ptr<IBasedTextureProgramQ> createBaseQuickTextureProgram()=0;
		};

	}
}