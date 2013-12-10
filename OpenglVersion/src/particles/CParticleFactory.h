#pragma once
#include "CParticleSystem.h"
#include<drawBasement/particlesystem/IParticleFactory.h>
namespace xc{
	namespace particlesystem{

		class CFireSystemFactory:public IFireSystemFactory{
		private:

		public:
			//! ������򵥵Ļ�������ϵͳ
			virtual shared_ptr<IRectFireSystem> createRectFire(shared_ptr<drawBasement::IPosColorProgramQ> program);
		};
		class CParticleFactory:public IParticleFactory{
		private:
			CFireSystemFactory mFire;
		public:
			//! ��û�������ϵͳ����
			virtual IFireSystemFactory* getFireFactory(){
				return &mFire;
			}
		};
	}
}