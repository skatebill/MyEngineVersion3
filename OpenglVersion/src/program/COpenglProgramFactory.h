#pragma once
#include<IDrawProgram.h>
namespace xc{
	namespace drawBasement{
		class COpenglProgramFactory:public IProgramFactory{
		public:
			//! 创建最基本的shader
			virtual shared_ptr<IBaseProgram> createBaseProgram();
			//! 创建快速版本的基本shader
			virtual shared_ptr<IBaseProgramQ> createBaseQuickProgram();
			//! 创建快速版本的基本纹理shader
			virtual shared_ptr<IBasedTextureProgramQ> createBaseQuickTextureProgram();
			//! 创建快速版本的骨骼动画shader
			virtual shared_ptr<IBonedProgramQ> createBaseQuickBonedProgram();

		};
	}
}