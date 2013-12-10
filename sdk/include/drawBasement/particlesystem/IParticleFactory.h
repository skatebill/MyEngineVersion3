#pragma once
#include"IParticleSystem.h"
namespace xc{
	namespace particlesystem{
		class IParticleFactory{
		public:
			//! 获得火焰粒子系统工厂
			virtual IFireSystemFactory* getFireFactory()=0;
		};
	}
}