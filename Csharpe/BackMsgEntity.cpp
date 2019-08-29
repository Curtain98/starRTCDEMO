#include "stdafx.h"
#include "BackMsgEntity.h"
#include "CPlusThread.h"

CPlusThread* pAlarmSer;
//数据返回类
CallBackFun callBack_Data;

void RunMsg(INT32 code, char* msg)
{
	if (pAlarmSer != NULL)
	{
		pAlarmSer = NULL;
	}
	pAlarmSer = new CPlusThread;
	pAlarmSer->run(callBack_Data, code, msg);

}

void InitBack(CallBackFun pFun)
{
	callBack_Data = pFun;
}
