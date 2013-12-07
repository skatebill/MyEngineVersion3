//////////////////////////////////////////////////////////////////////////
//
//		3d�������Ľӿ�
//		����ʹ�ø�����program resource context ����3d����
//		author by Ф�� @ 2013��11��3��2:42:15
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDrawBuffers.h"
#include "IDrawContext.h"
#include <viewer/ICamera.h>
#include <viewer/IMatrixStack.h>
#include<drawBasement/IDrawProgram.h>
namespace xc{
	namespace drawBasement{
		enum EnumProjectionType{
			type_ortho,
			type_perspective
		};
		class ICanvas{
		public:
			//! ����ͶӰ��ʽ
			virtual void setProjectionType(EnumProjectionType type,float perspective_angle)=0;
			//! Ϊcanvas��camera
			virtual void attachCamera(shared_ptr<viewer::ICamera> cam)=0;
			//! ����canvas�Ĵ�С
			virtual void setCanvasRect(recti r)=0;
			//! ��ȡcanvas�Ĵ�С
			virtual recti getCanvasRect()=0;
			//! ��ȡͶӰ����
			virtual mat4 getProjectionMatrix()=0;
			//! ��ȡ�۲����
			virtual mat4 getViewMatrix()=0;
			//! ��ȡ����任����
			virtual mat4 getWorldTranslateMatrix()=0;
			//! ��ȡ����仯��
			virtual viewer::IMatStack* getMatStack()=0;
			//! ����ָ������
			virtual void render(IDrawBuffer* vbuf,IDrawIndexBuffer* ibuf)=0;
			//! ����vbo
			virtual void render(IDrawVertexBufferOBject* vbo)=0;
			//! ָ�������õ�program
			virtual void attachShader(shared_ptr<IDrawProgram> program)=0;
			//////////////////////////////////////////////////////////////////////////
			//! ����ָ������
			void render(shared_ptr<IDrawBuffer> vbuf,shared_ptr<IDrawIndexBuffer> ibuf){
				render(vbuf.get(),ibuf.get());
			}
			void render(shared_ptr<IDrawVertexBufferOBject> vbo){
				render(vbo.get());
			}
		};
	}
}