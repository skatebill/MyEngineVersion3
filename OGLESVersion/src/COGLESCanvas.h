#pragma once
#include <drawBasement/ICanvas.h>
#include<viewer/IMatrixStack.h>
namespace xc{
	namespace drawBasement{
		class COGLESCanvas:public ICanvas{
		private:
			shared_ptr<IDrawCotext> mContext;
			recti mRect;
			shared_ptr<viewer::ICamera> mCurrentCamera;
			EnumProjectionType mProjectionType;
			float mAngle;
			shared_ptr<viewer::IMatStack> mMatStack;
			mat4 mProjectionMat;
			mat4 mViewTempMat;
			shared_ptr<IDrawProgram> mCurrentProgram;
		public:
			COGLESCanvas(shared_ptr<IDrawCotext> context,shared_ptr<viewer::IMatStack> matStack){
				mContext = context;
				mProjectionType = type_perspective;
				mAngle = 45;
				mMatStack = matStack;
			}
			//! 指定绘制用的program 
			//! 绘制指定物体
			virtual void render(IDrawBuffer* vbuf,IDrawIndexBuffer* ibuf);
			virtual void render(IDrawVertexBufferOBject* vbo);

			//! 设置投影方式
			virtual void setProjectionType(EnumProjectionType type,float perspective_angle){
				mProjectionType = type;
				mAngle = perspective_angle;
				switch (type)
				{
				case xc::drawBasement::type_ortho:
					
					if(mContext->getCoordinateType() == RIGHT_HAND){
						mProjectionMat.buildProjectionMatrixOrthoRH((float)mRect.getWidth(),(float)mRect.getHeight(),0.001f,100.f);
					}else{
						mProjectionMat.buildProjectionMatrixOrthoLH((float)mRect.getWidth(),(float)mRect.getHeight(),0.001f,100.f);
					}
					
					break;
				case xc::drawBasement::type_perspective:
					{
						if(mContext->getCoordinateType() == RIGHT_HAND){
							mProjectionMat.buildProjectionMatrixPerspectiveFovRH(mAngle,mRect.getWidth()/(float)mRect.getHeight(),0.001f,100.f);
						}else{
							mProjectionMat.buildProjectionMatrixPerspectiveFovLH(mAngle,mRect.getWidth()/(float)mRect.getHeight(),0.001f,100.f);
						}

					}
					break;
				default:
					break;
				}
			}
			//! 为canvas绑定camera
			virtual void attachCamera(shared_ptr<viewer::ICamera> cam){
				mCurrentCamera = cam;
			}
			//! 设置canvas的大小
			virtual void setCanvasRect(recti r){
				mRect = r;
			}
			//! 获取canvas的大小
			virtual recti getCanvasRect(){
				return mRect;
			}
			//! 获取投影矩阵
			virtual mat4 getProjectionMatrix(){
				return mProjectionMat;
			}
			//! 获取观察矩阵
			virtual mat4 getViewMatrix(){
				if(mCurrentCamera->isChanged()){
					mViewTempMat = mCurrentCamera->getViewMatrix();
					if(mContext->getCoordinateType() == LEFT_HAND){
						mViewTempMat = mViewTempMat.getTransposed();
					}
				}
				return mViewTempMat;
			}
			//! 获取世界变换矩阵
			virtual mat4 getWorldTranslateMatrix(){
				return mMatStack->getWorldTransMat();
			}
			//! 获取矩阵变化器
			virtual viewer::IMatStack* getMatStack(){
				return mMatStack.get();
			}
			//! 指定绘制用的program
			virtual void attachShader(shared_ptr<IDrawProgram> program){
				mCurrentProgram = program;
			}
		};
	}
}