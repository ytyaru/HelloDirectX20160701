#include <windows.h>
#include <tchar.h>
#include <d3d9.h>

TCHAR className[100] = _T("HelloDirectX20160701");
TCHAR title[100] = _T("Hello DirectX !! こんにちはDirectX！");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return (0L);
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG msg; HWND hWnd;
	WNDCLASSEX wcex ={ sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, NULL, NULL, (HBRUSH)(COLOR_WINDOW+1), NULL, (TCHAR*)className, NULL };
	if(!RegisterClassEx(&wcex)) return 0;

	if(!(hWnd = CreateWindow(className, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL)))
		return 0;

	// Direct3Dの初期化
	LPDIRECT3D9 g_pD3D;
	LPDIRECT3DDEVICE9 g_pD3DDev;
	if( !(g_pD3D = Direct3DCreate9( D3D_SDK_VERSION )) ) return 0;

	D3DPRESENT_PARAMETERS d3dpp = { 0, 0, D3DFMT_UNKNOWN, 0, D3DMULTISAMPLE_NONE, 0, D3DSWAPEFFECT_DISCARD, NULL, TRUE, 0, D3DFMT_UNKNOWN, 0, 0 };

	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDev ) ) )
	{ g_pD3D->Release(); return 0; }

	ShowWindow(hWnd, nCmdShow);

	// メッセージ ループ
	do{
		Sleep(1);
		if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ){ DispatchMessage(&msg);}
		else{
			g_pD3DDev->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );
			g_pD3DDev->BeginScene();

			// 何か描画する

			g_pD3DDev->EndScene();
			g_pD3DDev->Present( NULL, NULL, NULL, NULL );
		}
	} while(msg.message != WM_QUIT);

	g_pD3DDev->Release();
	g_pD3D->Release();

	return 0;
}