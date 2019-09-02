// TPVOIP_P2P.cpp: ʵ���ļ�
//

#include "stdafx.h"
#include "starrtcdemo.h"
#include "TPVOIP_P2P.h"
#include "afxdialogex.h"
#include "CUtil.h"
#include <Winsock2.h>
#include<ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib ")  //linking to the library
// TPVOIP_P2P �Ի���


TPVOIP_P2P::TPVOIP_P2P(CUserManager* pUserManager, char* LocaIP)
{
	m_strAimIP = "";
	m_strLocalIP = LocaIP;
	m_pUserManager = pUserManager;
	m_pVoipManager = new XHVoipP2PManager(this);
	m_pVoipManager->setUserId(m_strLocalIP);
	m_bConnect = false;
	m_pSoundManager = new CSoundManager(this);

	if (m_ShowLiveDlg == NULL) {
		m_ShowLiveDlg = new CShowLiveDlg();
		m_ShowLiveDlg->addPictureControlListener(this);
		m_ShowLiveDlg->addShowLiveListener(this);
		m_ShowLiveDlg->Create(IDD_DIALOG_SHOW_LIVE, AfxGetMainWnd());
		//m_ShowLiveDlg->Create(IDD_DIALOG_SHOW_LIVE, this);
	}
}

int acceptNumber = 0;
void TPVOIP_P2P::IPCall(char* AdmIP)
{
	acceptNumber = 0;
	RunMsg(1, "���ں���");
	m_strAimIP = AdmIP;

	//���жԷ�
	if (m_pVoipManager != NULL)
	{
		m_pVoipManager->call(m_strAimIP);
	}

	m_ShowLiveDlg->MoveWindow(CRect(100, 100, 400, 400), true);
	m_ShowLiveDlg->ShowWindow(SW_SHOW);

	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		m_ShowLiveDlg->m_pDataShowView->addUser(m_strAimIP, true);
		m_ShowLiveDlg->m_pDataShowView->addUser(m_pUserManager->m_ServiceParam.m_strUserId, true);
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}

	startGetData((CROP_TYPE)m_pUserManager->m_ServiceParam.m_CropType, false);

	//���ò�������
	m_bInsertData = true;
	if (m_pSoundManager != NULL)
	{
		m_pSoundManager->startSoundData(true);
	}
	m_bConnect = true;

}

void TPVOIP_P2P::IPaccept(char* AdmIP)
{
	//�����ʾ�Է�����
	
		RunMsg(1, "����accept");
		m_pVoipManager->accept(m_strAimIP);
}

TPVOIP_P2P::~TPVOIP_P2P()
{
}

void TPVOIP_P2P::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_LOCAL_IP, m_LocalIP);
	DDX_Control(pDX, IDC_IPADDRESS_AIM_IP, m_AimIP);
}


BEGIN_MESSAGE_MAP(TPVOIP_P2P, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CALLING, &TPVOIP_P2P::OnBnClickedButtonCalling)
END_MESSAGE_MAP()


// TPVOIP_P2P ��Ϣ�������


void TPVOIP_P2P::OnBnClickedButtonCalling()
{
	BYTE nf1, nf2, nf3, nf4;
	m_AimIP.GetAddress(nf1, nf2, nf3, nf4);
	if (nf4 == 0)
	{
		AfxMessageBox("��ȷ�϶Է�IP");
		return;
	}
	CString str;
	str.Format("%d.%d.%d.%d", nf1, nf2, nf3, nf4);//�����nf�õ���ֵ��IPֵ��. 
	m_strAimIP = str.GetBuffer(0);

	//���жԷ�
	if (m_pVoipManager != NULL)
	{
		m_pVoipManager->call(m_strAimIP);
		//m_pVoipManager->accept(m_strAimIP);
	}

	CRect rect;
	::GetWindowRect(this->m_hWnd, rect);
	m_ShowLiveDlg->MoveWindow(CRect(rect.left - 100, rect.top - 200, rect.right + 100, rect.bottom + 200), true);
	m_ShowLiveDlg->ShowWindow(SW_SHOW);

	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		m_ShowLiveDlg->m_pDataShowView->addUser(m_pUserManager->m_ServiceParam.m_strUserId, true);
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}

	startGetData((CROP_TYPE)m_pUserManager->m_ServiceParam.m_CropType, false);
}


