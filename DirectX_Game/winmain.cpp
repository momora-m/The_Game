#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//�v���g�^�C�v�錾
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hinst; //�O���[�o���ϐ�
HDC hdc;
TCHAR ch = ' ';
RECT rect;
PAINTSTRUCT ps; //�E�B���h�E�`��̂��߂̏��������Ă���\����
const char CLASS_NAME[] = "WinMain";
const char APP_TITLE[] = "Hello Game";
//�E�B���h�E�T�C�Y�錾
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
//�A�v���P�[�V�����̃G���g���[�|�C���g�̍쐬
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	//�E�B���h�E�̍쐬
	if (!CreateMainWindow(hInstance, nCmdShow))
		return false;
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
	}
	return msg.wParam;
}
//�E�B���h�E�֐�
LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY://�I�����߂������Ƃ�
		PostQuitMessage(0);
		return 0;
	case WM_CHAR:
		switch (wParam)
		{
		case 0x08: //�o�b�N�X�y�[�X
		case 0x09: //�^�u
		case 0x0A: //���C���t�B�[�h
		case 0x0D: //�L�����b�W���^�[��
		case 0x1B: //�G�X�P�[�v
			MessageBeep((UINT)-1);//�\���ł��Ȃ������̓r�[�v����炷
			return 0;
		default:
			ch = (TCHAR)wParam;
			InvalidateRect(hwnd, NULL, TRUE);//��`�������`��
			return 0;
		}
	case WM_PAINT:
		//�f�o�C�X�R���e�L�X�g�ւ̃n���h�����擾	
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect); //�E�B���h�E�̋�`���擾
		TextOut(hdc, rect.right / 2, rect.bottom / 2, &ch, 1);//�e�L�X�g��\��
		EndPaint(hwnd, &ps);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

//�E�B���h�E���쐬����
bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;
	HWND hwnd;
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
	hwnd = CreateWindow(
		CLASS_NAME,//�E�B���h�E�N���X�̖��O
		APP_TITLE,//�^�C�g���o�[�̃e�L�X�g
		WS_OVERLAPPEDWINDOW,//�E�B���h�E�̃X�^�C��
		CW_USEDEFAULT,//�E�C���h�E�̐����ʒu�̃f�t�H���g
		CW_USEDEFAULT,//W�E�C���h�E�̐����ʒu�̃f�t�H���g
		WINDOW_WIDTH,//�E�B���h�E�̕�
		WINDOW_HEIGHT,// �E�B���h�E�̍���
		(HWND)NULL,// �e�E�B���h�E�Ȃ�
		(HMENU)NULL,// ���j���[�Ȃ�
		hInstance,// �A�v���P�[�V�����C���X�^���X�ւ̃n���h��
		(LPVOID)NULL// �E�B���h�E�p�����[�^�Ȃ�
	);
	if (!hwnd)//�E�B���h�E�쐬���s��
		return false;
	//�E�B���h�E�\��
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	return true;
}
