#pragma once
#include<MyTypes.h>
#include"IBones.h"
#define  NUM_BONES_PER_VEREX 4
#define ZERO_MEM(a) memset(a, 0, sizeof(a))
namespace xc{
	namespace drawBasement{

		struct VertexBoneData
		{        
			u32 IDs[NUM_BONES_PER_VEREX];
			float Weights[NUM_BONES_PER_VEREX];

			VertexBoneData()
			{
				Reset();
			};

			void Reset()
			{
				ZERO_MEM(IDs);
				ZERO_MEM(Weights);        
			}

			void AddBoneData(u32 BoneID, float Weight){

				for (u32 i = 0 ; i < NUM_BONES_PER_VEREX ; ++i) {
					if (Weights[i] == 0.0) {
						IDs[i]     = BoneID;
						Weights[i] = Weight;
						return;
					}        
				}
				throw exception(" error building bones, maxed the bone vertex");
			}
		};

		struct keyScale{
			f32 keyPos;
			vector3df scaleInfo;
			bool operator == (keyScale &o ){
				return keyPos == o.keyPos;
			}
		};
		struct keyRotate
		{
			f32 keyPos;
			quaternion rotateInfo;
			bool operator == (keyRotate &o ){
				return keyPos == o.keyPos;
			}
		};
		struct keyTranslate{
			f32 keyPos;
			vector3df translateInfo;
			bool operator == (keyTranslate &o ){
				return keyPos == o.keyPos;
			}
		};
		class CBone:public CobjContainer<IBone,shared_ptr<IBone>>{
		private:
			IBone* mParent;
			mat4 mCurrentMatrix;
			bool needUpdate;
			f32 mCurrentFramePos;
			//! 获取父骨骼
			virtual IBone* getParent(){
				return mParent;
			}

		public:
			std::vector<keyScale> scaleList;
			std::vector<keyTranslate> translateList;
			std::vector<keyRotate> rotateList;
			mat4 nodeTranslatation;
			mat4 boneOffset;
			bool isinitial;
			string mBoneName;
			f32 mMaxFrame;
			u32 idx;
			CBone(IBone* parent):mParent(parent),mCurrentFramePos(0){
				isinitial=true;
			};

			//! 获取当前节点的变换矩阵
			virtual mat4 getCurrentTranslateMat(){
				if(needUpdate){
					needUpdate=false;
					mat4 rotateMat,scaleMat,translateMat;
					if(scaleList.size() == 0 || translateList.size()==0||rotateList.size()==0){
						mCurrentMatrix = nodeTranslatation;
					}else{
						//scale 差值
						if(scaleList.size() == 1){
							vector3df scale = scaleList[0].scaleInfo;
							scaleMat.setScale(scale);
						}else if(scaleList.size()>1){
							auto spos = std::find_if(scaleList.begin(),scaleList.end(),[this](keyScale& s)->bool{
								return mCurrentFramePos<s.keyPos;
							});
							if(spos == scaleList.end()){
								vector3df scale = scaleList[scaleList.size()-1].scaleInfo;
								scaleMat.setScale(scale);
							}else{

								auto pre = spos;
								pre--;
								auto t = (mCurrentFramePos - pre->keyPos)/(spos->keyPos-pre->keyPos);
								vector3df t1=pre->scaleInfo,t2=spos->scaleInfo;
								auto t3 = (t2-t1)*t+t1;
								scaleMat.setScale(t3);
							}
						}
						// translate 差值
						if(translateList.size() == 1){
							vector3df trans = translateList[0].translateInfo;
							translateMat.setTranslation(trans);
						}else if(translateList.size()>1){
							auto spos = std::find_if(translateList.begin(),translateList.end(),[this](keyTranslate& s)->bool{
								return mCurrentFramePos<s.keyPos;
							});
							if(spos == translateList.end()){
								vector3df trans = translateList[translateList.size()-1].translateInfo;
								translateMat.setTranslation(trans);
							}else{
								auto pre = spos;
								pre--;
								auto t = (mCurrentFramePos - pre->keyPos)/(spos->keyPos-pre->keyPos);
								vector3df t1=pre->translateInfo,t2=spos->translateInfo;
								auto t3 = (t2-t1)*t+t1;
								translateMat.setTranslation(t3);
							}
						}
						// rotate 差值
						if(rotateList.size() == 1){
							quaternion r = rotateList[0].rotateInfo;
							r.getMatrix(rotateMat,zero3df);
						}else if(rotateList.size()>1){
							auto spos = std::find_if(rotateList.begin(),rotateList.end(),[this](keyRotate& s)->bool{
								return mCurrentFramePos<s.keyPos;
							});
							if(spos == rotateList.end()){
								quaternion r = rotateList[rotateList.size()-1].rotateInfo;
								r.getMatrix(rotateMat,zero3df);
							}else{
								auto pre = spos;
								pre--;
								auto t = (mCurrentFramePos - pre->keyPos)/(spos->keyPos-pre->keyPos);
								auto t1=pre->rotateInfo,t2=spos->rotateInfo;
								auto t3 = t1.lerp(t1,t2,t);
								t3.getMatrix(rotateMat,zero3df);
							}
						}
						mat4 xx=boneOffset;xx.makeInverse();
						mCurrentMatrix = translateMat*rotateMat*scaleMat;
					}
					if(getParent()){
						mCurrentMatrix = getParent()->getCurrentTranslateMat()*mCurrentMatrix;
					}
				}
				return mCurrentMatrix;
			}
			//! 获取最终变化矩阵
			virtual mat4 getFinalTranslateMat(){
				return getCurrentTranslateMat()*boneOffset;
			}
			//! 设置当前位置
			virtual void setCurrentFrame(f32 fPos){
				mCurrentFramePos=fPos;
				needUpdate=true;
			}

