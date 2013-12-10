#pragma once
#include<drawBasement/particlesystem/IParticleFactory.h>
#include<list>
#include<vector>
#include <algorithm>
namespace xc{
	namespace particlesystem{
		template<typename T,typename pStruct,typename generator,typename disturbuncer,typename updator>
		class CParticleSystem:public T{
		protected:
			u32 mMaxParticleNums;
			std::list<typename pStruct::dataStruct> mParticles;
			std::vector<typename pStruct::bufferStruct> mParticBuff;
			f32 mMaxlife;

			generator mGenerator;
			disturbuncer mDisturbencer;
			updator mUpdator;
			bool mNeedUpdate;
		public:
			CParticleSystem(u32 max=10000):mMaxParticleNums(max),mMaxlife(5.0f),mNeedUpdate(true){
				mParticBuff.resize(mMaxParticleNums);
			}
			//! 更新粒子系统
			virtual void update(f32 delta){
				mNeedUpdate=true;
				for_each(mParticles.begin(),mParticles.end(),[this,delta](typename pStruct::dataStruct& src){
					mDisturbencer.disturb_update(src,delta);
					mUpdator.update(src,delta);
				});
				u32 pnow = mParticles.size();
				u32 n = mGenerator.num_to_generate(delta);
				if(n + pnow > mMaxParticleNums){
					n = mMaxParticleNums - pnow;
				}
				for(u32 i=0;i<n;++i){
					typename pStruct::dataStruct pd =  mGenerator.generate();
					mDisturbencer.disturb_construct(pd);
					mParticles.push_front(pd);
				}
				mParticles.remove_if([this](typename pStruct::dataStruct& src)->bool{
					return src.life > mMaxlife;
				});
			}
		};
		//////////////////////////////////////////////////////////////////////////
		struct pBaseStruct{
			struct dataStruct
			{
				vector3df pos;
				vector3df dir;
				f32 speed;
				f32 life;
			};
			struct bufferStruct
			{
				vector3df pos;
				colorf col;
			};

		};
	}
}