BOOL TPVOIP_P2P::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ShowLiveDlg->Create(IDD_DIALOG_SHOW_LIVE, this);
	WSADATA wsaData = { 0 };
	if (WSAStartup(MAKEWORD(2, 1), &wsaData) == 0)
	{
		char szHostName[MAX_PATH] = { 0 };
		int nRetCode;
		nRetCode = gethostname(szHostName, sizeof(szHostName));
		PHOSTENT hostinfo;
		if (nRetCode == 0)
		{
			hostinfo = gethostbyname(szHostName);
			m_strLocalIP = inet_ntoa(*(struct in_addr*)*hostinfo->h_addr_list);
		}
		WSACleanup();
	}


	m_pVoipManager->setUserId(m_strLocalIP);

	//m_strLocalIP = CUtil::GetLocalIpAddress();
	int pos = m_strLocalIP.find(".");
	string strVal1 = m_strLocalIP.substr(0, pos);
	m_strLocalIP = m_strLocalIP.substr(pos + 1, m_strLocalIP.length() - pos - 1);
	pos = m_strLocalIP.find(".");
	string strVal2 = m_strLocalIP.substr(0, pos);
	m_strLocalIP = m_strLocalIP.substr(pos + 1, m_strLocalIP.length() - pos - 1);
	pos = m_strLocalIP.find(".");
	string strVal3 = m_strLocalIP.substr(0, pos);
	m_strLocalIP = m_strLocalIP.substr(pos + 1, m_strLocalIP.length() - pos - 1);
	string strVal4 = m_strLocalIP;

	int val1 = atoi(strVal1.c_str());
	int val2 = atoi(strVal2.c_str());
	int val3 = atoi(strVal3.c_str());
	int val4 = atoi(strVal4.c_str());
	m_LocalIP.SetAddress(val1, val2, val3, val4);
	m_AimIP.SetAddress(val1, val2, val3, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


// voip callback
/**
 * ���з���Ӧ
 * ���з��յ����з��ĺ���
 * @param fromID
 */
void TPVOIP_P2P::onCalling(string fromID)
{
	CString str;
	str.Format("�Ƿ�ͬ���û�:%s������Ƶͨ��", fromID.c_str());
	if (IDYES == AfxMessageBox(str, MB_YESNO))
	{
		m_strAimIP = fromID;
		CRect rect;
		::GetWindowRect(this->m_hWnd, rect);
		m_ShowLiveDlg->MoveWindow(CRect(100,100,400,400), true);
		m_ShowLiveDlg->ShowWindow(SW_SHOW);
		m_bConnect = true;

		RunMsg(1, "�յ����� ��ͬ�� ���ڽ�������");
		m_pVoipManager->accept(m_strAimIP);

		if (m_ShowLiveDlg->m_pDataShowView != NULL)
		{
			m_ShowLiveDlg->m_pDataShowView->addUser(m_pUserManager->m_ServiceParam.m_strUserId, false);
			m_ShowLiveDlg->m_pDataShowView->addUser(m_strAimIP, true);
			m_ShowLiveDlg->m_pDataShowView->setShowPictures();
		}

		startGetData((CROP_TYPE)m_pUserManager->m_ServiceParam.m_CropType, true);
		if (m_pSoundManager != NULL)
		{
			m_pSoundManager->startSoundData(true);
		}
	}
	else
	{
		m_pVoipManager->refuse();
	}
}

/**
 * ���з���Ӧ
 * ���з��ڱ��з�����֮ǰ�Ҷϣ�ͨ����ȡ����
 * @param fromID
 */
void TPVOIP_P2P::onCancled(string fromID)
{
	AfxMessageBox("���з��ڱ��з�����֮ǰ�Ҷϣ�ͨ����ȡ����");
	stopGetData();
	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		m_ShowLiveDlg->m_pDataShowView->removeAllUser();
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
	m_ShowLiveDlg->ShowWindow(SW_HIDE);
}

/**
 * ���з���Ӧ
 * ���з��ܾ���ͨ��ͨ�����ܾ���
 * @param fromID
 */
void TPVOIP_P2P::onRefused(string fromID)
{
	stopGetData();
	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		m_ShowLiveDlg->m_pDataShowView->removeAllUser();
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
	m_ShowLiveDlg->ShowWindow(SW_HIDE);
	AfxMessageBox("�Է��ܾ���ͨ");

	m_bConnect = false;
	m_pSoundManager = new CSoundManager(this);
	m_pVoipManager = new XHVoipP2PManager(this);
	m_pVoipManager->setUserId(m_strLocalIP);
}

/**
 * ���з���Ӧ
 * ���з���·æ���Է�ͨ���У�
 * @param fromID
 */
void TPVOIP_P2P::onBusy(string fromID)
{
	//�ر�
	stopGetData();
	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		m_ShowLiveDlg->m_pDataShowView->removeAllUser();
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
	m_ShowLiveDlg->ShowWindow(SW_HIDE);
	AfxMessageBox("�Է���·æ");
}

/**
 * ���з���Ӧ
 * ���з���ͨ��ͨ����ʼ��
 * @param fromID
 */
void TPVOIP_P2P::onConnected(string fromID)
{
	
	if (acceptNumber == 0)
	{
		m_pVoipManager->accept(m_strAimIP);
		acceptNumber++;
		RunMsg(2, "�Է�ͬ��ͨ�� ���������");
	}
	////�����ʾ�Է�����
	//if (m_ShowLiveDlg->m_pDataShowView != NULL)
	//{
	//	m_strAimIP = fromID;
	//	m_ShowLiveDlg->m_pDataShowView->addUser(m_strAimIP, true);
	//	m_ShowLiveDlg->m_pDataShowView->changeShowStyle(m_pUserManager->m_ServiceParam.m_strUserId, false);
	//	m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	//}
	////���ò�������
	//m_bInsertData = true;
	//if (m_pSoundManager != NULL)
	//{
	//	m_pSoundManager->startSoundData(true);
	//}
	//m_bConnect = true;
}

/**
 * �Է��Ѿ��Ҷ�
 * @param fromID
 */
void TPVOIP_P2P::onHangup(string fromID)
{
	stopGetData();
	if (m_pSoundManager != NULL)
	{
		m_pSoundManager->stopSoundData();
	}

	if (m_pVoipManager != NULL)
	{
		if (m_bConnect)
		{
			m_pVoipManager->hangup();
		}
		else
		{
			m_pVoipManager->cancel();
		}
		m_bConnect = false;
	}
	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		m_ShowLiveDlg->m_pDataShowView->removeAllUser();
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
	m_ShowLiveDlg->ShowWindow(SW_HIDE);
}

/**
 * voip����
 * @param errorCode
 */
void TPVOIP_P2P::onError(string errorCode)
{
	//�����Լ�
	stopGetData();
	if (m_pSoundManager != NULL)
	{
		m_pSoundManager->stopSoundData();
	}
	if (m_pVoipManager != NULL)
	{
		m_pVoipManager->hangup();
	}
	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		m_ShowLiveDlg->m_pDataShowView->removeAllUser();
	}
	m_ShowLiveDlg->ShowWindow(SW_HIDE);
	//�Ͽ�����
	CString strErr;
	strErr.Format("err:%s", errorCode.c_str());
	AfxMessageBox(strErr);

}

