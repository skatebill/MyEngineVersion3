//////////////////////////////////////////////////////////////////////////
//		���ƹ��ߵ���ɫ���ӿ�
//		author by Ф�� @ 2013��11��3��2:44:18
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MyTypes.h"
#include<IDrawTexture.h>
namespace xc{
	namespace drawBasement{
		enum EnumProgramType
		{
			EPT_BaseType=0,
			EPT_Textured,
			EPT_Normaled
		};
		class IDrawProgram{
		public:
			//! ׼�����ƣ���һЩ׼��������
			virtual void prepareDraw()=0;
			//! ��һЩ��β����
			virtual void endDraw()=0;
			//! ��������һ����ɫ��
			virtual EnumProgramType type()=0;
		};

		class IBaseProgramQ:public IDrawProgram{
		public:
			//! �ϴ��任����
			virtual void uploadMatrix(mat4f mat)=0;
			//! �ϴ���ɫ
			virtual void uploadColor(colorf c)=0;
		};

		class IBaseProgram:public IDrawProgram{
		public:
			//! �ϴ�����任����
			virtual void uploadWorldTranslateMatrix(mat4f mat)=0;
			//! �ϴ�ͶӰ�任����
			virtual void uploadProjectionMatrix(mat4f mat)=0;
			//! �ϴ��ӵ�任����
			virtual void uploadViewMatrix(mat4f mat)=0;
			//! �ϴ���ɫ
			virtual void uploadColor(colorf c)=0;
		};

		class IBasedTextureProgramQ:public IBaseProgramQ{
		public:
			//! �ϴ�����
			virtual void uploadTexture(IDrawTexture2D* tex)=0;
		};

		class IProgramFactory{
		public:
			//! �����������shader
			virtual shared_ptr<IBaseProgram> createBaseProgram()=0;
			//! �������ٰ汾�Ļ���shader
			virtual shared_ptr<IBaseProgramQ> createBaseQuickProgram()=0;
			//! �������ٰ汾�Ļ�������shader
			virtual shared_ptr<IBasedTextureProgramQ> createBaseQuickTextureProgram()=0;
		};

	}
}