#pragma once
#include<IDrawProgram.h>
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
			//! 初始化shader
			virtual void initialProgram()=0;
			//! 初始化handle
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
			//! 准备绘制（做一些准备工作）
			virtual void prepareDraw(){
				glUseProgram(m_Program);
			}
			//! 做一些收尾工作
			virtual void endDraw(){
			}
			//! 表明是哪一种着色器
			virtual EnumProgramType type()=0;

			//! 上传指定的vbo
			virtual void uploadVerterBufferObject(IDrawVertexBufferOBject* vbo){}
		};
	}
}