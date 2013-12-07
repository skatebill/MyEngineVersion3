#pragma once
#include <drawBasement/IDrawProgram.h>
#include "../COGLESBuffer.h"
#include <algorithm>
namespace xc{
	namespace drawBasement{
		const int MAX_BONES = 100;
		static const char* pQBVS = "                                                    \n\
								   precision highp float;\n\
								   precision highp int;\n\
								  attribute vec3 Position;                                       \n\
								  attribute vec2 TexCoord;										\n\
								  attribute vec3 Normal;										\n\
								  attribute vec4 BoneID;										\n\
								  attribute vec4 BoneWeight;										\n\
								  const int MAX_BONES = 100;													\n\
								  uniform mat4 uMVPMat;                                                         \n\
								  uniform mat4 gBones[100];                                               \n\
								  \n\
								  varying vec2 TexCoord0;															\n\
								 void main()                                                                   \n\
								  {                                                                             \n\
									TexCoord0 = TexCoord;                                                       \n\
									vec4 pos = vec4(Position.x, Position.y, Position.z, 1.0); \n\
									int b1 = int(BoneID[0]);int b2 = int(BoneID[1]);int b3 = int(BoneID[2]);int b4 = int(BoneID[3]);\n\
									mat4 BoneTransform = gBones[b1] * BoneWeight[0];\n\
									BoneTransform += gBones[b2] * BoneWeight[1];\n\
									BoneTransform += gBones[b3] * BoneWeight[2];\n\
									BoneTransform += gBones[b4] * BoneWeight[3];\n\
									gl_Position = uMVPMat*BoneTransform *pos;   \n\
						//			gl_Position = gl_Position/gl_Position.w; \n\
								  }";

		static const char* pQBFS = "precision highp float;                                                    \n\
								  varying vec2 TexCoord0;															\n\
								  uniform sampler2D gSampler;													  \n\
								  void main()                                                                   \n\
								  {                                                                             \n\
								  gl_FragColor = texture2D(gSampler, TexCoord0.st);				             \n\
								  }";

		/*BoneTransform     += gBones[(int)BoneID[1]] * BoneWeight[1];\n\
			BoneTransform     += gBones[(int)BoneID[2]] * BoneWeight[2];\n\
			BoneTransform     += gBones[(int)BoneID[3]] * BoneWeight[3];\n\*/

		template<typename T>
		class COGLESBonedProgramQ:public COGLESProgram<T>{
		private:
			GLuint mTexHandle;
			GLuint mMatHandle;
			GLuint mBoneMatHandle;

			GLuint mAttributePos;
			GLuint mAttributeTex;
			GLuint mAttributeNormal;
			GLuint mAttributeId;
			GLuint mAttributeWeight;
			std::vector<GLuint> mHandles;
		public:
			virtual void initialProgram(){
				AddShader(getProgram(),pQBVS,GL_VERTEX_SHADER);
				AddShader(getProgram(),pQBFS,GL_FRAGMENT_SHADER);
				linkProgram(getProgram());
				initialHandles();

			}
			//! 初始化handle
			virtual void initialHandles(){
				mAttributePos = glGetAttribLocation(getProgram(),"Position");
				mAttributeTex = glGetAttribLocation(getProgram(),"TexCoord");
				mAttributeNormal = glGetAttribLocation(getProgram(),"Normal");
				mAttributeId = glGetAttribLocation(getProgram(),"BoneID");
				mAttributeWeight = glGetAttribLocation(getProgram(),"BoneWeight");

				mHandles.push_back(mAttributePos);
				mHandles.push_back(mAttributeTex);
				mHandles.push_back(mAttributeNormal);
				mHandles.push_back(mAttributeId);
				mHandles.push_back(mAttributeWeight);

				mMatHandle = glGetUniformLocation(getProgram(),"uMVPMat");
				if(mMatHandle == 0xFFFFFFFF) throw std::exception();
				mTexHandle = glGetUniformLocation(getProgram(),"gSampler");
				if(mTexHandle == 0xFFFFFFFF) throw std::exception();
				mBoneMatHandle = glGetUniformLocation(getProgram(),"gBones");
				if(mBoneMatHandle == 0xFFFFFFFF) throw std::exception();
				glUniform1i(mTexHandle,0);

			}
			//! 上传纹理
			virtual void uploadTexture(IDrawTexture2D* tex){
				tex->use(0);
			}

			virtual void uploadVerterBufferObject(IDrawVertexBufferOBject* vbo){
				COGLESVertexBufferObject* cbo = (COGLESVertexBufferObject*)vbo;
				int curpos = 0;
				int elapsed = 0;
				for_each(mHandles.begin(),mHandles.end(),[&curpos,&elapsed,cbo](GLuint handle){
					if(handle!= 0xFFFFFFFF){
						cbo->m_vertexList[elapsed]->use(handle);
						curpos++;
					}
					elapsed++;
				});

			}
			//! 上传变换矩阵
			virtual void uploadMatrix(mat4f mat){
				glUniformMatrix4fv(mMatHandle,1,false,(const GLfloat*)&mat);

			}
			//! 类型 纹理快速
			virtual EnumProgramType type(){
				return EPT_Boned;
			}
			//! 上传骨骼矩阵
			virtual void uploadBoneMatrix(void* buffer,u32 size){
				glUniformMatrix4fv(mBoneMatHandle,size,false,(const GLfloat*)buffer);
			}
		};
	}
}