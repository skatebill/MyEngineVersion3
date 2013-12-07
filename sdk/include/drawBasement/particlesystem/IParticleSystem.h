#pragma once
#include<tools/MyTypes.h>
/************************************************************************/
/* 粒子系统的抽象
	authored by 肖驰
	@ 2013年12月7日23:06:20*/
/************************************************************************/
namespace xc{
	namespace particlesystem{
		class IParticleSystem{
		public:
			//! 更新粒子系统
			//! 输入 delta 间隔时间
			virtual void update(f32 delta);
		};
	}
}