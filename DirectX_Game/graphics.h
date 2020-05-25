#ifndef _GRAPHICS_H //多重定義の防止
#define _GRAPHICS_H 
#define WIN32_LEAN_AND_MEAM
#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include "constants.h"
#include "gameError.h"
//Direct X　ポインタ
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D LPDIRECT3D9

#define COLOR_ARGB DWORD //色定義
#define SETCOLOR_ARGB(a,r,g,b) \
((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<8)|(((g)&0xff)<<8)|((b)&0xff)))
class Graphics
{
private:
	//Direcx API
	LP_3D direct3d;
	LP_3DDEVICE device3d;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;
	D3DCOLOR backColor;
	//変数

	HRESULT result;
	HWND hwnd;
	bool fullscreen;
	int width;
	int height;
	//エンジン使用時に内部的に使用
	//D3Dプレゼンテーションパラメータを初期化
	void initD3Dpp();
public:
	//コンストラクタ
	Graphics();
	//デストラクタ
	virtual ~Graphics();
	//direct3dとdevice3dの解放
	void releaseAll();
	//DirectXグラフィックスを初期化
	void initialize(HWND hw, int width, int height, bool fullscreen);
	HRESULT getDeviceState();
	HRESULT reset();
	HRESULT beginScene();
	HRESULT endScene();
	//オフスクリーンバックバッファを画面に表示
	HRESULT showBackbuffer();
	//アダプターがバックバッファに適合しているかをチェックする。
	bool isAdapterCompatible();
};
#endif // !_GRAPHICS_H
#pragma once
