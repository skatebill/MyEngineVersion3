#pragma once
#include <MyTypes.h>
#include <service/phraser/IPhraseSerivce.h>
#include <service/file/IFileService.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <IDrawFactory.h>
#include <CBones.hpp>
#include<CModel.hpp>
#ifndef ZeroMemory
#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
#endif
namespace xc{
	namespace phraser{
		using namespace fileservice;
		class assimpPhraser{
		public:
			shared_ptr<drawBasement::IModel> load(drawBasement::IDrawFactory* df,IFileService* ff,shared_ptr<IFile> fi){
				using namespace Assimp;
				Importer Imp;
				u32 size = fi->getFileSize();
				void* buf = malloc(size);
				fi->read((char*)buf,size);
				const aiScene* pScene = Imp.ReadFile(fi->getAbsolutePath().c_str(),aiProcess_Triangulate | aiProcess_GenSmoothNormals);
				free(buf);
				const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
				auto model = new drawBasement::CModel;
				//骨骼动画初始化
				if(pScene->HasAnimations()){
					model->mBoneAnimator = shared_ptr<drawBasement::CBoneAnimator>(new drawBasement::CBoneAnimator);
					memcpy(&model->mBoneAnimator->mGlobleInverseTranslate,&pScene->mRootNode->mTransformation,sizeof(f32)*16);
	/*				model->mBoneAnimator->mGlobleInverseTranslate = model->mBoneAnimator->mGlobleInverseTranslate.getTransposed();
					model->mBoneAnimator->mGlobleTranslate = model->mBoneAnimator->mGlobleInverseTranslate;
					model->mBoneAnimator->mGlobleInverseTranslate.makeInverse();*/
					buildBoneAnimations(pScene->mAnimations[0],pScene->mRootNode,model);
				}
				mat4 zeroMat;
				ZeroMemory(&zeroMat,sizeof(mat4));
				//模型数据初始化
				for(unsigned int i=0;i<pScene->mNumMeshes;++i){
					const aiMesh* paiMesh = pScene->mMeshes[i];
					auto vbuf = df->createVertexBuffer();
					vbuf->setElemtSize(3);
					vbuf->reSizeBuffer(sizeof(vector3df)*paiMesh->mNumVertices);
					vector3df* vb = (vector3df*)vbuf->lock();

					auto nbuf = df->createVertexBuffer();
					nbuf->setElemtSize(3);
					nbuf->reSizeBuffer(sizeof(vector3df)*paiMesh->mNumVertices);
					vector3df* nb = (vector3df*)nbuf->lock();

					auto tbuf = df->createVertexBuffer();
					tbuf->setElemtSize(2);
					tbuf->reSizeBuffer(sizeof(vector2df)*paiMesh->mNumVertices);
					vector2df* tb = (vector2df*)tbuf->lock();
					
					for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) {
						const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
						const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
						const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
						vb[i].X=pPos->x;
						vb[i].Y=pPos->y;
						vb[i].Z=pPos->z;

						tb[i].X=pTexCoord->x;
						tb[i].Y=pTexCoord->y;

						nb[i].X=pNormal->x;
						nb[i].Y=pNormal->y;
						nb[i].Z=pNormal->z;
						
					}

					auto ibuf = df->createIndexBuffer();
					ibuf->setIndexNums(paiMesh->mNumFaces*3);
					ibuf->setPrimityType(drawBasement::EPT_TRIANGLES);
					ibuf->reSizeBuffer(paiMesh->mNumFaces*3*ibuf->getIndexType());
					u16* ib = (u16*)ibuf->lock();
					for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) {
						const aiFace& Face = paiMesh->mFaces[i];
						ib[i*3+0]=Face.mIndices[0];
						ib[i*3+1]=Face.mIndices[1];
						ib[i*3+2]=Face.mIndices[2];
					}
					tbuf->initialBuffer();
					nbuf->initialBuffer();
					vbuf->initialBuffer();
					ibuf->initialBuffer();
					u32 bsize = 4*sizeof(u32)*paiMesh->mNumVertices;
					shared_ptr<drawBasement::IDrawBuffer> bbuf = 0;
					shared_ptr<drawBasement::IDrawBuffer> bwbuf = 0;
					if(paiMesh->HasBones()){
						bbuf = df->createVertexBuffer();
						bwbuf = df->createVertexBuffer();
						bbuf->reSizeBuffer(bsize);
						bbuf->setElemtSize(4);
						bbuf->setDataType(drawBasement::EDT_UINT);
						bwbuf->reSizeBuffer(bsize);
						bwbuf->setElemtSize(4);


						u32* bb = (u32*)bbuf->lock();
						f32* bwb = (f32*)bwbuf->lock();
						ZeroMemory(bb,bsize);
						ZeroMemory(bwb,bsize);
						for(u32 i=0;i<paiMesh->mNumBones;++i){
							auto bone = model->mBoneAnimator->findBones(paiMesh->mBones[i]->mName.C_Str());
							if(((drawBasement::CBone*)bone.get())->isinitial){
								((drawBasement::CBone*)bone.get())->isinitial=false;
								memcpy(&((drawBasement::CBone*)bone.get())->boneOffset,&paiMesh->mBones[i]->mOffsetMatrix,sizeof(f32)*16);
								((drawBasement::CBone*)bone.get())->boneOffset=((drawBasement::CBone*)bone.get())->boneOffset.getTransposed();
							}
							u32 bid = bone->getBoneIdx();
							for(u32 bi=0;bi<paiMesh->mBones[i]->mNumWeights;++bi){
								u32 vid = paiMesh->mBones[i]->mWeights[bi].mVertexId;
								f32 vw = paiMesh->mBones[i]->mWeights[bi].mWeight;
								AddBoneData(bb+vid*4,bwb+vid*4,bid,vw);
							}
						}
						bbuf->initialBuffer();
						bwbuf->initialBuffer();
					}
					drawBasement::ModelMeshInfo inf;
					auto vbo = df->createVertexBufferObject(vbuf,ibuf,tbuf,nbuf,bbuf,bwbuf);
					inf.mVbo = vbo;
					inf.materialIdx = paiMesh->mMaterialIndex;
					model->addObj(inf);
				}
				string path = fi->getAbsolutePath();
				bool linustyle = true;
				auto p = path.findLast('/');
				if(p == -1){
					p = path.findLast('\\');
					linustyle=false;
				}
				if(p == -1){
					throw exception("error load mode-- filepath error");
				}
				string dir = path.subString(0,p);
				if(!linustyle)
					dir+="\\";
				else
					dir+='/';
				//纹理初始化
				for (u32 i=0;i<pScene->mNumMaterials;++i)
				{
					if(pScene->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE) == 1){
						aiString filename;
						pScene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE,0,&filename);
						string filenamew(filename.C_Str());
						auto p = dir+filenamew;
						auto tex = df->getTextureFactory()->createTextureFromImage(ff->createImageFromFile(p.c_str()).get());
						drawBasement::ModelMatrials mat;
						mat.texture =tex;
						u32 idx = model->mMatarials.size();
						
