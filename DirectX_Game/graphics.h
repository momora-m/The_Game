#ifndef _GRAPHICS_H //���d��`�̖h�~
#define _GRAPHICS_H 
#define WIN32_LEAN_AND_MEAM
#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include "constants.h"
#include "gameError.h"
//Direct X�@�|�C���^
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D LPDIRECT3D9

#define COLOR_ARGB DWORD //�F��`
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
	//�ϐ�

	HRESULT result;
	HWND hwnd;
	bool fullscreen;
	int width;
	int height;
	//�G���W���g�p���ɓ����I�Ɏg�p
	//D3D�v���[���e�[�V�����p�����[�^��������
	void initD3Dpp();
public:
	//�R���X�g���N�^
	Graphics();
	//�f�X�g���N�^
	virtual ~Graphics();
	//direct3d��device3d�̉��
	void releaseAll();
	//DirectX�O���t�B�b�N�X��������
	void initialize(HWND hw, int width, int height, bool fullscreen);
	HRESULT getDeviceState();
	HRESULT reset();
	HRESULT beginScene();
	HRESULT endScene();
	//�I�t�X�N���[���o�b�N�o�b�t�@����ʂɕ\��
	HRESULT showBackbuffer();
	//�A�_�v�^�[���o�b�N�o�b�t�@�ɓK�����Ă��邩���`�F�b�N����B
	bool isAdapterCompatible();
};
#endif // !_GRAPHICS_H
#pragma once
