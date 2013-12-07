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
			//! 初始化shader
			virtual void initialProgram()=0;
			//! 初始化handle
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
			//! 准备绘制（做一些准备工作）
			virtual void prepareDraw(){
				glUseProgram(m_Program);
			}
			//! 做一些收尾工作
			virtual void endDraw(){
			}
			//! 表明是哪一种着色器
			virtual EnumProgramType type()=0;

			virtual void uploadVerterBufferObject(IDrawVertexBufferOBject* vbo){

			}

		};
	}
}