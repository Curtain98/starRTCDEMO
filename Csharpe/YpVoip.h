#pragma once
#include "CVoipDataShowView.h"
#include "XHVoipManager.h"
#include "CDataControl.h"
#include "CShowLiveDlg.h"
#include "CSqliteDB.h"
#include "CSoundManager.h"
#include "CUserManager.h"


class YpVoip :  public CLocalDataControl, public IVoipManagerListener, public CPicControlCallback, public IShowLiveCallback, public ISoundCallback
{

	public:
	YpVoip(CUserManager* pUserManager);   // ��׼���캯��
	virtual ~YpVoip();

public:
	// voip callback
	/**
	 * ���з���Ӧ
	 * ���з��յ����з��ĺ���
	 * @param fromID
	 */
	virtual void onCalling(string fromID);

	/**
	 * ���з���Ӧ��������
	 * ���з��յ����з��ĺ���
	 * @param fromID
	 */
	virtual void onAudioCalling(string fromID);

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
	 * ͨ���д��������
	 */
	virtual void onMiss(CIMMessage* pMsg);

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
	 * �յ�ʵʱ����
	 */
	virtual int getVideoRaw(string strUserId, int w, int h, uint8_t* videoData, int videoDataLen);

	/**
	* ���ݴ���ģʽ�л�
	* @param state
	*/
	virtual void onTransStateChanged(int state);

public:
	/**
	 * ֹͣ��Ƶ�ص�
	 */
	virtual void stopLive();

	/**
	 * upid����
	 */
	virtual void addUpId();
	/**
	 * �������ݻص�
	 */
	virtual void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	/**
	 * �ü���Ƶ����
	 */
	virtual int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
	/**
	 * ����
	 */
	virtual void drawPic(YUV_TYPE type, int w, int h, uint8_t* videoData, int videoDataLen);
	// msg callback
	/**
	 * ���յ���Ϣ
	 */
	virtual void onNewMessage(CIMMessage* var1);

	// picture control callback
	virtual void changeShowStyle(string strUserId);
	virtual void closeCurrentLive();
public:
	virtual void getLocalSoundData(char* pData, int nLength);
	virtual void querySoundData(char** pData, int* nLength);
public:
	CStatic m_ShowArea;
	//CVoipDataShowView* m_pDataShowView;
	CUserManager* m_pUserManager;
	XHVoipManager* m_pVoipManager;
	CSoundManager* m_pSoundManager;
	CShowLiveDlg* m_ShowLiveDlg;
	bool m_bConnect;
	//CSqliteDB* m_pSqliteDB;
	string m_strTargetId;
	bool m_bAudio;
	void callPerson(string targetid);

};
