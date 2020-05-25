#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "graphics.h"
#include "Game.h""
//�v���g�^�C�v�錾
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool AnotherInstance();
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hinst; //�O���[�o���ϐ�
HDC hdc;//�f�o�C�X�R���e�L�X�g�ւ̃n���h��
TCHAR ch = ' ';
RECT rect;
PAINTSTRUCT ps; //�E�B���h�E�`��̂��߂̏��������Ă���\����
bool vkKeys[256]; //�L�[���͊i�[�p�̉��z�L�[�̔z��
Graphics *graphics;//Graphic�|�C���^
Game *game;//Game�|�C���^

//�A�v���P�[�V�����̃G���g���[�|�C���g�̍쐬

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	#if defined(DEBUG) || defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//���������[�N�̌��o
	#endif
	MSG msg;
	HWND hwnd = NULL;
	//�E�B���h�E�̍쐬
	if (!CreateMainWindow(hwnd, hInstance, nCmdShow))
		return 1;


	for (int i = 0; i < 256; i++)//���z�L�[�z��̏�����
		vkKeys[i] = false;
	try {
		graphics = new Graphics;
		//graphics ������
		graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);
		int done = 0;
		while (!done)
		{
			//���b�Z�[�W���󂯎��
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) //�I�����b�Z�[�W�����m������
					done = 1;

				TranslateMessage(&msg);
				DispatchMessage(&msg);//���b�Z�[�W���f�R�[�h���ēn��
			}
			else
			{
				graphics->showBackbuffer();
			}
		}
		SAFE_DELETE(graphics);//�Q�[���I�����Ƀ��������
		return msg.wParam;
	}
	catch(const GameError &err)//�Q�Ɠn���ɂ��邱�Ƃŏ��̃X���C�X�Ɣj�����ꂽ�����l�̃I�u�W�F�N�g�� catch ���邱�Ƃ�h��
	{
		MessageBox(NULL, err.getMessage(), "Error", MB_OK);
	}
	catch (...)
	{
		MessageBox(NULL, "Unknown error occured in game", "Error", MB_OK);
	}
	SAFE_DELETE(graphics);//�Q�[���I�����Ƀ��������
	return 0;
}


bool AnotherInstance()//��d�N���ɂ�镡���C���X�^���X�̎��s��h��
{
	HANDLE ourMutex;

	ourMutex = CreateMutex(NULL, true, "Use_a_different_string_here_for_each_program");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return true;
	return false;

}

