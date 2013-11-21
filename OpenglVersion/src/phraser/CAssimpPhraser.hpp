#pragma once
#include <MyTypes.h>
#include <service/phraser/IPhraseSerivce.h>
#include <service/file/IFileService.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <IDrawFactory.h>
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
					drawBasement::ModelMeshInfo inf;
					auto vbo = df->createVertexBufferObject(vbuf,ibuf,tbuf,nbuf);
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
		};
		class CPhraserService:public IPhraserService{
		private:
			shared_ptr<IFileService> mFileService;
			shared_ptr<drawBasement::IDrawFactory> mDrawFactory;
			assimpPhraser mAssImp;
		public:
			CPhraserService(shared_ptr<IFileService> f,shared_ptr<drawBasement::IDrawFactory> d):mFileService(f),mDrawFactory(d){

			}
			//! ¶ÁÈ¡Ä£ÐÍ
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