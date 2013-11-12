#include "COpenglBaseProgram.h"

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

namespace xc{
	namespace drawBasement{
		COpenglBaseProgramQ::COpenglBaseProgramQ(){
			initialProgram();
		}

		void COpenglBaseProgramQ::initialProgram(){
			AddShader(getProgram(),pQVS,GL_VERTEX_SHADER);
			AddShader(getProgram(),pQFS,GL_FRAGMENT_SHADER);
			linkProgram(getProgram());
			m_MVPMatHandle = glGetUniformLocation(getProgram(),"uMVPMat");
			m_ColorHandle = glGetUniformLocation(getProgram(),"uColor");

		}
		void COpenglBaseProgramQ::uploadMatrix(mat4f mat){
			glUniformMatrix4fv(m_MVPMatHandle,1,false,(const GLfloat*)&mat);
		}
		//! ÉÏ´«ÑÕÉ«
		void COpenglBaseProgramQ::uploadColor(colorf c){
			glUniform4fv(m_ColorHandle,1,(const GLfloat*)&c);
		}
	}
}