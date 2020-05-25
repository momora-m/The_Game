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
	Graphics *graphics; //Graphics�ւ̃|�C���^
	Input *input; //input�|�C���^
	HWND hwnd;   //�E�B���h�E�n���h��
	HRESULT hr;
	LARGE_INTEGER timeStart; //�p�t�H�[�}���X�J�E���^�[�̊J�n�l
	LARGE_INTEGER timeEnd; //�p�t�H�[�}���X�J�E���^�[�̏I���l
	LARGE_INTEGER timerFreq; //�p�t�H�[�}���X�J�E���^�[�̕��ϒl
	float frameTime; //�Ō�̃t���[���ɂ�����������
	float fps; //�t���[�����[�g�\��
	DWORD sleepTime; //�t���[�����ŃX���[�v���鎞��
	bool paused; //�Q�[����~�̃t���O�Ǘ�
	bool initialized;
public:
	Game();//�R���X�g���N�^
	virtual ~Game();//�f�X�g���N�^

	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//���삷��Q�[�����ƂɕK�v�ȗv���͈Ⴄ�̂ŁAvirtual���g�p����
	virtual void initialize(HWND hwnd);
	//�O���t�B�b�N�f�o�C�X�������̃r�f�I�������̉��
	virtual void releaseAll();
	//�G���e�B�e�B�̃��Z�b�g
	virtual void resetAll();
	//�S���\�[�X�̃������̍폜
	virtual void deleteAll();
	//�Q�[���̃����_�����O
	virtual void renderGame();
	//���������O���t�B�b�N�f�o�C�X������
	virtual void handleLostGraphicsDevice();
	//Graphics�ւ̃|�C���^���擾
	Graphics* getGraphics() { return graphics; }
	//�Q�[�����I��
	void exitGame() { PostMessage(hwnd, WM_DESTROY, 0, 0);}

	//�p���p���z�N���X�̐錾

	virtual void update() = 0;
	virtual void collisions() = 0;
	virtual void render() = 0;

};

