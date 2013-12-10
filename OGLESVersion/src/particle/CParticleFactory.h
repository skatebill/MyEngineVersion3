#pragma once
#include "CParticleSystem.h"
#include<drawBasement/particlesystem/IParticleFactory.h>
namespace xc{
	namespace particlesystem{

		class CFireSystemFactory:public IFireSystemFactory{
		private:

		public:
			//! 创建最简单的火焰粒子系统
			virtual shared_ptr<IRectFireSystem> createRectFire(shared_ptr<drawBasement::IPosColorProgramQ> program);
		};
		class CParticleFactory:public IParticleFactory{
		private:
			CFireSystemFactory mFire;
		public:
			//! 获得火焰粒子系统工厂
			virtual IFireSystemFactory* getFireFactory(){
				return &mFire;
			}
		};
	}
}