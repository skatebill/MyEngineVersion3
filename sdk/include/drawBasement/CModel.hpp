#pragma once
#include <drawBasement/IModel.h>
#include <drawBasement/CBones.hpp>
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
			shared_ptr<CBoneAnimator> mBoneAnimator;
			string modelPath;
			CModel(){
			}
			void render(ICanvas* canvas){
				this->doFunc([&canvas,this](ModelMeshInfo& mm){
					this->mMatarials[mm.materialIdx].texture->use(0);
					canvas->render(mm.mVbo);
				});
			}
			virtual IBoneAnimator* getBoneAnimator(){
				if(mBoneAnimator == nullptr) throw exception();
				return mBoneAnimator.get();
			}
		};
	}
}