			//! 获取骨骼节点的最大关键帧位置
			virtual f32 getMaxFrame(){
				return mMaxFrame;
			}
			//! 获取骨骼名
			virtual const char* getBoneName(){
				return mBoneName.c_str();
			}
			//! 获取骨骼索引位置
			virtual const u32 getBoneIdx(){
				return idx;
			}
		};

		class CBoneAnimator:public IBoneAnimator{
		private:
			std::vector<shared_ptr<IBone>> mBoneList;
			f32 mcurFrame;
			std::vector<mat4> mUnifomMatBuffer;
		public:
			f32 mMaxFrames;
			f32 mFramePerSecond;
			mat4 mGlobleInverseTranslate;
			mat4 mGlobleTranslate;
			CBoneAnimator():mcurFrame(0),mMaxFrames(0){
			}
			//! 添加骨骼
			u32 addBones(shared_ptr<IBone> bo){
				mBoneList.push_back(bo);
				return mBoneList.size()-1;
			}
			//! 获取动画一帧的时间
			virtual f32 getFramePerSecond(){
				return mFramePerSecond;
			}
			//! 获取动画帧数
			virtual f32 getNumFrames(){
				return mMaxFrames;
			}
			//! 设置当前位置
			virtual void setCurrentFrame(f32 fPos){
				for_each(mBoneList.begin(),mBoneList.end(),[fPos](shared_ptr<IBone>& bo){
					bo->setCurrentFrame(fPos);
				});
				mUnifomMatBuffer.resize(mBoneList.size());
				mcurFrame = fPos;
				for(u32 i=0;i<mBoneList.size();++i){
					mUnifomMatBuffer[mBoneList[i]->getBoneIdx()]=mBoneList[i]->getFinalTranslateMat();
				}
				int i=0;
			}
			//! 获取当前动画位置
			virtual f32 getCurrentFramePos(){
				return mcurFrame;
			}
			//! 找到指定骨骼
			virtual shared_ptr<IBone> findBones(const char* bonename){
				string bn(bonename);
				auto dst = find_if(mBoneList.begin(),mBoneList.end(),[&bn](shared_ptr<IBone>& bo){
					return bn == bo->getBoneName();
				});
				if(dst == mBoneList.end()){
					throw exception("bone not found");
				}
				return *dst;
			}
			//! 获取骨骼变换矩阵的缓冲区首地址
			virtual void* getUniformMatrixBuffer(){
				return &mUnifomMatBuffer[0];
			}
			//! 获取骨骼数量
			virtual u32 getUniformMatrixSize(){
				return mUnifomMatBuffer.size();
			}

			void computeMaxFrames()
			{
				for(u32 i=0;i<mBoneList.size();++i){
					mMaxFrames = max(mMaxFrames,mBoneList[i]->getMaxFrame());
				}
			}


		};
	}
}