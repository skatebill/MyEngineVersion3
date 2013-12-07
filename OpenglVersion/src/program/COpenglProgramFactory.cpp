#include "COpenglProgramFactory.h"
#include "COpenglBaseProgram.hpp"
#include "COpenglTexturedProgram.hpp"
#include "COpenglBonedProgram.hpp"
namespace xc{
	namespace drawBasement{

		//! �����������shader
		shared_ptr<IBaseProgram> COpenglProgramFactory::createBaseProgram(){
			return 0;
		}
		//! �������ٰ汾�Ļ���shader
		shared_ptr<IBaseProgramQ> COpenglProgramFactory::createBaseQuickProgram(){
			COpenglBaseProgramQ<IBaseProgramQ>* r(new COpenglBaseProgramQ<IBaseProgramQ>);
			r->initialProgram();
			return shared_ptr<IBaseProgramQ>(r);
		}
		//! �������ٰ汾�Ļ�������shader
		shared_ptr<IBasedTextureProgramQ> COpenglProgramFactory::createBaseQuickTextureProgram(){
			COpenglTexturedProgramQ<IBasedTextureProgramQ>* r(new COpenglTexturedProgramQ<IBasedTextureProgramQ>);
			r->initialProgram();
			return shared_ptr<IBasedTextureProgramQ>(r);
		}
		//! �������ٰ汾�Ĺ�������shader
		shared_ptr<IBonedProgramQ> COpenglProgramFactory::createBaseQuickBonedProgram(){
			COpenglBonedProgramQ<IBonedProgramQ>* r(new COpenglBonedProgramQ<IBonedProgramQ>);
			r->initialProgram();
			return shared_ptr<IBonedProgramQ>(r);
		}
	}
}