#pragma once
#include"CParticleSystem.h"
#include<drawBasement/particlesystem/PGenerator.h>
#include<drawBasement/particlesystem/PUpdator.h>
#include<drawBasement/particlesystem/PDisturbancer.h>
#include<GLES2/gl2.h>
namespace xc{
	namespace particlesystem{
		class CRectFireSystem:public CParticleSystem<IRectFireSystem,
			pBaseStruct,
			PRectGenerator<pBaseStruct::dataStruct>,
			PBaseDisturbuncer<pBaseStruct::dataStruct>,
			PBaseUpdator<pBaseStruct::dataStruct>>{
		private:
			shared_ptr<drawBasement::IPosColorProgramQ> mProgram;
		public:
			CRectFireSystem(shared_ptr<drawBasement::IPosColorProgramQ> program){
				mProgram = program;
			}
			//! 设置中心
			virtual void setCenter(vector3df c){
				mGenerator.center = c;
			}
			//! 设置长宽区域
			virtual void setRect(u32 l,u32 w){
				mGenerator.length=l;
				mGenerator.width=w;
			}
			//! 设置发射方向 
			virtual void setDirection(vector3df dir){
				mGenerator.launchDirection = dir;
			}
			//! 设置发射速度
			virtual void setSpeed(float speed){
				mGenerator.lauchSpeed = speed;
			}
			//! 设置粒子寿命
			virtual void setLife(float life){
				mMaxlife = life;
			}
			virtual void draw(drawBasement::ICanvas* canvas){
				if(mNeedUpdate){
					int processed = 0;
					for_each(mParticles.begin(),mParticles.end(),[this,&processed](pBaseStruct::dataStruct& src){
						pBaseStruct::bufferStruct bs;
						bs.pos = src.pos;
						bs.col = colorf(1.0,1.0,0.0,1.0);
						f32 factor = (mMaxlife - src.life)/mMaxlife;
						bs.col = bs.col * factor;
						mParticBuff[processed] = bs;
						processed++;
					});
				}
				glEnable(GL_BLEND);
				glDisable(GL_CULL_FACE);
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
				mProgram->prepareDraw();
				mProgram->uploadMatrix(canvas->getProjectionMatrix()*canvas->getViewMatrix()*canvas->getWorldTranslateMatrix());
				u32 stride = sizeof(pBaseStruct::bufferStruct);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(0,3,GL_FLOAT,false,stride,&mParticBuff[0].pos);
				glVertexAttribPointer(1,4,GL_FLOAT,false,stride,&mParticBuff[0].col);
				glDrawArrays(GL_POINTS,0,mParticles.size());
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(0);
				glDisable(GL_BLEND);
				mProgram->endDraw();
			}
		};
	}
}