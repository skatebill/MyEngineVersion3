#include"COpenglProgram.h"

namespace xc{
	namespace drawBasement{
		void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
		{
			GLuint ShaderObj = glCreateShader(ShaderType);

			if (ShaderObj == 0) {
				throw std::exception("error createShaders");
			}

			const GLchar* p[1];
			p[0] = pShaderText;
			GLint Lengths[1];
			Lengths[0]= strlen(pShaderText);
			glShaderSource(ShaderObj, 1, p, Lengths);
			glCompileShader(ShaderObj);
			GLint success;
			glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
			if (!success) {
				GLchar InfoLog[1024];
				glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
				throw std::exception("error compileShaders");
			}

			glAttachShader(ShaderProgram, ShaderObj);
		}
		void linkProgram(GLuint ShaderProgram){
			GLint Success = 0;
			glLinkProgram(ShaderProgram);
			glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
			if (Success == 0) {
				throw std::exception("error linkShaders");
			}

			glValidateProgram(ShaderProgram);
			glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
			if (!Success) {
				throw std::exception("error validateShaders");
			}

			glUseProgram(ShaderProgram);
		}

	}
}