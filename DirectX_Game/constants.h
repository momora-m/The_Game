#pragma once

#ifndef _CONSTANTS_H
#define _CONSTANTS_H
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//ポインタdeleteのためのマクロ定義
#define SAFE_DELETE(ptr) {if(ptr){delete(ptr); (ptr)=NULL;} }
//ポインタreleaseのためのマクロ定義
#define SAFE_RELEASE(ptr) { if(ptr) { (ptr)->Release(); (ptr)=NULL; }}
//配列ポインタdeleteのためのマクロ定義
#define SAFE_DELETE_ARRAY(ptr) { if(ptr){ delete [](ptr); (ptr)=NULL; } }


const char CLASS_NAME[] = "MyProtoTypeGame";
const char GAME_TITLE[] = "DirectX Device Capabilities";
const bool FULLSCREEN = false;

//この値は開発環境テスト以外では実際に使用しないで初期化すること
const UINT GAME_WIDTH = 600;
const UINT GAME_HEIGHT = 200;
const UINT GAME_FULLWIDTH = 1920;
const UINT GAME_FULLHEIGHT = 1080;
//キーマッピング
const byte ESC_KEY = VK_ESCAPE;

#endif