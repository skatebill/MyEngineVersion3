#include <windows.h>
#include<GL/glew.h>
#include<GL/glut.h>
#include"src/COpenglFactory.h"
//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}
xc::drawBasement::COpenglFactory f;
xc::shared_ptr<xc::drawBasement::IDrawCotext> t;
void create( HINSTANCE hInstance ,int w,int h)
{

	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )107 );
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"MyWindowClass";
	wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )107 );
	if( !RegisterClassEx( &wcex ) )
		return;
	DWORD styles = (CS_OWNDC|WS_OVERLAPPEDWINDOW) & ~(WS_SIZEBOX |WS_MAXIMIZEBOX|WS_MINIMIZEBOX) ;
	RECT rc = { 0, 0, w, h };
	AdjustWindowRect( &rc, styles , FALSE);

	int screenW=GetSystemMetrics(SM_CXSCREEN);
	int screenH=GetSystemMetrics(SM_CYSCREEN);
	int newposx= (screenW>>1)-((rc.right - rc.left)>>1);
	int newposy= (screenH>>1)-((rc.bottom - rc.top)>>1);

	HWND hwnd = CreateWindow( L"MyWindowClass", L"hello world", styles,
		newposx, newposy, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL );
	if( !hwnd )
		return;
	ShowWindow( hwnd, SW_SHOW );
	t = f.createDrawContext(&hwnd);
}

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	create(hInstance,800,600);
	auto vbuf = f.createVertexBuffer();
	auto ibuf = f.createIndexBuffer();
	auto prog = f.getProgramFactory()->createBaseQuickProgram();
	auto drawer = f.createDrawer();
	vbuf->reSizeBuffer(sizeof(xc::vector3df)*6);
	xc::vector3df* buf = (xc::vector3df*)vbuf->lock();
	buf[0] = xc::vector3df(0,0,0);
	buf[1] = xc::vector3df(0,0.2,0);
	buf[2] = xc::vector3df(0.2,0.2,0);
	buf[3] = xc::vector3df(0,0,0);
	buf[4] = xc::vector3df(0,-0.2,0);
	buf[5] = xc::vector3df(-0.2,-0.2,0);
	vbuf->setElemtSize(3);
	vbuf->initialBuffer();

	ibuf->reSizeBuffer(6);
	unsigned char* ib = ibuf->lock();
	ibuf->setPrimityType(xc::drawBasement::EPT_TRIANGLES);
	ibuf->setIndexNums(6);
	for(int i=0;i<6;++i){
		ib[i]=i;
	}
	ibuf->initialBuffer();
	xc::mat4 m;
	m.makeIdentity();

	MSG msg = {0};

	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			t->clearScreenColor(xc::color::BLUE);
			prog->prepareDraw();
			prog->uploadMatrix(m);
			prog->uploadColor(xc::color::GREEN);
			drawer->draw(vbuf,ibuf,t);
			prog->endDraw();
			t->presentData();
		}

	}
}
