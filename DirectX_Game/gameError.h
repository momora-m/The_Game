#pragma once
#ifndef _GAMEERROR_H
#define _GAMEERROR_H

#include <string>
#include <exception>


namespace gameErrorNS
{
	//エラーコード
	//ゲーム終了が必要なエラーは-1,必要でない警告は1
	const int FATAL_ERROR = -1;
	const int WARNING = 1;
}

//エラーを投げるGame Error クラス
class GameError : public std::exception
{
private:
	int errorCode;
	std::string message;
public:
	//デフォルトのコンストラクタ
	GameError() throw() :errorCode(gameErrorNS::FATAL_ERROR), message("Undefined Error in game."){}
	//コピーされたコンストラクタ
	GameError(const GameError& e) throw(): std::exception(e), errorCode(e.errorCode), message(e.message) {}
	//引数を持つコンストラクタ
	GameError(int code, const std::string &s) throw() :errorCode(code), message(s) {}
	//オペレーター ->で自分の値を参照するため 
	GameError& operator= (const GameError& rhs) throw()
	{
		std::exception::operator=(rhs);
		this->errorCode = rhs.errorCode;
		this->message = rhs.message;
	}

	virtual ~GameError() throw(){};
	//whatをオーバーライドする
	virtual const char* what() const throw() { return this->getMessage(); }

	const char* getMessage() const throw() { return message.c_str(); }
	int getErrorCode() const throw() { return errorCode; }
};

#endif // !_GAMEERROR_H