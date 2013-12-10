#pragma once
#include <drawBasement/IDrawProgram.h>
namespace xc{
	namespace drawBasement{
		static const char* pQTVS = "                                                    \n\
								  #version 330                                                                  \n\
								  \n\
								  layout (location = 0) in vec3 Position;                                       \n\
								  layout (location = 1) in vec2 TexCoord;										\n\
								  uniform mat4 uMVPMat;                                                         \n\
								  \n\
								  out vec2 TexCoord0;															\n\
								  void main()                                                                   \n\
								  {                                                                             \n\
									TexCoord0 = TexCoord;                                                       \n\
									gl_Position = uMVPMat *vec4( Position.x, Position.y, Position.z, 1.0);   \n\
								  }";

		static const char* pQTFS = "                                                    \n\
								  #version 330                                                                  \n\
								  in vec2 TexCoord0;															\n\
								  out vec4 FragColor;                                                           \n\
								  uniform sampler2D gSampler;													  \n\
								  void main()                                                                   \n\
								  {                                                                             \n\
									  FragColor = texture2D(gSampler, TexCoord0.st);				             \n\
								  }";


		template<typename T>
		class COpenglTexturedProgramQ:public COpenglProgram<T>{
		private:
			GLuint mTexHandle;
			GLuint mMatHandle;
		public:
			virtual void initialProgram(){
				AddShader(getProgram(),pQTVS,GL_VERTEX_SHADER);
				AddShader(getProgram(),pQTFS,GL_FRAGMENT_SHADER);
				linkProgram(getProgram());
				initialHandles();

			}
			//! 初始化handle
			virtual void initialHandles(){
				mMatHandle = glGetUniformLocation(getProgram(),"uMVPMat");
				if(mMatHandle == 0xFFFFFFFF) throw std::exception("error bind translate matrix handle");
				mTexHandle = glGetUniformLocation(getProgram(),"gSampler");
				if(mTexHandle == 0xFFFFFFFF) throw std::exception("error bind texture handle");
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
				return EPT_Textured;
			}
		};
	}
}