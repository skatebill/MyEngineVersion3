#pragma once
#include"COpenglProgram.h"
namespace xc{
	namespace drawBasement{
		class COpenglBaseProgram:public COpenglProgram<IBaseProgram>{
		public:
			//! �ϴ�����任����
			virtual void uploadWorldTranslateMatrix(mat4f mat)=0;
			//! �ϴ�ͶӰ�任����
			virtual void uploadProjectionMatrix(mat4f mat)=0;
			//! �ϴ��ӵ�任����
			virtual void uploadViewMatrix(mat4f mat)=0;

		};

		class COpenglBaseProgramQ:public COpenglProgram<IBaseProgramQ>{
		private:
			virtual void initialProgram();
			GLuint m_MVPMatHandle;
			GLuint m_ColorHandle;
		public:
			explicit COpenglBaseProgramQ();

			//! �ϴ��任����
			virtual void uploadMatrix(mat4f mat);
			//! ׼�����ƣ���һЩ׼��������
			virtual void prepareDraw(){
				COpenglProgram::prepareDraw();
			}
			//! ��һЩ��β����
			virtual void endDraw(){
				COpenglProgram::endDraw();
			}
			//! ��������һ����ɫ��
			virtual EnumProgramType type(){
				return EPT_BaseType;
			}
			//! �ϴ���ɫ
			virtual void uploadColor(colorf c);

		};
	}
}