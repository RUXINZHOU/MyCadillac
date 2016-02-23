
// TSComDlg.h : ͷ�ļ�
//

#pragma once
#include "mscomm.h"
#include "afxwin.h"


// CTSComDlg �Ի���
class CTSComDlg : public CDialogEx
{
// ����
public:
	CTSComDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TSCOM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMscomm m_Com;
	CButton m_ButtonOpen;
	CButton m_ButtonClose;
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedClose();
	CComboBox m_ComboBox;
	afx_msg void OnCbnSelchangeCombo();
	// �������
	int m_ComOrder;
	// ���ڲ���
	CString m_ComSetting;
	// Ҫ���͵�����
	CString m_Order2Send;
	// �����ô��ںŵ���Ͽ�
	CComboBox m_ComboComOrder;
	// ��ʾ�յ������ݵı༭��
	CEdit m_CEditDataR;
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	afx_msg void OnCbnSelchangeOrder();
	CButton m_ButtonForward;
	CButton m_ButtonLeft;
	CButton m_ButtonRight;
	CButton m_ButtonBack;
	afx_msg void OnBnClickedForward();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedBack();
	void manage_measure_data(CString);

	// �յ�������
	CString m_RecievedStr;
	afx_msg void OnBnClickedClear();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// Ҫ���Ƶ��豸
	CComboBox mTargets;
	CButton mButton_stop;
	// ��ǰѡ�е��豸
	int mTarget;
	// �Ҽ���ֵ
	CString command_right[6] = { _T("R"), _T("r"), _T("3"), _T("R"), _T("+"), _T("j") };
	// �����ֵ	
	CString command_left[6] = { _T("L"), _T("l"), _T("1"), _T("L"), _T("-"), _T("J") };
	//�ϼ���ֵ
	CString command_up[2] = { _T("U"), _T("f") };
	CString command_down[3] = { _T("D"), _T(""), _T("2") };
	afx_msg void OnTargetChange();
	afx_msg void OnBnClickedStop();
	CEdit mTemerature;
	CEdit mHumidity;
	CEdit mFDistance;
	CEdit mBDistance;
	CButton mbutton_renew_HT;
	CButton mbutton_renew_FB;
	CButton mbutton_auto_renew;
	CButton mbutton_auto_mode;
	CButton mbutton_fine_turning;
	CButton mbutton_s1;
	CButton mbutton_s2;
	CButton mbutton_s3;
	CButton mbutton_s4;
	CButton mbutton_s5;
	// ��Ϊ�ռ���Ϣ������
	CString mString_MeasureData;
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedRenewFB();
	afx_msg void OnBnClickedAutoRenew();
	bool auto_renew;
	bool auto_mode;
	afx_msg void OnBnClickedAutoMode();
	afx_msg void OnBnClickedFineTurn();
	// ���΢����־
	bool is_fine_turning;
	afx_msg void OnBnClickedL1();
	afx_msg void OnBnClickedL2();
	afx_msg void OnBnClickedL3();
	afx_msg void OnBnClickedL4();
	afx_msg void OnBnClickedL5();
	// ��־�Ƿ��а������£���ֹ��Ϣ�ص�����
	bool has_key_down;
};
