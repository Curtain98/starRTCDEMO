#pragma once
using namespace std;
extern "C" {

	//�������ݻص�����
	typedef int(*CallBackFun)(unsigned char* pData, int nLen);
	//�������ݵ�C#��
	void RunMsg(INT32 code, char* msg);
	//��ʼ������C#����
	void InitBack(CallBackFun pFun);
}