						model->mMatarials.insert(make_pair(idx,mat));
					}else{
						throw exception("error load mode-- muti textures error");
					}
				}
				return shared_ptr<drawBasement::IModel>(model);
			}


			void AddBoneData(u32* IDs,f32* Weights,u32 BoneID, float Weight){

				for (u32 i = 0 ; i < NUM_BONES_PER_VEREX ; ++i) {
					if (Weights[i] == 0.0) {
						IDs[i]     = BoneID;
						Weights[i] = Weight;
						return;
					}        
				}
				throw exception(" error building bones, maxed the bone vertex");
			}
			const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName)
			{
				for (u32 i = 0 ; i < pAnimation->mNumChannels ; i++) {
					const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

					if (string(pNodeAnim->mNodeName.data) == NodeName) {
						return pNodeAnim;
					}
				}

				return NULL;
			}

			void buildBoneAnimations(aiAnimation* animation, aiNode* node, xc::drawBasement::CModel * model,drawBasement::CBone* parent = nullptr )
			{
				using namespace drawBasement;
				CBone* bone = new CBone(parent);
				bone->mBoneName = node->mName.C_Str();
				memcpy(&bone->nodeTranslatation,&node->mTransformation,sizeof(f32)*16);
				bone->nodeTranslatation = bone->nodeTranslatation.getTransposed();
				bone->idx = model->mBoneAnimator->addBones(shared_ptr<IBone>(bone));
				const aiNodeAnim* pNodeAnim = FindNodeAnim(animation, bone->mBoneName);
				if(pNodeAnim){
					for(u32 i=0;i<pNodeAnim->mNumPositionKeys;++i){
						keyTranslate tt;
						tt.keyPos=pNodeAnim->mPositionKeys[i].mTime;
						auto& r = pNodeAnim->mPositionKeys[i].mValue;
						tt.translateInfo.X = r.x;
						tt.translateInfo.Y = r.y;
						tt.translateInfo.Z = r.z;
						bone->translateList.push_back(tt);
					}
					for(u32 i=0;i<pNodeAnim->mNumRotationKeys;++i){
						keyRotate tr;
						tr.keyPos=pNodeAnim->mRotationKeys[i].mTime;
						auto& r = pNodeAnim->mRotationKeys[i].mValue;
						tr.rotateInfo.X = r.x;
						tr.rotateInfo.Y = r.y;
						tr.rotateInfo.Z = r.z;
						tr.rotateInfo.W = r.w;
						bone->rotateList.push_back(tr);
					}

					for(u32 i=0;i<pNodeAnim->mNumScalingKeys;++i){
						keyScale ts;
						ts.keyPos=pNodeAnim->mScalingKeys[i].mTime;
						auto& r = pNodeAnim->mScalingKeys[i].mValue;
						ts.scaleInfo.X = r.x;
						ts.scaleInfo.Y = r.y;
						ts.scaleInfo.Z = r.z;
						bone->scaleList.push_back(ts);
					}
				}

				for(u32 i=0;i<node->mNumChildren;++i){
					buildBoneAnimations(animation,node->mChildren[i],model,bone);
				}
			}


		};
		class CPhraserService:public IPhraserService{
		private:
			shared_ptr<IFileService> mFileService;
			shared_ptr<drawBasement::IDrawFactory> mDrawFactory;
			assimpPhraser mAssImp;
		public:
			CPhraserService(shared_ptr<IFileService> f,shared_ptr<drawBasement::IDrawFactory> d):mFileService(f),mDrawFactory(d){

			}
			//! 读取模型
			virtual shared_ptr<drawBasement::IModel> loadModelFromFile(const char* filename){
				auto file = mFileService->createReadableFile(filename);
				//file->open();
				auto r =mAssImp.load(mDrawFactory.get(),mFileService.get(),file);
				//file->close();
				return r;
			}
		};

	}
}