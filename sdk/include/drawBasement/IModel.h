#pragma once
#include<tools/MyTypes.h>
#include <vector>
#include<drawBasement/ICanvas.h>
#include<drawBasement/IDrawBuffers.h>
#include<drawBasement/IDrawTexture.h>
#include<tools/CobjContainer.hpp>
#include <unordered_map>
#include <drawBasement/IBones.h>
namespace xc{
	namespace drawBasement{
		//! 动画mesh信息
		struct ModelMeshInfo{
			shared_ptr<IDrawVertexBufferOBject> mVbo;
			u32 materialIdx;
			bool operator == (const ModelMeshInfo& o){
				return mVbo.get() == o.mVbo.get();
			}
		};

		template<typename T>
		class IModel_T:public T{
		public:
			//! 绘制模型
			virtual void render(ICanvas* canvas)=0;
			//! 获取模型动画播放器
			virtual IBoneAnimator* getBoneAnimator()=0;
		};
		typedef IModel_T<IobjContainer<ModelMeshInfo>> IModel;
	}
}