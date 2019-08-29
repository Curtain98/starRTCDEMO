#include "stdafx.h"
#include "CPlusThread.h"


void CPlusThread::run(CallBackFun fun,INT32 code,char* message)
{
	callBack_ = fun;
	Code = code;
	Msg = message;
	thread_ = std::thread(&CPlusThread::WorkFun, this);
}

void CPlusThread::WorkFun()
{
		if (callBack_)
		{
			MessageEntity msg;
			msg.Code = Code;
			strcpy_s(msg.note, Msg);
			memcpy_s(data_, 8, (void*)&msg.Code, 8);
			memcpy_s(data_ + 8, 100, (void*)msg.note, 100);
			callBack_(data_, 108);
		}
}