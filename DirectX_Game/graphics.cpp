#include "graphics.h"

//Graphics�R���X�g���N�^


Graphics::Graphics()
{
	direct3d = NULL;
	device3d = NULL;
	fullscreen = false;
	width = GAME_WIDTH;
	height = GAME_HEIGHT;
}

Graphics::~Graphics()
{
	releaseAll();
}

void Graphics::releaseAll()
{
	SAFE_RELEASE(device3d);
	SAFE_RELEASE(direct3d);
}
//Directx �O���t�B�b�N�X�̏�����
void Graphics::initialize(HWND hw, int w, int h, bool full)
{
	hwnd = hw;
	width = w;
	height = h;
	fullscreen = full;
	//Direct3D��������
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL)//���������s���ɃG���[��Ԃ�
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Direct3D"));

	initD3Dpp(); //	�v���[���e�[�V�����p�����[�^�̏�����

	if (fullscreen) {
		if (isAdapterCompatible())
			d3dpp.FullScreen_RefreshRateInHz = pMode.RefreshRate;//�K���������t���b�V�����[�g�ɍ��킹��
		else
			throw(GameError(gameErrorNS::FATAL_ERROR, "The graphics device does not support the specified resolution and/or format."));
	}

	D3DCAPS9 caps;//�O���t�B�b�N�{�[�h��D3DCREATE_HARDWARE_VERTEXPROCESSING�ɑΉ����Ă��邩���ׂ�
	DWORD behavior;
	result = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	//�O���t�B�b�N�{�[�h��1.1 vertex sharders�ɑΉ����Ă��Ȃ��Ƃ��̓\�t�g�E�F�A���ŏ�������B
	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
	{
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;  // �\�t�g�E�F�A�ŏ���
	}
	else
	{
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;  // �n�[�h�E�F�A�ŏ���
	}


	result = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		behavior,
		&d3dpp,
		&device3d
	);

	if (FAILED(result))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D device"));
}
//�v���[���e�[�V�����p�����[�^�̏�����������
void Graphics::initD3Dpp() 
{
	try {
		ZeroMemory(&d3dpp, sizeof(d3dpp));//d3dpp�\���̂Ƀ[������������
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		if (fullscreen) {
			d3dpp.BackBufferWidth = GAME_FULLWIDTH;
			d3dpp.BackBufferHeight = GAME_FULLHEIGHT;
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;//24bit�J���[
		}
		else {
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//�f�X�N�g�b�v�ݒ�Ɉˑ�
		}
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//�f�o�C�X���Ńo�b�t�@�̐؂�ւ��ɍœK�ȕ���I�΂���
		d3dpp.hDeviceWindow = hwnd;
		d3dpp.Windowed = (!fullscreen);
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//��ʂ̍X�V�Ԋu
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR,
			"Error initializing D3D presentation parameters"));
	}
}


HRESULT Graphics::getDeviceState()
{
	result = E_FAIL;
	if (device3d == NULL)
		return result;
	result = device3d->TestCooperativeLevel();
	return result;
}

HRESULT Graphics::reset()
{
	result = E_FAIL;
	initD3Dpp();
	result = device3d->Reset(&d3dpp);
	return result;
}

HRESULT Graphics::beginScene()
{
	result = E_FAIL;//�����l�͎��s�ɂ��Ă���
	if (device3d == NULL)
		return result;
	//�o�b�N�o�b�t�@��backcolor�ŃN���A�ɂ���
	device3d->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0F, 0);
	device3d->BeginScene();
	return result;
}

HRESULT Graphics::endScene()
{
	result = E_FAIL;
	if (device3d)
		result = device3d->EndScene();
	return result;
}

bool Graphics::isAdapterCompatible()
{
	UINT modes = direct3d->GetAdapterModeCount(D3DADAPTER_DEFAULT,
		d3dpp.BackBufferFormat);
	for (UINT i = 0; i < modes; i++)
	{
		result = direct3d->EnumAdapterModes(D3DADAPTER_DEFAULT,
			d3dpp.BackBufferFormat,
			i, &pMode);
		if (pMode.Height == d3dpp.BackBufferHeight &&
			pMode.Width == d3dpp.BackBufferWidth &&
			pMode.RefreshRate >= d3dpp.FullScreen_RefreshRateInHz)
			return true;
	}
	return false;
}
