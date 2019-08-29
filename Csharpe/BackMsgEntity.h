#pragma once
using namespace std;
extern "C" {

	//报警数据回调函数
	typedef int(*CallBackFun)(unsigned char* pData, int nLen);
	//返回数据到C#中
	void RunMsg(INT32 code, char* msg);
	//初始化返回C#参数
	void InitBack(CallBackFun pFun);
}

