#pragma once

#ifndef _CONSTANTS_H
#define _CONSTANTS_H
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//�|�C���^delete�̂��߂̃}�N����`
#define SAFE_DELETE(ptr) {if(ptr){delete(ptr); (ptr)=NULL;} }
//�|�C���^release�̂��߂̃}�N����`
#define SAFE_RELEASE(ptr) { if(ptr) { (ptr)->Release(); (ptr)=NULL; }}
//�z��|�C���^delete�̂��߂̃}�N����`
#define SAFE_DELETE_ARRAY(ptr) { if(ptr){ delete [](ptr); (ptr)=NULL; } }


const char CLASS_NAME[] = "MyProtoTypeGame";
const char GAME_TITLE[] = "DirectX Device Capabilities";
const bool FULLSCREEN = false;

//���̒l�͊J�����e�X�g�ȊO�ł͎��ۂɎg�p���Ȃ��ŏ��������邱��
const UINT GAME_WIDTH = 600;
const UINT GAME_HEIGHT = 200;
const UINT GAME_FULLWIDTH = 1920;
const UINT GAME_FULLHEIGHT = 1080;
//�L�[�}�b�s���O
const byte ESC_KEY = VK_ESCAPE;

#endif