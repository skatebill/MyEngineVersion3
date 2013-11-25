#pragma once
#include <IDrawProgram.h>
namespace xc{
	namespace drawBasement{
		const int MAX_BONES = 100;
		static const char* pQBVS = "                                                    \n\
								  #version 330                                                                  \n\
								  \n\
								  layout (location = 0) in vec3 Position;                                       \n\
								  layout (location = 1) in vec2 TexCoord;										\n\
								  layout (location = 2) in vec3 Normal;										\n\
								  layout (location = 3) in ivec4 BoneID;										\n\
								  layout (location = 4) in vec4 BoneWeight;										\n\
								  const int MAX_BONES = 100;													\n\
								  uniform mat4 uMVPMat;                                                         \n\
								  uniform mat4 gBones[100];                                               \n\
								  \n\
								  out vec2 TexCoord0;															\n\
								  void main()                                                                   \n\
								  {                                                                             \n\
									TexCoord0 = TexCoord;                                                       \n\
									vec4 pos = vec4(Position.x, Position.y, Position.z, 1.0); \n\
									mat4 BoneTransform = gBones[BoneID[0]] * BoneWeight[0];\n\
									BoneTransform     += gBones[BoneID[1]] * BoneWeight[1];\n\
									BoneTransform     += gBones[BoneID[2]] * BoneWeight[2];\n\
									BoneTransform     += gBones[BoneID[3]] * BoneWeight[3];\n\
									gl_Position = uMVPMat*BoneTransform *pos;   \n\
								  }";

		static const char* pQBFS = "                                                    \n\
								  #version 330                                                                  \n\
								  in vec2 TexCoord0;															\n\
								  out vec4 FragColor;                                                           \n\
								  uniform sampler2D gSampler;													  \n\
								  void main()                                                                   \n\
								  {                                                                             \n\
								  FragColor = texture2D(gSampler, TexCoord0.st);				             \n\
								  }";


		template<typename T>
		class COpenglBonedProgramQ:public COpenglProgram<T>{
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