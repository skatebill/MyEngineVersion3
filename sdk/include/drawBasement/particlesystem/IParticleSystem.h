#pragma once
#include<tools/MyTypes.h>
/************************************************************************/
/* ����ϵͳ�ĳ���
	authored by Ф��
	@ 2013��12��7��23:06:20*/
/************************************************************************/
namespace xc{
	namespace particlesystem{
		class IParticleSystem{
		public:
			//! ��������ϵͳ
			//! ���� delta ���ʱ��
			virtual void update(f32 delta);
		};
	}
}