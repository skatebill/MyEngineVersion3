#pragma once
#include <IModel.h>
#include "CBones.hpp"
namespace xc{
	namespace drawBasement{

		//! 材质信息(主要是纹理)
		struct ModelMatrials
		{
			shared_ptr<IDrawTexture2D> texture;
		};


		class CModel:public CobjContainer<IModel,ModelMeshInfo>{
		public:
			std::unordered_map<int,ModelMatrials> mMatarials;
			mat4 mBaseMat;
			shared_ptr<CBoneAnimator> mBoneAnimator;
			CModel(){
				mBaseMat.setRotationDegrees(vector3df(270.f,180.f,0));

			}
			void render(ICanvas* canvas){
				this->doFunc([&canvas,this](ModelMeshInfo& mm){
					this->mMatarials[mm.materialIdx].texture->use(0);
					canvas->render(mm.mVbo);
				});
			}
			virtual IBoneAnimator* getBoneAnimator(){
				return mBoneAnimator.get();
			}
			virtual mat4 getBaseTranslateMatrix(){
				return mBaseMat;
			}
		};
	}
}