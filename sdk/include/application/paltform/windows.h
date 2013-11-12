
#ifndef CLASS_REG
#error no class registerd
#endif
#include <windows.h>
#include<gl/glew.h>
namespace temp{
	HWND hwnd;
	const char* windowName="";
	CLASS_REG abc;
	unsigned int width=800;
	unsigned int height=600;

	void setWindowName(const char* name){
		windowName = name;
	}
	void setWindowSize(unsigned int w,unsigned int h){
		width = w;
		height = h;
	}
}


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
}

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	temp::abc.onInitialWindow(temp::setWindowName,temp::setWindowSize);
	create(hInstance,temp::width,temp::height);
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
		}

	}
}
