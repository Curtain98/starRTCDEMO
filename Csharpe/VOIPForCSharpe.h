#pragma once
#pragma once
#include<string>
#include "BackMsgEntity.h"

using namespace std;
extern "C" {

	//��ʼ���ص�C#��Ϣ
	__declspec(dllexport) extern BOOL InitBackMsg(CallBackFun pFun);
	//��¼
	__declspec(dllexport) extern BOOL YPLogin(char* localuserid);
	//����
	__declspec(dllexport) extern int VoipCallPerson(char* targetId, char* str);
	//�ͷ�
	__declspec(dllexport) extern int DeleteVoip();
	//IP����
	__declspec(dllexport) extern void IPCall(char* AdmIP);
	//IP���г�ʼ��
	__declspec(dllexport) extern BOOL InitIP(char* LocaIP);
	//�Ҷ�
	__declspec(dllexport) extern void stopLive();
	//���Իص���Ϣ
	__declspec(dllexport) extern void BackMsg();
	//���Իص���Ϣ
	__declspec(dllexport) extern void accept(char* AdmIP);
}
