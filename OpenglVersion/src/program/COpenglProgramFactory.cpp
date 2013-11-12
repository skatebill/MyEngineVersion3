#include "COpenglProgramFactory.h"
#include "COpenglBaseProgram.h"
namespace xc{
	namespace drawBasement{

		//! �����������shader
		shared_ptr<IBaseProgram> COpenglProgramFactory::createBaseProgram(){
			return 0;
		}
		//! �������ٰ汾�Ļ���shader
		shared_ptr<IBaseProgramQ> COpenglProgramFactory::createBaseQuickProgram(){
			return shared_ptr<IBaseProgramQ>(new COpenglBaseProgramQ);
		}
		//! �������ٰ汾�Ļ�������shader
		shared_ptr<IBasedTextureProgramQ> COpenglProgramFactory::createBaseQuickTextureProgram(){
			return 0;
		}
	}
}