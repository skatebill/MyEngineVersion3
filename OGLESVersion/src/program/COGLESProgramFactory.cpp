#include "COGLESProgramFactory.h"
#include "COGLESBaseProgram.hpp"
#include "COGLESTexturedProgram.hpp"
#include "COGLESBonedProgram.hpp"
namespace xc{
	namespace drawBasement{

		//! 创建最基本的shader
		shared_ptr<IBaseProgram> COGLESProgramFactory::createBaseProgram(){
			return 0;
		}
		//! 创建快速版本的基本shader
		shared_ptr<IBaseProgramQ> COGLESProgramFactory::createBaseQuickProgram(){
			COGLESBaseProgramQ<IBaseProgramQ>* r(new COGLESBaseProgramQ<IBaseProgramQ>);
			r->initialProgram();
			return shared_ptr<IBaseProgramQ>(r);
		}
		//! 创建快速版本的基本纹理shader
		shared_ptr<IBasedTextureProgramQ> COGLESProgramFactory::createBaseQuickTextureProgram(){
			COGLESTexturedProgramQ<IBasedTextureProgramQ>* r(new COGLESTexturedProgramQ<IBasedTextureProgramQ>);
			r->initialProgram();
			return shared_ptr<IBasedTextureProgramQ>(r);
		}
		//! 创建快速版本的骨骼动画shader
		shared_ptr<IBonedProgramQ> COGLESProgramFactory::createBaseQuickBonedProgram(){
			COGLESBonedProgramQ<IBonedProgramQ>* r(new COGLESBonedProgramQ<IBonedProgramQ>);
			r->initialProgram();
			return shared_ptr<IBonedProgramQ>(r);
		}
	}
}