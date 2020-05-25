#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "graphics.h"
#include "Game.h""
//プロトタイプ宣言
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool AnotherInstance();
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hinst; //グローバル変数
HDC hdc;//デバイスコンテキストへのハンドル
TCHAR ch = ' ';
RECT rect;
PAINTSTRUCT ps; //ウィンドウ描画のための情報を持っている構造体
bool vkKeys[256]; //キー入力格納用の仮想キーの配列
Graphics *graphics;//Graphicポインタ
Game *game;//Gameポインタ

//アプリケーションのエントリーポイントの作成

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	#if defined(DEBUG) || defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//メモリリークの検出
	#endif
	MSG msg;
	HWND hwnd = NULL;
	//ウィンドウの作成
	if (!CreateMainWindow(hwnd, hInstance, nCmdShow))
		return 1;


	for (int i = 0; i < 256; i++)//仮想キー配列の初期化
		vkKeys[i] = false;
	try {
		graphics = new Graphics;
		//graphics 初期化
		graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);
		int done = 0;
		while (!done)
		{
			//メッセージを受け取る
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) //終了メッセージを検知した時
					done = 1;

				TranslateMessage(&msg);
				DispatchMessage(&msg);//メッセージをデコードして渡す
			}
			else
			{
				graphics->showBackbuffer();
			}
		}
		SAFE_DELETE(graphics);//ゲーム終了時にメモリ解放
		return msg.wParam;
	}
	catch(const GameError &err)//参照渡しにすることで情報のスライスと破棄された無効値のオブジェクトを catch することを防ぐ
	{
		MessageBox(NULL, err.getMessage(), "Error", MB_OK);
	}
	catch (...)
	{
		MessageBox(NULL, "Unknown error occured in game", "Error", MB_OK);
	}
	SAFE_DELETE(graphics);//ゲーム終了時にメモリ解放
	return 0;
}


bool AnotherInstance()//二重起動による複数インスタンスの実行を防ぐ
{
	HANDLE ourMutex;

	ourMutex = CreateMutex(NULL, true, "Use_a_different_string_here_for_each_program");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return true;
	return false;

}

