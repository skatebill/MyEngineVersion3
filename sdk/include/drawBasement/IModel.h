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
		//! ����mesh��Ϣ
		struct ModelMeshInfo{
			shared_ptr<IDrawVertexBufferOBject> mVbo;
			u32 materialIdx;
			bool operator == (const ModelMeshInfo& o){
				return mVbo.get() == o.mVbo.get();
			}
		};
		//! ������Ϣ(��Ҫ������)
		struct ModelMatrials
		{
			shared_ptr<IDrawTexture2D> texture;
		};
		//����������
		class IAnimePlayer{
		public:
			//! ��ȡ�����ж���֡
			virtual u32 getNumFrams()=0;
			//! ���õ�ǰ����֡��
			virtual void setCurrentFrame(f32 fPos)=0;

		};
		class CAnimePlayer{
		public:
			u32 mFrameNums;
			//! ��ȡ�����ж���֡
			virtual u32 getNumFrams(){
				return mFrameNums;
			}
			//! ���õ�ǰ����֡��
			virtual void setCurrentFrame(f32 fPos)=0;

			void getTranslateMatrix(){

			}
			void getNumMatrix(){

			}

		};
		
		template<typename T>
		class IModel_T:public T{
		public:
			//! ����ģ��
			virtual void render(ICanvas* canvas)=0;
			//! ��ȡģ�Ͷ���������
			virtual IAnimePlayer* getAnimator()=0;
			//! ��ȡ�任����
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