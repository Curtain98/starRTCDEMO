#pragma once
#include <thread>
#include "BackMsgEntity.h"

class CPlusThread
{
	

	typedef struct MessageEntity
	{
		INT32 Code;
		char note[100];
	}MessageEntity;

	

public:
	void run(CallBackFun fun, INT32 code, char* msgage);
private:
	CallBackFun callBack_;
	void WorkFun();
	std::thread thread_;
	unsigned char data_[150];
	char* Msg;
	INT32 Code;
};
	

