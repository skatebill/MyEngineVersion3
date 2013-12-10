#pragma once
#include<tools/MyTypes.h>
#include<random>
namespace xc{
	namespace particlesystem{
		const u32 randomMax=10000;
		template<typename pStruct>
		class PRectGenerator{
		public:
			//! 参数列表
			//! 宽度
			u32 width;
			//! 场地
			u32 length;
			//! 中心
			vector3df center;
			//! 长度方向
			vector3df lengthDirection;
			//! 宽度方向
			vector3df widthDirection;
			//! 粒子发射方向
			vector3df launchDirection;
			//! 粒子发射速度
			f32 lauchSpeed;
			//! 粒子产生速度
			f32 generatorSpeed;

			//! 随机数发生器
			std::mt19937 gen;
			std::uniform_int_distribution<> rer;
			PRectGenerator():rer(0,randomMax){
				std::random_device rd;
				gen = std::mt19937(rd());

				width = 0;
				length = 0;
				launchDirection = vector3df(0,1,0);
				lengthDirection = vector3df(1,0,0);
				widthDirection = vector3df(0,0,-1);

				generatorSpeed = 1000;
				lauchSpeed = 2;
			}
			pStruct generate(){
				f32 _l = (rer(gen)/(f32)randomMax-0.5f) * 2 * length;
				f32 _w = (rer(gen)/(f32)randomMax-0.5f) * 2 * width;

				vector3df p = center + _l * lengthDirection + _w * widthDirection;
				pStruct r;
				r.pos = p;
				r.dir = launchDirection;
				r.speed = lauchSpeed;
				r.life = 0;
				return r;
			}
			u32 num_to_generate(f32 time){
				return (u32)(time * generatorSpeed);
			}
		};
	}
}