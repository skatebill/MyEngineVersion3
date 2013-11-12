#pragma once
#include"COpenglProgram.h"
namespace xc{
	namespace drawBasement{
		class COpenglBaseProgram:public COpenglProgram<IBaseProgram>{
		public:
			//! 上传世界变换矩阵
			virtual void uploadWorldTranslateMatrix(mat4f mat)=0;
			//! 上传投影变换矩阵
			virtual void uploadProjectionMatrix(mat4f mat)=0;
			//! 上传视点变换矩阵
			virtual void uploadViewMatrix(mat4f mat)=0;

		};

		class COpenglBaseProgramQ:public COpenglProgram<IBaseProgramQ>{
		private:
			virtual void initialProgram();
			GLuint m_MVPMatHandle;
			GLuint m_ColorHandle;
		public:
			explicit COpenglBaseProgramQ();

			//! 上传变换矩阵
			virtual void uploadMatrix(mat4f mat);
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
			virtual void uploadColor(colorf c);

		};
	}
}