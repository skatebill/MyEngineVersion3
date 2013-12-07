#pragma once
#include<drawBasement/IDrawProgram.h>
namespace xc{
	namespace drawBasement{
		class COGLESProgramFactory:public IProgramFactory{
		public:
			//! �����������shader
			virtual shared_ptr<IBaseProgram> createBaseProgram();
			//! �������ٰ汾�Ļ���shader
			virtual shared_ptr<IBaseProgramQ> createBaseQuickProgram();
			//! �������ٰ汾�Ļ�������shader
			virtual shared_ptr<IBasedTextureProgramQ> createBaseQuickTextureProgram();
			//! �������ٰ汾�Ĺ�������shader
			virtual shared_ptr<IBonedProgramQ> createBaseQuickBonedProgram();

		};
	}
}