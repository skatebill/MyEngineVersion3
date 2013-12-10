#include "CParticleSystem.h"
#include"CParticleFactory.h"
#include "CRectFireParticle.h"
namespace xc{
	namespace particlesystem{

		//! 创建最简单的火焰粒子系统
		shared_ptr<IRectFireSystem> CFireSystemFactory::createRectFire(shared_ptr<drawBasement::IPosColorProgramQ> program){
			return shared_ptr<IRectFireSystem>(new CRectFireSystem(program));
		}
	}
}