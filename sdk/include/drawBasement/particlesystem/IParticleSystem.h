#pragma once
#include<tools/MyTypes.h>
#include<drawBasement/ICanvas.h>
#include<drawBasement/IDrawProgram.h>
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
			virtual void update(f32 delta)=0;
			//! ��������ϵͳ
			virtual void draw(shared_ptr<drawBasement::ICanvas> canvas){
				draw(canvas.get());
			}
			virtual void draw(drawBasement::ICanvas* canvas)=0;
		};
#pragma region ��������ϵͳ
		//! ���� ���ĵ� ���� ���䷽�� �����ٶ� ��������
		class IRectFireSystem:public IParticleSystem{
		public:
			//! ��������
			virtual void setCenter(vector3df c)=0;
			//! ���ó�������
			virtual void setRect(u32 l,u32 w)=0;
			//! ���÷��䷽�� 
			virtual void setDirection(vector3df dir)=0;
			//! ���÷����ٶ�
			virtual void setSpeed(float speed)=0;
			//! ������������
			virtual void setLife(float life)=0;
		};
		//! ����ģ������ϵͳ
		class IFireSystemFactory{
		public:
			//! ������򵥵Ļ�������ϵͳ
			virtual shared_ptr<IRectFireSystem> createRectFire(shared_ptr<drawBasement::IPosColorProgramQ> program)=0;
		};
#pragma endregion ��������ϵͳ
	}
}