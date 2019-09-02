#pragma once
#include <string>
#include "CUserManager.h"
#include "XHVoipP2PManager.h"
#include "CSoundManager.h"
#include "CShowLiveDlg.h"
#include "CDataControl.h"
#include "BackMsgEntity.h"

using namespace std;
// TPVOIP_P2P 对话框

class TPVOIP_P2P : public CDialogEx, public CLocalDataControl, public IVoipP2PManagerListener, public CPicControlCallback, public IShowLiveCallback, public ISoundCallback
{
public:
	TPVOIP_P2P(CUserManager* pUserManager,char* LocaIP);   // 标准构造函数
	virtual ~TPVOIP_P2P();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VOIP_P2P };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	 void IPaccept(char* AdmIP);
	 void IPCall(char* AdmIP);
	 void OnBnClickedButtonCalling();
	virtual BOOL OnInitDialog();
public:

	/**
	 * 被叫方响应
	 * 被叫方收到主叫方的呼叫
	 * @param fromID
	 */
	virtual void onCalling(string fromID);
	/**
	 * 被叫方响应
	 * 主叫方在被叫方接听之前挂断（通话被取消）
	 * @param fromID
	 */
	virtual void onCancled(string fromID);

	/**
	 * 主叫方响应
	 * 被叫方拒绝接通（通话被拒绝）
	 * @param fromID
	 */
	virtual void onRefused(string fromID);

	/**
	 * 主叫方响应
	 * 被叫方线路忙（对方通话中）
	 * @param fromID
	 */
	virtual void onBusy(string fromID);

	/**
	 * 主叫方响应
	 * 被叫方接通（通话开始）
	 * @param fromID
	 */
	virtual void onConnected(string fromID);

	/**
	 * 对方已经挂断
	 * @param fromID
	 */
	virtual void onHangup(string fromID);

	/**
	 * voip报错
	 * @param errorCode
	 */
	virtual void onError(string errorCode);

	/**
	 * 收到实时数据
	 * @param data
	 */
	virtual void onReceiveRealtimeData(uint8_t* data, int length);

	/**
	 * 收到视频数据
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
