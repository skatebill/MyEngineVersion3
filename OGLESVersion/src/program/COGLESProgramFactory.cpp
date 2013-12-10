#include "COGLESProgramFactory.h"
#include "COGLESBaseProgram.hpp"
#include "COGLESTexturedProgram.hpp"
#include "COGLESBonedProgram.hpp"
#include "COGLESPosColorProgram.hpp"
namespace xc{
	namespace drawBasement{

		//! �����������shader
		shared_ptr<IBaseProgram> COGLESProgramFactory::createBaseProgram(){
			return 0;
		}
		//! �������ٰ汾�Ļ���shader
		shared_ptr<IBaseProgramQ> COGLESProgramFactory::createBaseQuickProgram(){
			COGLESBaseProgramQ<IBaseProgramQ>* r(new COGLESBaseProgramQ<IBaseProgramQ>);
			r->initialProgram();
			return shared_ptr<IBaseProgramQ>(r);
		}
		//! �������ٰ汾�Ļ�������shader
		shared_ptr<IBasedTextureProgramQ> COGLESProgramFactory::createBaseQuickTextureProgram(){
			COGLESTexturedProgramQ<IBasedTextureProgramQ>* r(new COGLESTexturedProgramQ<IBasedTextureProgramQ>);
			r->initialProgram();
			return shared_ptr<IBasedTextureProgramQ>(r);
		}
		//! �������ٰ汾�Ĺ�������shader
		shared_ptr<IBonedProgramQ> COGLESProgramFactory::createBaseQuickBonedProgram(){
			COGLESBonedProgramQ<IBonedProgramQ>* r(new COGLESBonedProgramQ<IBonedProgramQ>);
			r->initialProgram();
			return shared_ptr<IBonedProgramQ>(r);
		}
		//! �������ٰ汾�Ķ�����ɫshader
		shared_ptr<IPosColorProgramQ> COGLESProgramFactory::createBaseQuickPosColorProgram(){
			COGLESPosColorProgramQ<IPosColorProgramQ>* r(new COGLESPosColorProgramQ<IPosColorProgramQ>);
			r->initialProgram();
			return shared_ptr<IPosColorProgramQ>(r);

		}
	}
}