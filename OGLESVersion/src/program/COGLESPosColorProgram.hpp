#pragma once
#include <drawBasement/IDrawProgram.h>
namespace xc{
	namespace drawBasement{
		static const char* pQPCVS = "                                                    \n\
								  \n\
								  attribute vec3 Position;                                       \n\
								  attribute vec4 Color;										\n\
								  uniform mat4 uMVPMat;                                                         \n\
								  uniform float uPointSize;                                                         \n\
								  \n\
								  varying vec4 vColor;															\n\
								  void main()                                                                   \n\
								  {                                                                             \n\
									gl_PointSize = 10.0;   \n\
									vColor = Color;                                                       \n\
									gl_Position = uMVPMat *vec4( Position.x, Position.y, Position.z, 1.0);   \n\
								  }";

		static const char* pQPCFS = "precision mediump float;                                                   \n\
								   varying vec4 vColor;															\n\
								  void main()                                                                   \n\
								  {                                                                             \n\
								  gl_FragColor = vColor;													     \n\
								  }";


		template<typename T>
		class COGLESPosColorProgramQ:public COGLESProgram<T>{
		private:
			GLuint mMatHandle;
			GLuint mPosHandle;
			GLuint mColorHandle;
		public:
			virtual void initialProgram(){
				AddShader(getProgram(),pQPCVS,GL_VERTEX_SHADER);
				AddShader(getProgram(),pQPCFS,GL_FRAGMENT_SHADER);
				linkProgram(getProgram());
				initialHandles();

			}
			//! ��ʼ��handle
			virtual void initialHandles(){
				mMatHandle = glGetUniformLocation(getProgram(),"uMVPMat");
				mPosHandle = glGetAttribLocation(getProgram(),"Position");
				mColorHandle = glGetAttribLocation(getProgram(),"Color");
				if(mMatHandle == 0xFFFFFFFF) throw std::exception();

			}
			//! �ϴ��任����
			virtual void uploadMatrix(mat4f mat){
				glUniformMatrix4fv(mMatHandle,1,false,(const GLfloat*)&mat);
			}
			//! ���� �������
			virtual EnumProgramType type(){
				return EPT_PosColor;
			}
		};
	}
}