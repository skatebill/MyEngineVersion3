#pragma once
#include"COGLESProgram.h"
namespace xc{
	namespace drawBasement{
		template<typename T>
		class COGLESBaseProgram:public COGLESProgram<T>{
		public:
			//! �ϴ�����任����
			virtual void uploadWorldTranslateMatrix(mat4f mat)=0;
			//! �ϴ�ͶӰ�任����
			virtual void uploadProjectionMatrix(mat4f mat)=0;
			//! �ϴ��ӵ�任����
			virtual void uploadViewMatrix(mat4f mat)=0;

		};


		static const char* pQVS = "                                                    \n\
								  \n\
								  attribute vec3 Position;                                       \n\
								  uniform mat4 uMVPMat;                                                         \n\
								  \n\
								  \n\
								  void main()                                                                   \n\
								  {                                                                             \n\
								  gl_Position = uMVPMat *vec4( Position.x, Position.y, Position.z, 1.0);   \n\
								  }";

		static const char* pQFS = "                                                    \n\
								  precision mediump float;\n\
								  uniform vec4 uColor;                                                           \n\
								  \n\
								  void main()                                                                   \n\
								  {                                                                             \n\
								  gl_FragColor = uColor;									                     \n\
								  }";


		template<typename T>
		class COGLESBaseProgramQ:public COGLESProgram<T>{
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
			//! ��ʼ��handle
			virtual void initialHandles(){
				m_MVPMatHandle = glGetUniformLocation(getProgram(),"uMVPMat");
				m_ColorHandle = glGetUniformLocation(getProgram(),"uColor");
			}
			//! �ϴ��任����
			virtual void uploadMatrix(mat4f mat){
				glUniformMatrix4fv(m_MVPMatHandle,1,false,(const GLfloat*)&mat);
			}
			//! ׼�����ƣ���һЩ׼��������
			virtual void prepareDraw(){
				COGLESProgram<T>::prepareDraw();
			}
			//! ��һЩ��β����
			virtual void endDraw(){
				COGLESProgram<T>::endDraw();
			}
			//! ��������һ����ɫ��
			virtual EnumProgramType type(){
				return EPT_BaseType;
			}
			//! �ϴ���ɫ
			virtual void uploadColor(colorf c){
				glUniform4fv(m_ColorHandle,1,(const GLfloat*)&c);
			}
		};
	}
}