#include "stdafx.h"
#include "VOIPForCSharpe.h"
#include "CStarRTCMenuDialog.h"
#include "CUserManager.h"
#include "CLogin.h"
#include "CVoipDlg.h"
#include "Resource.h"
#include "YpVoip.h"
#include "TPVOIP_P2P.h"


CUserManager* m_pUserManager;
YpVoip *ypip;
TPVOIP_P2P* P2P;


BOOL InitBackMsg(CallBackFun pFun)
{
		InitBack(pFun);
			RunMsg(0, "��ʼ���ص���Ϣ�ɹ���");
		return TRUE;
}

void BackMsg() 
{
	RunMsg(0, "����-�ص���Ϣ��");
}

BOOL InitIP(char* LocaIP)
{
	if (m_pUserManager != NULL)
	{
		P2P = new TPVOIP_P2P(m_pUserManager, LocaIP);
		return true;
	}
	return false;
}
void stopLive()
{
	P2P->stopLive();
}
void IPCall(char* AdmIP)
{
	P2P->IPCall(AdmIP);
}
void accept(char* AdmIP)
{
	P2P->IPaccept(AdmIP);
}


BOOL YPLogin(char* localuserid) {
	m_pUserManager = new CUserManager();
	CLogin login(m_pUserManager);
	//bool bRead = login.readConfig();��
	//if (!bRead)fdf 
	//{
	//	//OnClose();
	//	return FALSE;
	//}
	m_pUserManager->m_ServiceParam.m_strUserId = localuserid;
	if (ypip == NULL) {
		ypip = new YpVoip(m_pUserManager);
	}
	bool bSuccess = login.logIn();
	if (bSuccess)
	{
		//AfxMessageBox("��¼�ɹ�");
		//login.startIMServer((char*)m_pUserManager->m_strIMServerIp.c_str(), m_pUserManager->m_nIMServerPort, (char*)m_pUserManager->m_ServiceParam.m_strUserId.c_str(), (char*)m_pUserManager->m_ServiceParam.m_strAgentId.c_str(), (char*)m_pUserManager->m_strTokenId.c_str());
	}
	else
	{
		AfxMessageBox("��¼ʧ�ܣ�����������Ϣ");
	}
	return TRUE;
}

int VoipCallPerson(char* targetId, char* str) {
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (ypip == NULL) {
		ypip = new YpVoip(m_pUserManager);
	}
	string string_targetId;
	string_targetId = targetId;
	ypip->callPerson(string_targetId);
	return 1;
}

int DeleteVoip() {
	if (ypip != NULL) {
		delete ypip;
		ypip = NULL;
	}
	return 1;
}
