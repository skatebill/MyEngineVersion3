#pragma once
#include <IDrawProgram.h>
namespace xc{
	namespace drawBasement{
		const int MAX_BONES = 100;
		static const char* pQBVS = "                                                    \n\
								  \n\
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
								  int getBoneIdF(float value){															\n\
									  if(value < 1.0){															\n\
										  return 0;															\n\
									  }else if(value < 2.0)															\n\
									  {															\n\
										 return 1;															\n\
									  }else if(value < 3.0)															\n\
									  {															\n\
										 return 2;															\n\
									  }else if(value < 4.0)															\n\
									  {															\n\
										  return 3;															\n\
									  }else if(value < 5.0)															\n\
									  {															\n\
										 return 4;															\n\
									  }else if(value < 6.0)															\n\
									  {															\n\
										 return 5;															\n\
									  }else if(value < 7.0)															\n\
									  {															\n\
										 return 6;															\n\
									  }else if(value < 8.0)															\n\
									  {															\n\
										 return 7;															\n\
									  }else if(value < 9.0)															\n\
									  {															\n\
										 return 8;															\n\
									  }else if(value < 10.0)															\n\
									  {															\n\
										 return 9;															\n\
									  }															\n\
								  															\n\
								}															\n\
								int getBoneId(float value){															\n\
									if(value>=10.0){															\n\
										float tenf = value/10.0;															\n\
										int teni = getBoneIdF(tenf);															\n\
										tenf = floor(tenf)*10.0;															\n\
										int gei = getBoneIdF(value-tenf);															\n\
										return teni*10+gei;															\n\
									}else{															\n\
										int gei = getBoneIdF(value);															\n\
										return gei;												\n\
									}															\n\
								}															\n\
								 void main()                                                                   \n\
								  {                                                                             \n\
									TexCoord0 = TexCoord;                                                       \n\
									vec4 pos = vec4(Position.x, Position.y, Position.z, 1.0); \n\
									int b1 = getBoneId(BoneID[0]);int b2 = getBoneId(BoneID[1]);int b3 = getBoneId(BoneID[2]);int b4 = getBoneId(BoneID[3]);\n\
									mat4 BoneTransform = gBones[b1] * BoneWeight[0];\n\
									BoneTransform += gBones[b2] * BoneWeight[1];\n\
									BoneTransform += gBones[b3] * BoneWeight[2];\n\
									BoneTransform += gBones[b4] * BoneWeight[3];\n\
									gl_Position = uMVPMat*BoneTransform *pos;   \n\
								  }";

		static const char* pQBFS = "precision mediump float;                                                    \n\
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
		public:
			virtual void initialProgram(){
				AddShader(getProgram(),pQBVS,GL_VERTEX_SHADER);
				AddShader(getProgram(),pQBFS,GL_FRAGMENT_SHADER);
				linkProgram(getProgram());
				initialHandles();

			}
			//! 初始化handle
			virtual void initialHandles(){
				mMatHandle = glGetUniformLocation(getProgram(),"uMVPMat");
				if(mMatHandle == 0xFFFFFFFF) throw std::exception("error bind translate matrix handle");
				mTexHandle = glGetUniformLocation(getProgram(),"gSampler");
				if(mTexHandle == 0xFFFFFFFF) throw std::exception("error bind texture handle");
				mBoneMatHandle = glGetUniformLocation(getProgram(),"gBones");
				if(mBoneMatHandle == 0xFFFFFFFF) throw std::exception("error bind bone handle");
				glUniform1i(mTexHandle,0);
			}
			//! 上传纹理
			virtual void uploadTexture(IDrawTexture2D* tex){
				tex->use(0);
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