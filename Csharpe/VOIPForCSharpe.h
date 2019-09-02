#pragma once
#pragma once
#include<string>
#include "BackMsgEntity.h"

using namespace std;
extern "C" {

	//初始化回调C#信息
	__declspec(dllexport) extern BOOL InitBackMsg(CallBackFun pFun);
	//登录
	__declspec(dllexport) extern BOOL YPLogin(char* localuserid);
	//呼叫
	__declspec(dllexport) extern int VoipCallPerson(char* targetId, char* str);
	//释放
	__declspec(dllexport) extern int DeleteVoip();
	//IP呼叫
	__declspec(dllexport) extern void IPCall(char* AdmIP);
	//IP呼叫初始化
	__declspec(dllexport) extern BOOL InitIP(char* LocaIP);
	//挂断
	__declspec(dllexport) extern void stopLive();
	//测试回调信息
	__declspec(dllexport) extern void BackMsg();
<<<<<<< HEAD
	//���Իص���Ϣ
=======
	//单独调用accept
>>>>>>> origin/master
	__declspec(dllexport) extern void accept(char* AdmIP);
}
