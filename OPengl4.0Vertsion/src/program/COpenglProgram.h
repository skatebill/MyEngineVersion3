#pragma once
#include<drawBasement/IDrawProgram.h>
#include<gl/glew.h>
#include <string>
namespace xc{
	namespace drawBasement{
		void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
		void linkProgram(GLuint ShaderProgram);

		template<typename T>
		class COpenglProgram:public T{
		private:
			GLuint m_Program;

		public:
			//! ��ʼ��shader
			virtual void initialProgram()=0;
			//! ��ʼ��handle
			virtual void initialHandles()=0;

			COpenglProgram():m_Program(0){
				m_Program = glCreateProgram();
				if(m_Program == 0){
					throw std::exception("error createProgram");
				}
				glUseProgram(m_Program);
			}
			~COpenglProgram(){
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

			//! �ϴ�ָ����vbo
			virtual void uploadVerterBufferObject(IDrawVertexBufferOBject* vbo){}
		};
	}
}