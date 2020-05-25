#pragma once
#ifndef GAME_H
#define GAME_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Mmsystem.h>
#include "graphics.h"
#include "constants.h"
#include "gameError.h"
#endif // !GAME_H
class Game
{
protected:
	Graphics *graphics; //Graphicsへのポインタ
	Input *input; //inputポインタ
	HWND hwnd;   //ウィンドウハンドル
	HRESULT hr;
	LARGE_INTEGER timeStart; //パフォーマンスカウンターの開始値
	LARGE_INTEGER timeEnd; //パフォーマンスカウンターの終了値
	LARGE_INTEGER timerFreq; //パフォーマンスカウンターの平均値
	float frameTime; //最後のフレームにかかった時間
	float fps; //フレームレート表示
	DWORD sleepTime; //フレーム側でスリープする時間
	bool paused; //ゲーム停止のフラグ管理
	bool initialized;
public:
	Game();//コンストラクタ
	virtual ~Game();//デストラクタ

	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//製作するゲームごとに必要な要件は違うので、virtualを使用する
	virtual void initialize(HWND hwnd);
	//グラフィックデバイス消失時のビデオメモリの解放
	virtual void releaseAll();
	//エンティティのリセット
	virtual void resetAll();
	//全リソースのメモリの削除
	virtual void deleteAll();
	//ゲームのレンダリング
	virtual void renderGame();
	//消失したグラフィックデバイスを処理
	virtual void handleLostGraphicsDevice();
	//Graphicsへのポインタを取得
	Graphics* getGraphics() { return graphics; }
	//ゲームを終了
	void exitGame() { PostMessage(hwnd, WM_DESTROY, 0, 0);}

	//継承用仮想クラスの宣言

	virtual void update() = 0;
	virtual void collisions() = 0;
	virtual void render() = 0;

};

