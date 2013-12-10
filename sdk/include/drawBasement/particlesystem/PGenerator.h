#pragma once
#include<tools/MyTypes.h>
#include<random>
namespace xc{
	namespace particlesystem{
		const u32 randomMax=10000;
		template<typename pStruct>
		class PRectGenerator{
		public:
			//! �����б�
			//! ���
			u32 width;
			//! ����
			u32 length;
			//! ����
			vector3df center;
			//! ���ȷ���
			vector3df lengthDirection;
			//! ��ȷ���
			vector3df widthDirection;
			//! ���ӷ��䷽��
			vector3df launchDirection;
			//! ���ӷ����ٶ�
			f32 lauchSpeed;
			//! ���Ӳ����ٶ�
			f32 generatorSpeed;

			//! �����������
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