//ウィンドウ関数
/*LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	short nVirtKey;//仮想キー
	const short SHIFTED = (short)0x8000;
	TEXTMETRIC tm; //文字情報を持つ構造体
	DWORD chWidth = 20; //表示する文字数の幅
	DWORD chHeight = 20; //表示する文字数の高さ

	switch (msg)
	{
		case WM_CREATE://ウィンドウを生成して文字を表示する

			hdc = GetDC(hWnd);//ウィンドウのデバイスコンテキストのハンドルを取得
			GetTextMetrics(hdc, &tm); //バッファにフォントの情報を格納する
			ReleaseDC(hWnd, hdc);//デバイスコンテキストのハンドルを解法
			chWidth = tm.tmAveCharWidth;
			chHeight = tm.tmHeight;
			return 0;

		case WM_DESTROY://終了命令が来たときウィンドウを閉じる
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			vkKeys[wParam] = true;
			switch (wParam)
			{
				case VK_SHIFT://シフト入力時
					nVirtKey = GetKeyState(VK_LSHIFT);
					if(nVirtKey & SHIFTED)
						vkKeys[VK_LSHIFT] = true;//左シフト
					nVirtKey = GetKeyState(VK_RSHIFT);
					if(nVirtKey & SHIFTED)
						vkKeys[VK_RSHIFT] = true;//右シフト
					break;
				case VK_CONTROL:
					nVirtKey = GetKeyState(VK_LCONTROL);
					if(nVirtKey & SHIFTED)
						vkKeys[VK_LCONTROL] = true;//左コントロール
					nVirtKey = GetKeyState(VK_RCONTROL);
					if (nVirtKey & SHIFTED)
						vkKeys[VK_CONTROL] = true;//右コントロール
					break;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;
			break;

		case WM_KEYUP:
			vkKeys[wParam] = false;
			switch (wParam)
			{
				case VK_SHIFT:
					nVirtKey = GetKeyState(VK_LSHIFT);
					if ((nVirtKey & SHIFTED) == 0)
						vkKeys[VK_LSHIFT] = false;//左シフト
					nVirtKey = GetKeyState(VK_RSHIFT);
					if ((nVirtKey & SHIFTED) == 0)
						vkKeys[VK_RSHIFT] = false;//右シフト
					break;
				case VK_CONTROL:
					nVirtKey = GetKeyState(VK_LCONTROL);
					if ((nVirtKey & SHIFTED) == 0)
						vkKeys[VK_LCONTROL] = false;//左コントロール
					nVirtKey = GetKeyState(VK_RCONTROL);
					if ((nVirtKey & SHIFTED) == 0)
						vkKeys[VK_RCONTROL] = false;//右コントロール	
					break;
			}
			InvalidateRect(hWnd, NULL, TRUE);//強制的に描画
			return 0;
			break;

		case WM_CHAR:
			switch (wParam)
			{
				case 0x08: //バックスペース
				case 0x09: //タブ
				case 0x0A: //ラインフィード
				case 0x0D: //キャリッジリターン
				case ESC_KEY: //エスケープ
					PostQuitMessage(0);
					return 0;
			}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//ウィンドウを作成する
bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;
	//ウィンドウクラスの構造体を設定する
	wcx.cbSize = sizeof(wcx); //構造体のサイズ
	wcx.style = CS_HREDRAW | CS_VREDRAW; //ウィンドウサイズ変更時に構造体のサイズ変更
	wcx.lpfnWndProc = WinProc;//ウィンドウプロシージャ(イベントハンドラ)
	wcx.cbClsExtra = 0;//拡張メモリクラス
	wcx.cbWndExtra = 0;//拡張ウィンドウメモリ
	wcx.hInstance = hInstance; //インスタンス識別のためのハンドル
	wcx.hIcon = NULL; //アイコン
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);//カーソル定義(矢印)
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//背景ブラシ
	wcx.lpszMenuName = NULL; //メニューリソースの名前
	wcx.lpszClassName = CLASS_NAME; //ウィンドウクラスの名前
	wcx.hIconSm = NULL; //小さいアイコン

	//ウィンドウクラスの登録
	if (RegisterClassEx(&wcx) == 0)
		return false;

	//画面モードの設定
	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	hwnd = CreateWindow(
		CLASS_NAME,//ウィンドウクラスの名前
		GAME_TITLE,//タイトルバーのテキスト
		style,//ウィンドウのスタイル
		CW_USEDEFAULT,//ウインドウの水平位置のデフォルト
		CW_USEDEFAULT,//Wウインドウの垂直位置のデフォルト
		GAME_WIDTH,//ウィンドウの幅
		GAME_HEIGHT,// ウィンドウの高さ
		(HWND)NULL,// 親ウィンドウなし
		(HMENU)NULL,// メニューなし
		hInstance,// アプリケーションインスタンスへのハンドル
		(LPVOID)NULL// ウィンドウパラメータなし
	);
	if (!hwnd)//ウィンドウ作成失敗時
		return false;
	if (!FULLSCREEN) {
		//クライアント領域を GAME_WIDTH * GAME_HEIGHTとなるように変更
		RECT clientRect;
		//ウィンドウのクライアント領域のサイズ取得
		GetClientRect(hwnd, &clientRect);
		MoveWindow(
			hwnd,
			0,//左
			0,//上
			GAME_WIDTH + (GAME_WIDTH - clientRect.right),//右
			GAME_HEIGHT + (GAME_HEIGHT - clientRect.left),//下
			TRUE
		);

	}
	//ウィンドウ表示
	ShowWindow(hwnd, nCmdShow);

	UpdateWindow(hwnd);
	return true;
}*/

LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return (game->messageHandler(hwnd, msg, wParam, lParam));
}
