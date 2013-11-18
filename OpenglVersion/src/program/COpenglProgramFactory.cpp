#include "COpenglProgramFactory.h"
#include "COpenglBaseProgram.hpp"
#include "COpenglTexturedProgram.hpp"
namespace xc{
	namespace drawBasement{

		//! 创建最基本的shader
		shared_ptr<IBaseProgram> COpenglProgramFactory::createBaseProgram(){
			return 0;
		}
		//! 创建快速版本的基本shader
		shared_ptr<IBaseProgramQ> COpenglProgramFactory::createBaseQuickProgram(){
			COpenglBaseProgramQ<IBaseProgramQ>* r(new COpenglBaseProgramQ<IBaseProgramQ>);
			r->initialProgram();
			return shared_ptr<IBaseProgramQ>(r);
		}
		//! 创建快速版本的基本纹理shader
		shared_ptr<IBasedTextureProgramQ> COpenglProgramFactory::createBaseQuickTextureProgram(){
			COpenglTexturedProgramQ<IBasedTextureProgramQ>* r(new COpenglTexturedProgramQ<IBasedTextureProgramQ>);
			r->initialProgram();
			return shared_ptr<IBasedTextureProgramQ>(r);
		}
	}
}