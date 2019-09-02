#pragma once
#include <string>
#include "CUserManager.h"
#include "XHVoipP2PManager.h"
#include "CSoundManager.h"
#include "CShowLiveDlg.h"
#include "CDataControl.h"
#include "BackMsgEntity.h"

using namespace std;
// TPVOIP_P2P �Ի���

class TPVOIP_P2P : public CDialogEx, public CLocalDataControl, public IVoipP2PManagerListener, public CPicControlCallback, public IShowLiveCallback, public ISoundCallback
{
public:
	TPVOIP_P2P(CUserManager* pUserManager,char* LocaIP);   // ��׼���캯��
	virtual ~TPVOIP_P2P();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VOIP_P2P };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	 void IPaccept(char* AdmIP);
	 void IPCall(char* AdmIP);
	 void OnBnClickedButtonCalling();
	virtual BOOL OnInitDialog();
public:

	/**
	 * ���з���Ӧ
	 * ���з��յ����з��ĺ���
	 * @param fromID
	 */
	virtual void onCalling(string fromID);
	/**
	 * ���з���Ӧ
	 * ���з��ڱ��з�����֮ǰ�Ҷϣ�ͨ����ȡ����
	 * @param fromID
	 */
	virtual void onCancled(string fromID);

	/**
	 * ���з���Ӧ
	 * ���з��ܾ���ͨ��ͨ�����ܾ���
	 * @param fromID
	 */
	virtual void onRefused(string fromID);

	/**
	 * ���з���Ӧ
	 * ���з���·æ���Է�ͨ���У�
	 * @param fromID
	 */
	virtual void onBusy(string fromID);

	/**
	 * ���з���Ӧ
	 * ���з���ͨ��ͨ����ʼ��
	 * @param fromID
	 */
	virtual void onConnected(string fromID);

	/**
	 * �Է��Ѿ��Ҷ�
	 * @param fromID
	 */
	virtual void onHangup(string fromID);

	/**
	 * voip����
	 * @param errorCode
	 */
	virtual void onError(string errorCode);

	/**
	 * �յ�ʵʱ����
	 * @param data
	 */
	virtual void onReceiveRealtimeData(uint8_t* data, int length);

	/**
	 * �յ���Ƶ����
	 * @param data
	 */
	virtual int getVideoRaw(string strUserId, int w, int h, uint8_t* videoData, int videoDataLen);
public:
	virtual void changeShowStyle(string strUserId);
	virtual void closeCurrentLive();
public:
	virtual void stopLive();
public:
	virtual void getLocalSoundData(char* pData, int nLength);
	virtual void querySoundData(char** pData, int* nLength);
public:
	virtual void addUpId();
	virtual void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	virtual int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
	virtual void drawPic(YUV_TYPE type, int w, int h, uint8_t* videoData, int videoDataLen);
private:
	string m_strLocalIP;
	string m_strAimIP;
	CIPAddressCtrl m_LocalIP;
	CIPAddressCtrl m_AimIP;
	CUserManager* m_pUserManager;
	XHVoipP2PManager* m_pVoipManager;
	CSoundManager* m_pSoundManager;
	CShowLiveDlg* m_ShowLiveDlg;
	bool m_bConnect;
};
