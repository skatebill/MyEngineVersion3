#pragma once
#include<IDrawProgram.h>
namespace xc{
	namespace drawBasement{
		class COpenglProgramFactory:public IProgramFactory{
		public:
			//! �����������shader
			virtual shared_ptr<IBaseProgram> createBaseProgram();
			//! �������ٰ汾�Ļ���shader
			virtual shared_ptr<IBaseProgramQ> createBaseQuickProgram();
			//! �������ٰ汾�Ļ�������shader
			virtual shared_ptr<IBasedTextureProgramQ> createBaseQuickTextureProgram();
			//! �������ٰ汾�Ĺ�������shader
			virtual shared_ptr<IBonedProgramQ> createBaseQuickBonedProgram();
			//! �������ٰ汾�Ķ�����ɫshader
			virtual shared_ptr<IPosColorProgramQ> createBaseQuickPosColorProgram(){
				return 0;
			}

		};
	}
}