// CVoipDlg.cpp: ʵ���ļ�
//

#include "stdafx.h"
#include "starrtcdemo.h"
#include "YpVoip.h"
#include "afxdialogex.h"
#include "CropType.h"
enum VOIP_LIST_REPORT_NAME
{
	VOIP_VIDEO_NAME = 0,
	VOIP_VIDEO_STATUS,
	VOIP_VIDEO_ID,
	VOIP_VIDEO_CREATER
};


YpVoip::YpVoip(CUserManager* pUserManager)
{
	m_pUserManager = pUserManager;
	m_pVoipManager = new XHVoipManager(this);
	if (m_ShowLiveDlg == NULL) {
		m_ShowLiveDlg = new CShowLiveDlg();
		m_ShowLiveDlg->addPictureControlListener(this);
		m_ShowLiveDlg->addShowLiveListener(this);
		m_ShowLiveDlg->Create(IDD_DIALOG_SHOW_LIVE, AfxGetMainWnd());
	}
	m_strTargetId = "";
	m_pSoundManager = new CSoundManager(this);
}

YpVoip::~YpVoip()
{
	if (m_pVoipManager != NULL)
	{
		delete m_pVoipManager;
		m_pVoipManager = NULL;
	}
	stopGetData();
	if (m_pSoundManager != NULL)
	{
		delete m_pSoundManager;
		m_pSoundManager = NULL;
	}
	if (m_ShowLiveDlg != NULL)
	{
		delete m_ShowLiveDlg;
		m_ShowLiveDlg = NULL;
	}

}


// voip callback
/**
 * ���з���Ӧ
 * ���з��յ����з��ĺ���
 * @param fromID
 */
void YpVoip::onCalling(string fromID)
{
	CString str;
	str.Format("�Ƿ�ͬ���û�:%s������Ƶͨ��", fromID.c_str());
	if (IDYES == AfxMessageBox(str, MB_YESNO))
	{
		m_bAudio = false;
		m_strTargetId = fromID;
		m_ShowLiveDlg->ShowWindow(SW_SHOW);
		m_pVoipManager->accept(fromID);
		m_bConnect = true;

		if (m_ShowLiveDlg->m_pDataShowView != NULL)
		{
			m_ShowLiveDlg->m_pDataShowView->addUser(m_pUserManager->m_ServiceParam.m_strUserId, false);
			m_ShowLiveDlg->m_pDataShowView->addUser(fromID, true);
			m_ShowLiveDlg->m_pDataShowView->setShowPictures();
		}
		startGetData((CROP_TYPE)m_pUserManager->m_ServiceParam.m_CropType, true);
		if (m_pSoundManager != NULL)
		{
			m_pSoundManager->startSoundData(true);;
		}
	}
	else
	{
		m_pVoipManager->refuse();
	}
}

