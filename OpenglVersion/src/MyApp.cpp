#include"MyApp.h"
#include "irrMath.h"
namespace xc{
	namespace app{
		//! 鼠标事件
		void myapp::onMouseEvent(EnumMouse mouse,MouseEvent ev,vector2di pos){
			switch (mouse)
			{
			case xc::app::Mouse_L:
				{
					switch (ev)
					{
					case xc::app::Mouse_Click:
						{
							mScreenColor = color::WHITE;
						}
						break;
					case xc::app::Mouse_Down:
						{

						}
						break;
					case xc::app::Mouse_Up:
						{

						}
						break;
					case xc::app::Mouse_DClick:
						{
							mScreenColor = color::BLACK;

						}
						break;
					default:
						break;
					}
				}
				break;
			case xc::app::Mouse_R:
				{
					switch (ev)
					{
					case xc::app::Mouse_Click:
						{
							mScreenColor = color::GREEN;

						}
						break;
					case xc::app::Mouse_Down:
						{

						}
						break;
					case xc::app::Mouse_Up:
						{

						}
						break;
					case xc::app::Mouse_DClick:
						{
							mScreenColor = color::BLUE;

						}
						break;
					default:
						break;
					}				

				}
				break;
			case xc::app::Mouse_M:
				break;
			default:
				break;
			}
		}
		//! 键盘事件
		void myapp::onKeyEvent(KeyEvent key,int keyCode){
		}
		//! 初始化
		void myapp::onInitialData(){
			m_Context = this->getSite()->getDrawFactory()->createDrawContext(getExtraData());
			mScreenColor = color::RED;

			mIndex = this->getSite()->getDrawFactory()->createIndexBuffer();
			mVertex = this->getSite()->getDrawFactory()->createVertexBuffer();

			mProg = this->getSite()->getDrawFactory()->getProgramFactory()->createBaseQuickTextureProgram();
			mBoneProg = this->getSite()->getDrawFactory()->getProgramFactory()->createBaseQuickBonedProgram();
			mVertex->reSizeBuffer(sizeof(vector3df)*8);
			mVertex->setElemtSize(3);
			vector3df* vbuf = (vector3df*)mVertex->lock();

			vbuf[0] = vector3df(-1,-1,1);
			vbuf[1] = vector3df(1,-1,1);
			vbuf[2] = vector3df(1,-1,-1);
			vbuf[3] = vector3df(-1,-1,-1);
			vbuf[4] = vector3df(-1,1,1);
			vbuf[5] = vector3df(1,1,1);
			vbuf[6] = vector3df(1,1,-1);
			vbuf[7] = vector3df(-1,1,-1);
			mVertex->initialBuffer();

			mtex = this->getSite()->getDrawFactory()->createVertexBuffer();
			mtex->reSizeBuffer(sizeof(vector2df)*8);
			mtex->setElemtSize(2);
			vector2df* tbuf = (vector2df*)mtex->lock();

			tbuf[0] = vector2df(0,0);
			tbuf[1] = vector2df(1,0);
			tbuf[2] = vector2df(0,0);
			tbuf[3] = vector2df(0,0);
			tbuf[4] = vector2df(0,1);
			tbuf[5] = vector2df(1,1);
			tbuf[6] = vector2df(0,0);
			tbuf[7] = vector2df(0,0);
			mtex->initialBuffer();

			mIndex->reSizeBuffer(24*2);
			mIndex->setIndexNums(24);
			mIndex->setPrimityType(drawBasement::EPT_TRIANGLES);
			unsigned short* ibuf = (unsigned short*)mIndex->lock();
			int i=0;
			ibuf[i++]=0;
			ibuf[i++]=1;
			ibuf[i++]=5;

			ibuf[i++]=0;
			ibuf[i++]=5;
			ibuf[i++]=4;

			ibuf[i++]=1;
			ibuf[i++]=2;
			ibuf[i++]=6;

			ibuf[i++]=1;
			ibuf[i++]=6;
			ibuf[i++]=5;


			ibuf[i++]=2;
			ibuf[i++]=3;
			ibuf[i++]=7;

			ibuf[i++]=2;
			ibuf[i++]=7;
			ibuf[i++]=6;


			ibuf[i++]=3;
			ibuf[i++]=0;
			ibuf[i++]=4;

			ibuf[i++]=3;
			ibuf[i++]=4;
			ibuf[i++]=7;

			mIndex->initialBuffer();

			mCanvas = this->getSite()->getDrawFactory()->createCanvas(m_Context,this->getSite()->getViewerFactory()->createMatStack());
			mCanvas->setCanvasRect(m_Context->getWindowRect());
			mCanvas->setProjectionType(drawBasement::type_perspective,45);
			mCamera = this->getSite()->getViewerFactory()->createCamera();
			mCanvas->attachCamera(mCamera);

			mCamera->goForward(-15);
			//mCamera->setCamera(vector3df(0,0,-5),vector3df(0,0,0));

			mtexture = this->getSite()->getDrawFactory()->getTextureFactory()->createTextureFromImage(this->getSite()->getFileService()->
				createImageFromFile("phoenix.pcx").get());

			

			m_VBO =this->getSite()->getDrawFactory()->createVertexBufferObject(mVertex,mIndex,mtex);

			mProg2 = this->getSite()->getDrawFactory()->getProgramFactory()->createBaseQuickProgram();

			auto index = this->getSite()->getDrawFactory()->createIndexBuffer();
			auto vertex = this->getSite()->getDrawFactory()->createVertexBuffer();
			vertex->reSizeBuffer(sizeof(vector3df)*8);
			vertex->setElemtSize(3);
			vbuf = (vector3df*)vertex->lock();

			vbuf[0] = vector3df(-1,-1,0);
			vbuf[1] = vector3df(1,-1,0);
			vbuf[2] = vector3df(1,1,0);
			vbuf[3] = vector3df(-1,1,0);
			vertex->initialBuffer();

			index->reSizeBuffer(6*2);
			index->setIndexNums(6);
			index->setPrimityType(drawBasement::EPT_TRIANGLES);
			ibuf = (unsigned short*)index->lock();
			i=0;
			ibuf[i++]=0;
			ibuf[i++]=1;
			ibuf[i++]=2;

			ibuf[i++]=0;
			ibuf[i++]=2;
			ibuf[i++]=3;

			index->initialBuffer();
			m_VBO2 =this->getSite()->getDrawFactory()->createVertexBufferObject(vertex,index);

			mModle = getSite()->getPhraser()->loadModelFromFile("models/boblampclean.md5mesh");
			
		}
		//! 销毁
		void myapp::onCleanup(){

		}
		//! 绘制
		void myapp::onRender(){
			m_Context->clearScreenColor(mScreenColor);
			m_Context->clearDepthBuffer();
			mProg->prepareDraw();
			mCanvas->getMatStack()->push();
			mCanvas->getMatStack()->translate(vector3df(-1,0,0));
			mat4 w=mCanvas->getWorldTranslateMatrix();
			mat4 v=mCanvas->getViewMatrix();
			mat4 p=mCanvas->getProjectionMatrix();
			mProg->uploadMatrix(p*v*w);
			mProg->uploadTexture(mtexture.get());
			//mCanvas->render(m_VBO);
			mProg->endDraw();
			mCanvas->getMatStack()->pop();

			mCanvas->getMatStack()->push();
			static float y=0;
			//mCanvas->getMatStack()->mutipleMatrix(mModle->getBaseTranslateMatrix());
			mCanvas->getMatStack()->scale(vector3df(0.1f,0.1f,0.1f));
			//y+=0.01;
			mCanvas->getMatStack()->rotate(y,vector3df(0,1,0));
			mCanvas->getMatStack()->translate(vector3df(0,-1,0));
			static float frame = 0;
			frame+=0.15f;
			if(frame>54) frame = 0;
			mModle->getBoneAnimator()->setCurrentFrame(frame);
			mBoneProg->prepareDraw();
			mBoneProg->uploadTexture(mtexture.get());
			w=mCanvas->getWorldTranslateMatrix();
			v=mCanvas->getViewMatrix();
			p=mCanvas->getProjectionMatrix();
			mBoneProg->uploadMatrix(p*v*w);
			mBoneProg->uploadBoneMatrix(mModle->getBoneAnimator()->getUniformMatrixBuffer(),mModle->getBoneAnimator()->getUniformMatrixSize());
			mModle->render(mCanvas.get());
			mBoneProg->endDraw();
			mCanvas->getMatStack()->pop();

		/*	mCanvas->getMatStack()->push();
			static float y=0;
			mCanvas->getMatStack()->mutipleMatrix(mModle->getBaseTranslateMatrix());
			mCanvas->getMatStack()->scale(vector3df(0.1f,0.1f,0.1f));
			y+=0.01;
			mCanvas->getMatStack()->rotate(y,vector3df(0,1,0));
			mCanvas->getMatStack()->translate(vector3df(0,-1,0));
			static float frame = 0;
			frame+=0.5f;
			if(frame>10) frame = 0;
			mProg->prepareDraw();
			mProg->uploadTexture(mtexture.get());
			w=mCanvas->getWorldTranslateMatrix();
			v=mCanvas->getViewMatrix();
			p=mCanvas->getProjectionMatrix();
			mProg->uploadMatrix(p*v*w);
			mModle->render(mCanvas.get());
			mProg->endDraw();
			mCanvas->getMatStack()->pop();*/

			m_Context->presentData();
			
		}
	}
}