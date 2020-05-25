#include "Game.h"

Game::Game()
{
	input = new input();
	paused = false;
	graphics = NULL;
	initialized = false;
}

Game::~Game()
{
	deleteAll();
	ShowCursor(true);
}

LRESULT Game::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(initialized)
	{
		switch (msg)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			case WM_KEYDOWN: case WM_SYSKEYDOWN://�L�[�������ꂽ
				input->keyDown(wParam);
				return 0;
			case WM_KEYUP: case WM_SYSKEYUP: //�L�[�������ꂽ
				input->keyUp(wParam);
				return 0;
			case WM_CHAR: //���������͂��ꂽ
				input->keyIn(wParam);
				return 0;
			case WM_MOUSEMOVE: //�}�E�X���ړ����ꂽ
				input->mouseIn(lParam);
				return 0;
			case WM_INPUT: //�}�E�X����̃��[�f�[�^����
				input->mouseRawIn(lParam);
				return 0;
			case WM_LBUTTONDOWN:
				input->setMouseLButton(true);
				input->mouseIn(lParam);
				return 0;
			case WM_LBUTTONUP:
				input->setMouseLButton(false);
				input->mouseIn(lParam);
				return 0;
			case WM_RBUTTONDOWN:
				input->setMouseRButton(true);
				input->mouseIn(lParam);
				return 0;
			case WM_RBUTTONUP:
				input->setMouseRButton(false);
				input->mouseIn(lParam);
				return 0;
			case WM_MBUTTONDOWN:
				input->setMouseMButton(true);
				input->mouseIn(lParam);
				return 0;
			case WM_MBUTTONUP:
				input->setMouseMButton(false);
				input->mouseIn(lParam);
				return 0;
			case WM_XBUTTONDOWN: case WM_XBUTTONUP:
				input->setMouseXButton(wParam);
				input->mouseIn(lParam);
			case WM_DEVICECHANGE:
				input->checkControllers();
				return 0;
		}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


void Game::initialize(HWND hw)
{
	hwnd = hw;
	graphics = new Graphics();
	input->initialize(hwnd, false);
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "�^�C�}�[���������s"));
	QueryPerformanceCounter(&timeStart);
	initialized = true;
}

void Game::handleLostGraphicsDevice() {
	hr = graphics->getDeviceState();

	if (FAILED(hr))
	{

		if (FAILED(hr))
		{
			if (hr == D3DERR_DEVICELOST)
			{
				Sleep(100);
				return;
			}

			else if (hr == D3DERR_DEVICENOTRESET)
			{
				releaseAll();
				hr = graphics->reset();
				if (FAILED(hr))
					return;
				resetAll();
			}
			else
				return;
		}
	}
}