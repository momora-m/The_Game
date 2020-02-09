#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//プロトタイプ宣言
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hinst; //グローバル変数
HDC hdc;
TCHAR ch = ' ';
RECT rect;
PAINTSTRUCT ps; //ウィンドウ描画のための情報を持っている構造体
const char CLASS_NAME[] = "WinMain";
const char APP_TITLE[] = "Hello Game";
//ウィンドウサイズ宣言
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
//アプリケーションのエントリーポイントの作成
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	//ウィンドウの作成
	if (!CreateMainWindow(hInstance, nCmdShow))
		return false;
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
	}
	return msg.wParam;
}
//ウィンドウ関数
LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY://終了命令が来たとき
		PostQuitMessage(0);
		return 0;
	case WM_CHAR:
		switch (wParam)
		{
		case 0x08: //バックスペース
		case 0x09: //タブ
		case 0x0A: //ラインフィード
		case 0x0D: //キャリッジリターン
		case 0x1B: //エスケープ
			MessageBeep((UINT)-1);//表示できない文字はビープ音を鳴らす
			return 0;
		default:
			ch = (TCHAR)wParam;
			InvalidateRect(hwnd, NULL, TRUE);//矩形を強制描画
			return 0;
		}
	case WM_PAINT:
		//デバイスコンテキストへのハンドルを取得	
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect); //ウィンドウの矩形を取得
		TextOut(hdc, rect.right / 2, rect.bottom / 2, &ch, 1);//テキストを表示
		EndPaint(hwnd, &ps);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

//ウィンドウを作成する
bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;
	HWND hwnd;
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
	hwnd = CreateWindow(
		CLASS_NAME,//ウィンドウクラスの名前
		APP_TITLE,//タイトルバーのテキスト
		WS_OVERLAPPEDWINDOW,//ウィンドウのスタイル
		CW_USEDEFAULT,//ウインドウの水平位置のデフォルト
		CW_USEDEFAULT,//Wウインドウの垂直位置のデフォルト
		WINDOW_WIDTH,//ウィンドウの幅
		WINDOW_HEIGHT,// ウィンドウの高さ
		(HWND)NULL,// 親ウィンドウなし
		(HMENU)NULL,// メニューなし
		hInstance,// アプリケーションインスタンスへのハンドル
		(LPVOID)NULL// ウィンドウパラメータなし
	);
	if (!hwnd)//ウィンドウ作成失敗時
		return false;
	//ウィンドウ表示
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	return true;
}
