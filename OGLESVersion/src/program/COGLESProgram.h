#pragma once
#include<drawBasement/IDrawProgram.h>
#include<GLES2/gl2.h>
#include <string>
namespace xc{
	namespace drawBasement{
		void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
		void linkProgram(GLuint ShaderProgram);

		template<typename T>
		class COGLESProgram:public T{
		private:
			GLuint m_Program;

		public:
			//! ��ʼ��shader
			virtual void initialProgram()=0;
			//! ��ʼ��handle
			virtual void initialHandles()=0;

			COGLESProgram():m_Program(0){
				m_Program = glCreateProgram();
				if(m_Program == 0){
					throw std::exception();
				}
				glUseProgram(m_Program);
			}
			~COGLESProgram(){
				glDeleteProgram(m_Program);
			}
			inline GLuint getProgram(){
				return m_Program;
			}
			//! ׼�����ƣ���һЩ׼��������
			virtual void prepareDraw(){
				glUseProgram(m_Program);
			}
			//! ��һЩ��β����
			virtual void endDraw(){
			}
			//! ��������һ����ɫ��
			virtual EnumProgramType type()=0;

			virtual void uploadVerterBufferObject(IDrawVertexBufferOBject* vbo){

			}

		};
	}
}