//�E�B���h�E�֐�
/*LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	short nVirtKey;//���z�L�[
	const short SHIFTED = (short)0x8000;
	TEXTMETRIC tm; //�����������\����
	DWORD chWidth = 20; //�\�����镶�����̕�
	DWORD chHeight = 20; //�\�����镶�����̍���

	switch (msg)
	{
		case WM_CREATE://�E�B���h�E�𐶐����ĕ�����\������

			hdc = GetDC(hWnd);//�E�B���h�E�̃f�o�C�X�R���e�L�X�g�̃n���h�����擾
			GetTextMetrics(hdc, &tm); //�o�b�t�@�Ƀt�H���g�̏����i�[����
			ReleaseDC(hWnd, hdc);//�f�o�C�X�R���e�L�X�g�̃n���h������@
			chWidth = tm.tmAveCharWidth;
			chHeight = tm.tmHeight;
			return 0;

		case WM_DESTROY://�I�����߂������Ƃ��E�B���h�E�����
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			vkKeys[wParam] = true;
			switch (wParam)
			{
				case VK_SHIFT://�V�t�g���͎�
					nVirtKey = GetKeyState(VK_LSHIFT);
					if(nVirtKey & SHIFTED)
						vkKeys[VK_LSHIFT] = true;//���V�t�g
					nVirtKey = GetKeyState(VK_RSHIFT);
					if(nVirtKey & SHIFTED)
						vkKeys[VK_RSHIFT] = true;//�E�V�t�g
					break;
				case VK_CONTROL:
					nVirtKey = GetKeyState(VK_LCONTROL);
					if(nVirtKey & SHIFTED)
						vkKeys[VK_LCONTROL] = true;//���R���g���[��
					nVirtKey = GetKeyState(VK_RCONTROL);
					if (nVirtKey & SHIFTED)
						vkKeys[VK_CONTROL] = true;//�E�R���g���[��
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
						vkKeys[VK_LSHIFT] = false;//���V�t�g
					nVirtKey = GetKeyState(VK_RSHIFT);
					if ((nVirtKey & SHIFTED) == 0)
						vkKeys[VK_RSHIFT] = false;//�E�V�t�g
					break;
				case VK_CONTROL:
					nVirtKey = GetKeyState(VK_LCONTROL);
					if ((nVirtKey & SHIFTED) == 0)
						vkKeys[VK_LCONTROL] = false;//���R���g���[��
					nVirtKey = GetKeyState(VK_RCONTROL);
					if ((nVirtKey & SHIFTED) == 0)
						vkKeys[VK_RCONTROL] = false;//�E�R���g���[��	
					break;
			}
			InvalidateRect(hWnd, NULL, TRUE);//�����I�ɕ`��
			return 0;
			break;

		case WM_CHAR:
			switch (wParam)
			{
				case 0x08: //�o�b�N�X�y�[�X
				case 0x09: //�^�u
				case 0x0A: //���C���t�B�[�h
				case 0x0D: //�L�����b�W���^�[��
				case ESC_KEY: //�G�X�P�[�v
					PostQuitMessage(0);
					return 0;
			}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//�E�B���h�E���쐬����
bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;
	//�E�B���h�E�N���X�̍\���̂�ݒ肷��
	wcx.cbSize = sizeof(wcx); //�\���̂̃T�C�Y
	wcx.style = CS_HREDRAW | CS_VREDRAW; //�E�B���h�E�T�C�Y�ύX���ɍ\���̂̃T�C�Y�ύX
	wcx.lpfnWndProc = WinProc;//�E�B���h�E�v���V�[�W��(�C�x���g�n���h��)
	wcx.cbClsExtra = 0;//�g���������N���X
	wcx.cbWndExtra = 0;//�g���E�B���h�E������
	wcx.hInstance = hInstance; //�C���X�^���X���ʂ̂��߂̃n���h��
	wcx.hIcon = NULL; //�A�C�R��
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);//�J�[�\����`(���)
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//�w�i�u���V
	wcx.lpszMenuName = NULL; //���j���[���\�[�X�̖��O
	wcx.lpszClassName = CLASS_NAME; //�E�B���h�E�N���X�̖��O
	wcx.hIconSm = NULL; //�������A�C�R��

	//�E�B���h�E�N���X�̓o�^
	if (RegisterClassEx(&wcx) == 0)
		return false;

	//��ʃ��[�h�̐ݒ�
	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	hwnd = CreateWindow(
		CLASS_NAME,//�E�B���h�E�N���X�̖��O
		GAME_TITLE,//�^�C�g���o�[�̃e�L�X�g
		style,//�E�B���h�E�̃X�^�C��
		CW_USEDEFAULT,//�E�C���h�E�̐����ʒu�̃f�t�H���g
		CW_USEDEFAULT,//W�E�C���h�E�̐����ʒu�̃f�t�H���g
		GAME_WIDTH,//�E�B���h�E�̕�
		GAME_HEIGHT,// �E�B���h�E�̍���
		(HWND)NULL,// �e�E�B���h�E�Ȃ�
		(HMENU)NULL,// ���j���[�Ȃ�
		hInstance,// �A�v���P�[�V�����C���X�^���X�ւ̃n���h��
		(LPVOID)NULL// �E�B���h�E�p�����[�^�Ȃ�
	);
	if (!hwnd)//�E�B���h�E�쐬���s��
		return false;
	if (!FULLSCREEN) {
		//�N���C�A���g�̈�� GAME_WIDTH * GAME_HEIGHT�ƂȂ�悤�ɕύX
		RECT clientRect;
		//�E�B���h�E�̃N���C�A���g�̈�̃T�C�Y�擾
		GetClientRect(hwnd, &clientRect);
		MoveWindow(
			hwnd,
			0,//��
			0,//��
			GAME_WIDTH + (GAME_WIDTH - clientRect.right),//�E
			GAME_HEIGHT + (GAME_HEIGHT - clientRect.left),//��
			TRUE
		);

	}
	//�E�B���h�E�\��
	ShowWindow(hwnd, nCmdShow);

	UpdateWindow(hwnd);
	return true;
}*/

LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return (game->messageHandler(hwnd, msg, wParam, lParam));
}
