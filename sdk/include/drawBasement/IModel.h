#pragma once
#include<MyTypes.h>
#include <vector>
#include"ICanvas.h"
#include"IDrawBuffers.h"
#include"IDrawTexture.h"
#include<tools/CobjContainer.hpp>
#include <unordered_map>
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
		//! 材质信息(主要是纹理)
		struct ModelMatrials
		{
			shared_ptr<IDrawTexture2D> texture;
		};
		//动画播放器
		class IAnimePlayer{
		public:
			//! 获取动画有多少帧
			virtual u32 getNumFrams()=0;
			//! 设置当前动画帧数
			virtual void setCurrentFrame(f32 fPos)=0;

		};
		class CAnimePlayer{
		public:
			u32 mFrameNums;
			//! 获取动画有多少帧
			virtual u32 getNumFrams(){
				return mFrameNums;
			}
			//! 设置当前动画帧数
			virtual void setCurrentFrame(f32 fPos)=0;

			void getTranslateMatrix(){

			}
			void getNumMatrix(){

			}

		};
		
		template<typename T>
		class IModel_T:public T{
		public:
			//! 绘制模型
			virtual void render(ICanvas* canvas)=0;
			//! 获取模型动画播放器
			virtual IAnimePlayer* getAnimator()=0;
			//! 获取变换矩阵
			virtual mat4 getBaseTranslateMatrix()=0;
		};
		typedef IModel_T<IobjContainer<ModelMeshInfo>> IModel;

		class CModel:public CobjContainer<IModel,ModelMeshInfo>{
		public:
			std::unordered_map<int,ModelMatrials> mMatarials;
			mat4 mBaseMat;
			CModel(){
				mBaseMat.setRotationDegrees(vector3df(270.f,180.f,0));

			}
			void render(ICanvas* canvas){
				this->doFunc([&canvas,this](ModelMeshInfo& mm){
					this->mMatarials[mm.materialIdx].texture->use(0);
					canvas->render(mm.mVbo);
				});
			}
			virtual IAnimePlayer* getAnimator(){
				return 0;
			}
			virtual mat4 getBaseTranslateMatrix(){
				return mBaseMat;
			}
		};
	}
}