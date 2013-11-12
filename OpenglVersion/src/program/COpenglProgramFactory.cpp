#include "COpenglProgramFactory.h"
#include "COpenglBaseProgram.h"
namespace xc{
	namespace drawBasement{

		//! 创建最基本的shader
		shared_ptr<IBaseProgram> COpenglProgramFactory::createBaseProgram(){
			return 0;
		}
		//! 创建快速版本的基本shader
		shared_ptr<IBaseProgramQ> COpenglProgramFactory::createBaseQuickProgram(){
			return shared_ptr<IBaseProgramQ>(new COpenglBaseProgramQ);
		}
		//! 创建快速版本的基本纹理shader
		shared_ptr<IBasedTextureProgramQ> COpenglProgramFactory::createBaseQuickTextureProgram(){
			return 0;
		}
	}
}