/**
 * �յ�ʵʱ����
 * @param data
 */
void TPVOIP_P2P::onReceiveRealtimeData(uint8_t* data, int length)
{

}

int TPVOIP_P2P::getVideoRaw(string strUserId, int w, int h, uint8_t* videoData, int videoDataLen)
{
	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		m_ShowLiveDlg->m_pDataShowView->drawPic(FMT_YUV420P, m_strAimIP, w, h, videoData, videoDataLen);
	}
	return 0;
}

void TPVOIP_P2P::changeShowStyle(string strUserId)
{
	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		string strId = m_ShowLiveDlg->m_pDataShowView->changeShowStyle(strUserId, true);
		m_ShowLiveDlg->m_pDataShowView->changeShowStyle(strId, false);
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
}

void TPVOIP_P2P::closeCurrentLive()
{
}

void TPVOIP_P2P::stopLive()
{
	stopGetData();
	if (m_pSoundManager != NULL)
	{
		m_pSoundManager->stopSoundData();
	}

	if (m_pVoipManager != NULL)
	{
		if (m_bConnect)
		{
			m_pVoipManager->hangup();
		}
		else
		{
			m_pVoipManager->cancel();
		}
		m_bConnect = false;
	}
	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		m_ShowLiveDlg->m_pDataShowView->removeAllUser();
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
	m_ShowLiveDlg->ShowWindow(SW_HIDE);
}

void TPVOIP_P2P::getLocalSoundData(char* pData, int nLength)
{
	if (m_pVoipManager != NULL)
	{
		m_pVoipManager->insertAudioRaw((uint8_t*)pData, nLength);
	}
}

void TPVOIP_P2P::querySoundData(char** pData, int* nLength)
{
	if (m_pVoipManager != NULL)
	{
		m_pVoipManager->querySoundData((uint8_t**)pData, nLength);
	}
}

void TPVOIP_P2P::addUpId()
{
	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		m_ShowLiveDlg->m_pDataShowView->addUser(m_pUserManager->m_ServiceParam.m_strUserId, false);
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
}

void TPVOIP_P2P::insertVideoRaw(uint8_t* videoData, int dataLen, int isBig)
{
	if (m_pVoipManager != NULL)
	{
		m_pVoipManager->insertVideoRaw(videoData, dataLen, isBig);
	}
}

int TPVOIP_P2P::cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall)
{
	int ret = 0;
	if (m_pVoipManager != NULL)
	{
		ret = m_pVoipManager->cropVideoRawNV12(w, h, videoData, dataLen, (int)CROP_TYPE::VIDEO_CROP_CONFIG_480BW_480BH_SMALL_NONE, 0, 0, outVideoDataBig, outVideoDataSmall);
	}
	return ret;
}

void TPVOIP_P2P::drawPic(YUV_TYPE type, int w, int h, uint8_t* videoData, int videoDataLen)
{
	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		m_ShowLiveDlg->m_pDataShowView->drawPic(type, m_pUserManager->m_ServiceParam.m_strUserId, w, h, videoData, videoDataLen);
	}
}