/**
* ���з���Ӧ��������
* ���з��յ����з��ĺ���
* @param fromID
*/
void YpVoip::onAudioCalling(string fromID)
{
	CString str;
	str.Format("�Ƿ�ͬ���û�:%s��������ͨ��", fromID.c_str());
	if (IDYES == AfxMessageBox(str, MB_YESNO))
	{
		m_bAudio = true;
		m_strTargetId = fromID;
		CRect rect;
		m_ShowLiveDlg->m_bAudio = true;
		m_ShowLiveDlg->m_strAimID = fromID;
		m_ShowLiveDlg->ShowWindow(SW_SHOW);
		m_pVoipManager->accept(fromID);
		m_bConnect = true;

		if (m_ShowLiveDlg->m_pDataShowView != NULL && m_bAudio == false)
		{
			m_ShowLiveDlg->m_pDataShowView->addUser(m_pUserManager->m_ServiceParam.m_strUserId, false);
			m_ShowLiveDlg->m_pDataShowView->addUser(fromID, true);
			m_ShowLiveDlg->m_pDataShowView->setShowPictures();
		}
		//startGetData((CROP_TYPE)m_pUserManager->m_ServiceParam.m_CropType, true);
		if (m_pSoundManager != NULL)
		{
			m_pSoundManager->startSoundData(true);;
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
void YpVoip::onCancled(string fromID)
{
	stopGetData();
	if (m_ShowLiveDlg->m_pDataShowView != NULL && m_bAudio == false)
	{
		m_ShowLiveDlg->m_pDataShowView->removeAllUser();
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
	m_ShowLiveDlg->ShowWindow(SW_HIDE);
	m_strTargetId = "";
}

/**
 * ���з���Ӧ
 * ���з��ܾ���ͨ��ͨ�����ܾ���
 * @param fromID
 */
void YpVoip::onRefused(string fromID)
{
	stopGetData();
	if (m_ShowLiveDlg->m_pDataShowView != NULL && m_bAudio == false)
	{
		m_ShowLiveDlg->m_pDataShowView->removeAllUser();
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
	m_ShowLiveDlg->ShowWindow(SW_HIDE);
	m_strTargetId = "";
	AfxMessageBox("�Է��ܾ���ͨ");
}

/**
 * ���з���Ӧ
 * ���з���·æ���Է�ͨ���У�
 * @param fromID
 */
void YpVoip::onBusy(string fromID)
{
	//�ر�
	stopGetData();
	if (m_ShowLiveDlg->m_pDataShowView != NULL && m_bAudio == false)
	{
		m_ShowLiveDlg->m_pDataShowView->removeAllUser();
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
	m_ShowLiveDlg->ShowWindow(SW_HIDE);
	m_strTargetId = "";
	AfxMessageBox("�Է���·æ");
}

/**
 * ͨ���д��������
 */
void YpVoip::onMiss(CIMMessage* pMsg)
{
}

/**
 * ���з���Ӧ
 * ���з���ͨ��ͨ����ʼ��
 * @param fromID
 */
void YpVoip::onConnected(string fromID)
{
	//�����ʾ�Է�����
	if (m_ShowLiveDlg->m_pDataShowView != NULL && m_bAudio == false)
	{
		m_strTargetId = fromID;
		m_ShowLiveDlg->m_pDataShowView->addUser(fromID, true);
		m_ShowLiveDlg->m_pDataShowView->changeShowStyle(m_pUserManager->m_ServiceParam.m_strUserId, false);
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
	//���ò�������
	m_bInsertData = true;
	if (m_pSoundManager != NULL)
	{
		m_pSoundManager->startSoundData(true);
	}
	m_bConnect = true;
}

/**
 * �Է��Ѿ��Ҷ�
 * @param fromID
 */
void YpVoip::onHangup(string fromID)
{
	stopGetData();
	if (m_pSoundManager != NULL)
	{
		m_pSoundManager->stopGetSoundData();
	}

	if (m_pVoipManager != NULL)
	{
		if (m_bConnect)
		{
			m_pVoipManager->hangup(0);
		}
		else
		{
			m_pVoipManager->cancel();
		}
		m_bConnect = false;
	}
	if (m_ShowLiveDlg->m_pDataShowView != NULL && m_bAudio == false)
	{
		m_ShowLiveDlg->m_pDataShowView->removeAllUser();
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
	m_ShowLiveDlg->ShowWindow(SW_HIDE);
	m_strTargetId = "";
}

/**
 * voip����
 * @param errorCode
 */
void YpVoip::onError(string errorCode)
{
	//�����Լ�
	stopGetData();
	if (m_pSoundManager != NULL)
	{
		m_pSoundManager->stopGetSoundData();
	}
	if (m_pVoipManager != NULL)
	{
		m_pVoipManager->hangup(0);
	}
	if (m_ShowLiveDlg->m_pDataShowView != NULL && m_bAudio == false)
	{
		m_ShowLiveDlg->m_pDataShowView->removeAllUser();
	}
	m_ShowLiveDlg->ShowWindow(SW_HIDE);
	//�Ͽ�����
	CString strErr;
	strErr.Format("err:%s", errorCode.c_str());
	AfxMessageBox(strErr);
	m_strTargetId = "";
}

/**
 * �յ�ʵʱ����
 * @param data
 */
void YpVoip::onReceiveRealtimeData(uint8_t* data, int length)
{
}

int YpVoip::getVideoRaw(string strUserId, int w, int h, uint8_t* videoData, int videoDataLen)
{
	if (m_ShowLiveDlg->m_pDataShowView != NULL && m_bAudio == false)
	{
		m_ShowLiveDlg->m_pDataShowView->drawPic(FMT_YUV420P, m_strTargetId, w, h, videoData, videoDataLen);
	}
	return 0;
}

/**
 * ���ݴ���ģʽ�л�
 * @param state
 */
void YpVoip::onTransStateChanged(int state)
{
}

void YpVoip::stopLive()
{
	stopGetData();
	if (m_pSoundManager != NULL)
	{
		m_pSoundManager->stopGetSoundData();
	}

	if (m_pVoipManager != NULL)
	{
		if (m_bConnect)
		{
			m_pVoipManager->hangup(1);
		}
		else
		{
			m_pVoipManager->cancel();
		}
		m_bConnect = false;
	}
	if (m_ShowLiveDlg->m_pDataShowView != NULL && m_bAudio == false)
	{
		m_ShowLiveDlg->m_pDataShowView->removeAllUser();
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
	m_ShowLiveDlg->ShowWindow(SW_HIDE);
	m_strTargetId = "";
}

void YpVoip::addUpId()
{
	if (m_ShowLiveDlg->m_pDataShowView != NULL && m_bAudio == false)
	{
		m_ShowLiveDlg->m_pDataShowView->addUser(m_pUserManager->m_ServiceParam.m_strUserId, false);
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
}

void YpVoip::insertVideoRaw(uint8_t* videoData, int dataLen, int isBig)
{
	if (m_pVoipManager != NULL && m_bAudio == false)
	{
		m_pVoipManager->insertVideoRaw(videoData, dataLen, isBig);
	}
}

int YpVoip::cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall)
{
	int ret = 0;
	if (m_pVoipManager != NULL)
	{
		ret = m_pVoipManager->cropVideoRawNV12(w, h, videoData, dataLen, (int)CROP_TYPE::VIDEO_CROP_CONFIG_480BW_480BH_SMALL_NONE, 0, 0, outVideoDataBig, outVideoDataSmall);
	}
	return ret;
}
void YpVoip::drawPic(YUV_TYPE type, int w, int h, uint8_t* videoData, int videoDataLen)
{
	if (m_ShowLiveDlg->m_pDataShowView != NULL && m_bAudio == false)
	{
		m_ShowLiveDlg->m_pDataShowView->drawPic(type, m_pUserManager->m_ServiceParam.m_strUserId, w, h, videoData, videoDataLen);
	}
}

void YpVoip::onNewMessage(CIMMessage* var1)
{
	CString strMsg = "";
	strMsg.Format("%s:%s", var1->m_strFromId.c_str(), var1->m_strContentData.c_str());
	//m_HistoryMsg.InsertString(0, strMsg);
}

void YpVoip::changeShowStyle(string strUserId)
{
	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		string strId = m_ShowLiveDlg->m_pDataShowView->changeShowStyle(strUserId, true);
		m_ShowLiveDlg->m_pDataShowView->changeShowStyle(strId, false);
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
}
void YpVoip::closeCurrentLive()
{
}
void YpVoip::getLocalSoundData(char* pData, int nLength)
{
	if (m_pVoipManager != NULL)
	{
		m_pVoipManager->insertAudioRaw((uint8_t*)pData, nLength);
	}
}

void YpVoip::querySoundData(char** pData, int* nLength)
{
	if (m_pVoipManager != NULL)
	{
		m_pVoipManager->querySoundData((uint8_t**)pData, nLength);
	}
}



void YpVoip::callPerson(string targetid)
{
	bool isCallSuccess = false;
	//���жԷ�
	if (m_pVoipManager != NULL)
	{
		isCallSuccess=m_pVoipManager->call(targetid);
	}
	if (!isCallSuccess) {
		AfxMessageBox("����ʧ��");
		return;
	}
	m_ShowLiveDlg->ShowWindow(SW_SHOW);
	if (m_ShowLiveDlg->m_pDataShowView != NULL)
	{
		m_ShowLiveDlg->m_pDataShowView->addUser(m_pUserManager->m_ServiceParam.m_strUserId, true);
		m_ShowLiveDlg->m_pDataShowView->setShowPictures();
	}
	if (m_pSoundManager != NULL)
	{
		m_pSoundManager->startSoundData(true);
	}

	startGetData((CROP_TYPE)m_pUserManager->m_ServiceParam.m_CropType, false);

}
