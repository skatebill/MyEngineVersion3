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

			mIndex->reSizeBuffer(24);
			mIndex->setIndexNums(24);
			mIndex->setPrimityType(drawBasement::EPT_TRIANGLES);
			unsigned char* ibuf = (unsigned char*)mIndex->lock();
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

			mCamera->goForward(-5);
			//mCamera->setCamera(vector3df(0,0,-5),vector3df(0,0,0));

			mtexture = this->getSite()->getDrawFactory()->getTextureFactory()->createTextureFromImage(this->getSite()->getFileService()->
				createImageFromFile("1.bmp").get());

			auto f = getSite()->getFileService()->createReadableFile(L"1234.txt");
			string filename = f->getAbsolutePath();
			auto fsize = f->getFileSize();
			string name = f->getFileName();
		}
		//! 销毁
		void myapp::onCleanup(){

		}
		//! 绘制
		void myapp::onRender(){
			m_Context->clearScreenColor(mScreenColor);
			m_Context->clearDepthBuffer();
			mProg->prepareDraw();
			mat4 w=mCanvas->getWorldTranslateMatrix();
			mat4 v=mCanvas->getViewMatrix();
			mat4 p=mCanvas->getProjectionMatrix();
			mProg->uploadMatrix(p*v*w);
			mProg->uploadTexture(mtexture.get());
			mtex->use(1);
			mCanvas->draw(mVertex,mIndex);
			mProg->endDraw();
			m_Context->presentData();
		}
	}
}