#pragma once
#include"COpenglProgram.h"
namespace xc{
	namespace drawBasement{
		template<typename T>
		class COpenglBaseProgram:public COpenglProgram<T>{
		public:
			//! 上传世界变换矩阵
			virtual void uploadWorldTranslateMatrix(mat4f mat)=0;
			//! 上传投影变换矩阵
			virtual void uploadProjectionMatrix(mat4f mat)=0;
			//! 上传视点变换矩阵
			virtual void uploadViewMatrix(mat4f mat)=0;

		};


		static const char* pQVS = "                                                    \n\
								  #version 330                                                                  \n\
								  \n\
								  layout (location = 0) in vec3 Position;                                       \n\
								  uniform mat4 uMVPMat;                                                         \n\
								  \n\
								  \n\
								  void main()                                                                   \n\
								  {                                                                             \n\
								  gl_Position = uMVPMat *vec4( Position.x, Position.y, Position.z, 1.0);   \n\
								  }";

		static const char* pQFS = "                                                    \n\
								  #version 330                                                                  \n\
								  \n\
								  out vec4 FragColor;                                                           \n\
								  uniform vec4 uColor;                                                           \n\
								  \n\
								  void main()                                                                   \n\
								  {                                                                             \n\
								  FragColor = uColor;									                     \n\
								  }";


		template<typename T>
		class COpenglBaseProgramQ:public COpenglProgram<T>{
		private:
			GLuint m_MVPMatHandle;
			GLuint m_ColorHandle;
		public:
			virtual void initialProgram(){
				AddShader(getProgram(),pQVS,GL_VERTEX_SHADER);
				AddShader(getProgram(),pQFS,GL_FRAGMENT_SHADER);
				linkProgram(getProgram());
				initialHandles();
			}
			//! 初始化handle
			virtual void initialHandles(){
				m_MVPMatHandle = glGetUniformLocation(getProgram(),"uMVPMat");
				m_ColorHandle = glGetUniformLocation(getProgram(),"uColor");
			}
			//! 上传变换矩阵
			virtual void uploadMatrix(mat4f mat){
				glUniformMatrix4fv(m_MVPMatHandle,1,false,(const GLfloat*)&mat);
			}
			//! 准备绘制（做一些准备工作）
			virtual void prepareDraw(){
				COpenglProgram::prepareDraw();
			}
			//! 做一些收尾工作
			virtual void endDraw(){
				COpenglProgram::endDraw();
			}
			//! 表明是哪一种着色器
			virtual EnumProgramType type(){
				return EPT_BaseType;
			}
			//! 上传颜色
			virtual void uploadColor(colorf c){
				glUniform4fv(m_ColorHandle,1,(const GLfloat*)&c);
			}
		};
	}
}