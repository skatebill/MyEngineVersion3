#pragma once
#include<tools/MyTypes.h>
#include<drawBasement/ICanvas.h>
#include<drawBasement/IDrawProgram.h>
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
			virtual void update(f32 delta)=0;
			//! 绘制粒子系统
			virtual void draw(shared_ptr<drawBasement::ICanvas> canvas){
				draw(canvas.get());
			}
			virtual void draw(drawBasement::ICanvas* canvas)=0;
		};
#pragma region 火焰粒子系统
		//! 参数 中心点 长宽 发射方向 发射速度 粒子寿命
		class IRectFireSystem:public IParticleSystem{
		public:
			//! 设置中心
			virtual void setCenter(vector3df c)=0;
			//! 设置长宽区域
			virtual void setRect(u32 l,u32 w)=0;
			//! 设置发射方向 
			virtual void setDirection(vector3df dir)=0;
			//! 设置发射速度
			virtual void setSpeed(float speed)=0;
			//! 设置粒子寿命
			virtual void setLife(float life)=0;
		};
		//! 火焰模拟粒子系统
		class IFireSystemFactory{
		public:
			//! 创建最简单的火焰粒子系统
			virtual shared_ptr<IRectFireSystem> createRectFire(shared_ptr<drawBasement::IPosColorProgramQ> program)=0;
		};
#pragma endregion 火焰粒子系统
	}
}