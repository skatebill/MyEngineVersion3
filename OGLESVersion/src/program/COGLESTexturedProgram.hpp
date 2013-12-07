#pragma once
#include <drawBasement/IDrawProgram.h>
namespace xc{
	namespace drawBasement{
		static const char* pQTVS = "                                                    \n\
								  \n\
								  attribute vec3 Position;                                       \n\
								  attribute vec2 TexCoord;										\n\
								  uniform mat4 uMVPMat;                                                         \n\
								  \n\
								  varying vec2 TexCoord0;															\n\
								  void main()                                                                   \n\
								  {                                                                             \n\
									TexCoord0 = TexCoord;                                                       \n\
									gl_Position = uMVPMat *vec4( Position.x, Position.y, Position.z, 1.0);   \n\
								  }";

		static const char* pQTFS = "precision mediump float;                                                   \n\
								  varying vec2 TexCoord0;															\n\
								  uniform sampler2D gSampler;													  \n\
								  void main()                                                                   \n\
								  {                                                                             \n\
									 gl_FragColor = texture2D(gSampler, TexCoord0.st);				             \n\
								  }";


		template<typename T>
		class COGLESTexturedProgramQ:public COGLESProgram<T>{
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
				if(mMatHandle == 0xFFFFFFFF) throw std::exception();
				mTexHandle = glGetUniformLocation(getProgram(),"gSampler");
				if(mTexHandle == 0xFFFFFFFF) throw std::exception();
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