#pragma once
#include"IParticleSystem.h"
namespace xc{
	namespace particlesystem{
		class IParticleFactory{
		public:
			//! ��û�������ϵͳ����
			virtual IFireSystemFactory* getFireFactory()=0;
		};
	}
}