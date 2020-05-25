#pragma once
#ifndef _GAMEERROR_H
#define _GAMEERROR_H

#include <string>
#include <exception>


namespace gameErrorNS
{
	//�G���[�R�[�h
	//�Q�[���I�����K�v�ȃG���[��-1,�K�v�łȂ��x����1
	const int FATAL_ERROR = -1;
	const int WARNING = 1;
}

//�G���[�𓊂���Game Error �N���X
class GameError : public std::exception
{
private:
	int errorCode;
	std::string message;
public:
	//�f�t�H���g�̃R���X�g���N�^
	GameError() throw() :errorCode(gameErrorNS::FATAL_ERROR), message("Undefined Error in game."){}
	//�R�s�[���ꂽ�R���X�g���N�^
	GameError(const GameError& e) throw(): std::exception(e), errorCode(e.errorCode), message(e.message) {}
	//���������R���X�g���N�^
	GameError(int code, const std::string &s) throw() :errorCode(code), message(s) {}
	//�I�y���[�^�[ ->�Ŏ����̒l���Q�Ƃ��邽�� 
	GameError& operator= (const GameError& rhs) throw()
	{
		std::exception::operator=(rhs);
		this->errorCode = rhs.errorCode;
		this->message = rhs.message;
	}

	virtual ~GameError() throw(){};
	//what���I�[�o�[���C�h����
	virtual const char* what() const throw() { return this->getMessage(); }

	const char* getMessage() const throw() { return message.c_str(); }
	int getErrorCode() const throw() { return errorCode; }
};

#endif // !_GAMEERROR_H