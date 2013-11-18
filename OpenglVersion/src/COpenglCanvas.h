#pragma once
#include <ICanvas.h>
#include<viewer/IMatrixStack.h>
namespace xc{
	namespace drawBasement{
		class COpenglCanvas:public ICanvas{
		private:
			shared_ptr<IDrawCotext> mContext;
			recti mRect;
			shared_ptr<viewer::ICamera> mCurrentCamera;
			EnumProjectionType mProjectionType;
			float mAngle;
			shared_ptr<viewer::IMatStack> mMatStack;
			mat4 mProjectionMat;
			mat4 mViewTempMat;
		public:
			COpenglCanvas(shared_ptr<IDrawCotext> context,shared_ptr<viewer::IMatStack> matStack){
				mContext = context;
				mProjectionType = type_perspective;
				mAngle = 45;
				mMatStack = matStack;
			}
			//! ָ�������õ�program 
			//! ����ָ������
			virtual void draw(IDrawBuffer* vbuf,IDrawIndexBuffer* ibuf);

			//! ����ͶӰ��ʽ
			virtual void setProjectionType(EnumProjectionType type,float perspective_angle){
				mProjectionType = type;
				mAngle = perspective_angle;
				switch (type)
				{
				case xc::drawBasement::type_ortho:
					
					if(mContext->getCoordinateType() == RIGHT_HAND){
						mProjectionMat.buildProjectionMatrixOrthoRH((float)mRect.getWidth(),(float)mRect.getHeight(),0.001f,1000.f);
					}else{
						mProjectionMat.buildProjectionMatrixOrthoLH((float)mRect.getWidth(),(float)mRect.getHeight(),0.001f,1000.f);
					}
					
					break;
				case xc::drawBasement::type_perspective:
					{
						if(mContext->getCoordinateType() == RIGHT_HAND){
							mProjectionMat.buildProjectionMatrixPerspectiveFovRH(mAngle,mRect.getWidth()/(float)mRect.getHeight(),0.001f,1000.f);
						}else{
							mProjectionMat.buildProjectionMatrixPerspectiveFovLH(mAngle,mRect.getWidth()/(float)mRect.getHeight(),0.001f,1000.f);
						}

					}
					break;
				default:
					break;
				}
			}
			//! Ϊcanvas��camera
			virtual void attachCamera(shared_ptr<viewer::ICamera> cam){
				mCurrentCamera = cam;
			}
			//! ����canvas�Ĵ�С
			virtual void setCanvasRect(recti r){
				mRect = r;
			}
			//! ��ȡcanvas�Ĵ�С
			virtual recti getCanvasRect(){
				return mRect;
			}
			//! ��ȡͶӰ����
			virtual mat4 getProjectionMatrix(){
				return mProjectionMat;
			}
			//! ��ȡ�۲����
			virtual mat4 getViewMatrix(){
				if(mCurrentCamera->isChanged()){
					mViewTempMat = mCurrentCamera->getViewMatrix();
					if(mContext->getCoordinateType() == LEFT_HAND){
						mViewTempMat = mViewTempMat.getTransposed();
					}
				}
				return mViewTempMat;
			}
			//! ��ȡ����任����
			virtual mat4 getWorldTranslateMatrix(){
				return mMatStack->getWorldTransMat();
			}
			//! ��ȡ����仯��
			virtual viewer::IMatStack* getMatStack(){
				return mMatStack.get();
			}
		};
	}
}