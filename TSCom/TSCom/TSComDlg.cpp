
// TSComDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TSCom.h"
#include "TSComDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTSComDlg �Ի���



CTSComDlg::CTSComDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TSCOM_DIALOG, pParent)
	, m_ComOrder(0)
	, m_ComSetting(_T(""))
	, m_Order2Send(_T(""))
	, m_RecievedStr(_T(""))
	, mTarget(0)
	, mString_MeasureData(_T(""))
	, auto_renew(false)
	, auto_mode(false)
	, is_fine_turning(false)
	, has_key_down(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTSComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_Com);
	DDX_Control(pDX, IDC_BUTTON1, m_ButtonOpen);
	DDX_Control(pDX, IDC_BUTTON2, m_ButtonClose);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
	DDX_Control(pDX, IDC_COMBO2, m_ComboComOrder);
	DDX_Control(pDX, IDC_EDIT1, m_CEditDataR);
	DDX_Control(pDX, IDC_BUTTON3, m_ButtonForward);
	DDX_Control(pDX, IDC_BUTTON4, m_ButtonLeft);
	DDX_Control(pDX, IDC_BUTTON5, m_ButtonRight);
	DDX_Control(pDX, IDC_BUTTON6, m_ButtonBack);
	DDX_Control(pDX, IDC_COMBO3, mTargets);
	DDX_Control(pDX, IDC_BUTTON8, mButton_stop);
	DDX_Control(pDX, IDC_EDIT2, mTemerature);
	DDX_Control(pDX, IDC_EDIT3, mHumidity);
	DDX_Control(pDX, IDC_EDIT4, mFDistance);
	DDX_Control(pDX, IDC_EDIT5, mBDistance);
	DDX_Control(pDX, IDC_BUTTON9, mbutton_renew_HT);
	DDX_Control(pDX, IDC_BUTTON10, mbutton_renew_FB);
	DDX_Control(pDX, IDC_BUTTON11, mbutton_auto_renew);
	DDX_Control(pDX, IDC_BUTTON12, mbutton_auto_mode);
	DDX_Control(pDX, IDC_BUTTON21, mbutton_fine_turning);
	DDX_Control(pDX, IDC_BUTTON13, mbutton_s1);
	DDX_Control(pDX, IDC_BUTTON14, mbutton_s2);
	DDX_Control(pDX, IDC_BUTTON15, mbutton_s3);
	DDX_Control(pDX, IDC_BUTTON16, mbutton_s4);
	DDX_Control(pDX, IDC_BUTTON20, mbutton_s5);
}

BEGIN_MESSAGE_MAP(CTSComDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTSComDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_BUTTON2, &CTSComDlg::OnBnClickedClose)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTSComDlg::OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CTSComDlg::OnCbnSelchangeOrder)
	ON_BN_CLICKED(IDC_BUTTON3, &CTSComDlg::OnBnClickedForward)
	ON_BN_CLICKED(IDC_BUTTON4, &CTSComDlg::OnBnClickedLeft)
	ON_BN_CLICKED(IDC_BUTTON5, &CTSComDlg::OnBnClickedRight)
	ON_BN_CLICKED(IDC_BUTTON6, &CTSComDlg::OnBnClickedBack)
	ON_BN_CLICKED(IDC_BUTTON7, &CTSComDlg::OnBnClickedClear)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CTSComDlg::OnTargetChange)
	ON_BN_CLICKED(IDC_BUTTON8, &CTSComDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_BUTTON9, &CTSComDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CTSComDlg::OnBnClickedRenewFB)
	ON_BN_CLICKED(IDC_BUTTON11, &CTSComDlg::OnBnClickedAutoRenew)
	ON_BN_CLICKED(IDC_BUTTON12, &CTSComDlg::OnBnClickedAutoMode)
	ON_BN_CLICKED(IDC_BUTTON21, &CTSComDlg::OnBnClickedFineTurn)
	ON_BN_CLICKED(IDC_BUTTON13, &CTSComDlg::OnBnClickedL1)
	ON_BN_CLICKED(IDC_BUTTON14, &CTSComDlg::OnBnClickedL2)
	ON_BN_CLICKED(IDC_BUTTON15, &CTSComDlg::OnBnClickedL3)
	ON_BN_CLICKED(IDC_BUTTON16, &CTSComDlg::OnBnClickedL4)
	ON_BN_CLICKED(IDC_BUTTON20, &CTSComDlg::OnBnClickedL5)
END_MESSAGE_MAP()


// CTSComDlg ��Ϣ�������

BOOL CTSComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//��Ӳ�����ѡ��
	m_ComboBox.AddString(_T("19200"));
	m_ComboBox.AddString(_T("9600"));
	m_ComboBox.AddString(_T("4800"));
	m_ComboBox.AddString(_T("2400"));
	//��Ӷ˿ں�ѡ��
	m_ComboComOrder.AddString(_T("com1"));
	m_ComboComOrder.AddString(_T("com2"));
	m_ComboComOrder.AddString(_T("com3"));
	m_ComboComOrder.AddString(_T("com4"));
	//���Ŀ���豸��Ŀ
	mTargets.AddString(_T("�����"));
	mTargets.AddString(_T("ǰ���"));
	mTargets.AddString(_T("����"));
	//��������Ͽ�Ĭ������
	m_ComboBox.SetCurSel(3);
	m_ComSetting = "9600,n,8,1";
	//�˿ں�Ĭ������
	m_ComboComOrder.SetCurSel(3);
	m_ComOrder = 4;
	//Ĭ��Ŀ���豸����
	mTargets.SetCurSel(0);
	mTarget = 0;
	//��ť����
	m_ButtonClose.EnableWindow(FALSE);
	m_ButtonOpen.EnableWindow(TRUE);
	m_ButtonForward.EnableWindow(FALSE);
	m_ButtonBack.EnableWindow(FALSE);
	m_ButtonLeft.EnableWindow(FALSE);
	m_ButtonRight.EnableWindow(FALSE);
	mButton_stop.EnableWindow(FALSE);
	mbutton_auto_mode.EnableWindow(FALSE);
	mbutton_auto_renew.EnableWindow(FALSE);
	mbutton_fine_turning.EnableWindow(FALSE);
	mbutton_renew_FB.EnableWindow(FALSE);
	mbutton_renew_HT.EnableWindow(FALSE);
	mbutton_s1.EnableWindow(FALSE);
	mbutton_s2.EnableWindow(FALSE);
	mbutton_s3.EnableWindow(FALSE);
	mbutton_s4.EnableWindow(FALSE);
	mbutton_s5.EnableWindow(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTSComDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTSComDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTSComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTSComDlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = 0, t_usable[4] = { 0, 0, 0, 0 }, sum = 0;
	HANDLE hcom = INVALID_HANDLE_VALUE;
	CString coms[] = { _T("COM1"), _T("COM2"), _T("COM3"), _T("COM4") };
	while (i < 4)
	{
		hcom = CreateFile(coms[i], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hcom != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hcom);
			t_usable[i] = 1;
			sum++;
		}
		i++;
	}
	if (sum == 0)
	{
		MessageBox(_T("δ���ֿ��ô��пڣ���ʧ�ܣ�"));
		return;
	}
	else
	{
		if (t_usable[m_ComOrder - 1] == 0)
		{
			CString t1("����"),t2;
			i = 0;
			while (i < 4)
			{
				if (t_usable[i] == 1)
				{
					t2.Format(_T("%d��"), i + 1);
					t1 += t2;
				}
				i++;
			}
			
			MessageBox(_T("��ǰ���пڲ����ã���ʧ�ܣ�"));
			if (t1 != "����")
			{
				MessageBox(t1 + _T("���ã�"));
			}
			return;
		}
	}
	m_Com.CloseWindow();
	if (m_Com.get_PortOpen())
	{
		m_Com.put_PortOpen(FALSE);
	}
	m_Com.put_CommPort(m_ComOrder);
	if (!m_Com.get_PortOpen())
	{
		m_Com.put_PortOpen(TRUE);
	}
	else
	{
		MessageBox(_T("δ�ܴ򿪴��ڣ�"));
		return;
	}
	m_Com.put_Settings(m_ComSetting);
	m_Com.put_RThreshold(1);
	m_Com.put_InputMode(1);
	m_Com.put_InputLen(0);
	m_Com.get_Input();
	m_ComboBox.EnableWindow(FALSE);
	m_ComboComOrder.EnableWindow(FALSE);
	m_ButtonClose.EnableWindow(TRUE);
	m_ButtonOpen.EnableWindow(FALSE);
	m_ButtonForward.EnableWindow(TRUE);
	m_ButtonBack.EnableWindow(TRUE);
	m_ButtonLeft.EnableWindow(TRUE);
	m_ButtonRight.EnableWindow(TRUE);
	mButton_stop.EnableWindow(TRUE);
	mTargets.EnableWindow(TRUE);
	mButton_stop.EnableWindow(TRUE);
	mbutton_auto_mode.EnableWindow(TRUE);
	mbutton_auto_renew.EnableWindow(TRUE);
	mbutton_fine_turning.EnableWindow(TRUE);
	mbutton_renew_FB.EnableWindow(TRUE);
	mbutton_renew_HT.EnableWindow(TRUE);
	mbutton_s1.EnableWindow(TRUE);
	mbutton_s2.EnableWindow(TRUE);
	mbutton_s3.EnableWindow(TRUE);
	mbutton_s4.EnableWindow(TRUE);
	mbutton_s5.EnableWindow(TRUE);
	MessageBox(_T("�򿪴��ڳɹ���"));
	m_Com.put_Output(COleVariant(_T("S")));//��������֪ͨ
}


void CTSComDlg::OnBnClickedClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Com.put_Output(COleVariant(_T("O")));//���������ж�֪ͨ
	m_Com.put_PortOpen(FALSE);
	m_ComboBox.EnableWindow(TRUE);
	m_ComboComOrder.EnableWindow(TRUE);
	m_ButtonClose.EnableWindow(FALSE);
	m_ButtonOpen.EnableWindow(TRUE);
	m_ButtonForward.EnableWindow(FALSE);
	m_ButtonBack.EnableWindow(FALSE);
	m_ButtonLeft.EnableWindow(FALSE);
	m_ButtonRight.EnableWindow(FALSE);
	mButton_stop.EnableWindow(FALSE);
	mTargets.EnableWindow(FALSE);
	mButton_stop.EnableWindow(FALSE);
	mbutton_auto_mode.EnableWindow(FALSE);
	mbutton_auto_renew.EnableWindow(FALSE);
	mbutton_fine_turning.EnableWindow(FALSE);
	mbutton_renew_FB.EnableWindow(FALSE);
	mbutton_renew_HT.EnableWindow(FALSE);
	mbutton_s1.EnableWindow(FALSE);
	mbutton_s2.EnableWindow(FALSE);
	mbutton_s3.EnableWindow(FALSE);
	mbutton_s4.EnableWindow(FALSE);
	mbutton_s5.EnableWindow(FALSE);
	MessageBox(_T("�����Ѿ��رգ�"));
}


void CTSComDlg::OnCbnSelchangeCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int sel = m_ComboBox.GetCurSel();
	switch (sel)
	{
	case 0:
		m_ComSetting = "19200,n,8,1";
		break;
	case 1:
		m_ComSetting = "2400,n,8,1";
		break;
	case 2:
		m_ComSetting = "4800,n,8,1";
		break;
	case 3:
		m_ComSetting = "9600,n,8,1";
		break;
	default:
		break;
	}
}
BEGIN_EVENTSINK_MAP(CTSComDlg, CDialogEx)
	ON_EVENT(CTSComDlg, IDC_MSCOMM1, 1, CTSComDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CTSComDlg::OnCommMscomm1()
{
	// TODO: �ڴ˴������Ϣ����������
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len, k;
	BYTE rxdata[2048];
	CString temp_str;
	if (2 == m_Com.get_CommEvent())
	{
		variant_inp = m_Com.get_Input();
		safearray_inp = variant_inp;
		len = safearray_inp.GetOneDimSize();
		for (k = 0; k < len; k++)
		{
			safearray_inp.GetElement(&k, rxdata + k);
		}
		for (k = 0; k < len; k++)
		{
			BYTE bt = *(char*)(rxdata + k);
			temp_str.Format(_T("%c"), bt);
			m_RecievedStr += temp_str;
		}
		m_RecievedStr += "\r\n";
	}
	//��ȡʱ��
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	//�ֱ�����
	char type = (char)m_RecievedStr[0];
	switch (type)
	{
	case '#':
		m_Com.put_Output(COleVariant(_T("&")));//����ȷ�Ϸ�
		if (mString_MeasureData.GetLength() > 0)
		{
			manage_measure_data(mString_MeasureData);
			mString_MeasureData = "";
		}
		else
		{
			m_CEditDataR.SetSel(1000000, 1000000);
			m_CEditDataR.ReplaceSel(CString(timE) + _T("���������ֹ��\r\n"));
			UpdateData(FALSE);
		}
		m_RecievedStr = "";
		break;
	case '$':
		m_Com.put_Output(COleVariant(_T("&")));//����ȷ�Ϸ�
		m_CEditDataR.SetSel(1000000, 1000000);
		m_CEditDataR.ReplaceSel(_T("MCU is uploading data...\r\n"));
		UpdateData(FALSE);
		m_RecievedStr = "";
		break;
	default:
		m_Com.put_Output(COleVariant(_T("&")));//����ȷ�Ϸ�
		mString_MeasureData.AppendChar(type);//�ռ�������Ϣ
		//��ӡ��־
		m_CEditDataR.SetSel(1000000, 1000000);
		m_CEditDataR.ReplaceSel(CString(timE) + _T("���յ���") + m_RecievedStr);
		UpdateData(FALSE);
		m_RecievedStr = "";
		break;
	}
}


void CTSComDlg::OnCbnSelchangeOrder()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int sel = m_ComboComOrder.GetCurSel();
	switch (sel)
	{
	case 0:
		m_ComOrder = 1;
		break;
	case 1:
		m_ComOrder = 2;
		break;
	case 2:
		m_ComOrder = 3;
		break;
	case 3:
		m_ComOrder = 4;
		break;
	default:
		break;
	}
}




void CTSComDlg::OnBnClickedForward()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_ButtonForward.IsWindowEnabled())
	{
		return;
	}
	m_Com.put_Output(COleVariant(command_up[mTarget]));
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo,&rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + command_up[mTarget] + CString(_T("\r\n")));
	UpdateData(FALSE);
}


void CTSComDlg::OnBnClickedLeft()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (is_fine_turning)
	{
		m_Com.put_Output(COleVariant(command_left[mTarget + 3]));
	}
	else
	{
		m_Com.put_Output(COleVariant(command_left[mTarget]));
	}
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo,&rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + command_left[mTarget] + CString(_T("\r\n")));
	UpdateData(FALSE);
}


void CTSComDlg::OnBnClickedRight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (is_fine_turning)
	{
		m_Com.put_Output(COleVariant(command_right[mTarget + 3]));
	}
	else
	{
		m_Com.put_Output(COleVariant(command_right[mTarget]));
	}
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo,&rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + command_right[mTarget] + CString(_T("\r\n")));
	UpdateData(FALSE);
}


void CTSComDlg::OnBnClickedBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_ButtonBack.IsWindowEnabled())
	{
		return;
	}
	m_Com.put_Output(COleVariant(command_down[mTarget]));
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo,&rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + CString(_T("D\r\n")));
	UpdateData(FALSE);
}


void CTSComDlg::OnBnClickedClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_CEditDataR.SetSel(0,2000000);
	m_CEditDataR.ReplaceSel(_T(""));
	UpdateData(FALSE);
}

BOOL CTSComDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && !has_key_down)
	{
		switch (pMsg->wParam)
		{
		case 37:
			OnBnClickedLeft();
			break;
		case 38:
			OnBnClickedForward();
			break;
		case 39:
			OnBnClickedRight();
			break;
		case 40:
			if (m_ButtonBack.IsWindowEnabled())
			{
				OnBnClickedBack();
			}
			break;
		case 49:
			OnBnClickedL1();
			break;
		case 50:
			OnBnClickedL2();
			break;
		case 51:
			OnBnClickedL3();
			break;
		case 52:
			OnBnClickedL4();
			break;
		case 53:
			OnBnClickedL5();
			break;
		default:
			break;
		}
		has_key_down = true;
	}
	else if (pMsg->message == WM_KEYUP || pMsg->wParam == 32)
	{
		if (mButton_stop.IsWindowEnabled())
		{
			OnBnClickedStop();
		}
		has_key_down = false;
	}
	if ((pMsg->wParam > 36 && pMsg->wParam < 41) || (pMsg->wParam > 48 && pMsg->wParam < 54))
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CTSComDlg::OnTargetChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int sel = mTargets.GetCurSel();
	switch (sel)
	{
	case 0:
		mTarget = 0;
		m_ButtonForward.EnableWindow(TRUE);
		m_ButtonBack.EnableWindow(TRUE);
		break;
	case 1:
		mTarget = 2;
		m_ButtonBack.EnableWindow(TRUE);
		m_ButtonForward.EnableWindow(FALSE);
		OnBnClickedStop();
		break;
	case 2:
		mTarget = 1;
		m_ButtonBack.EnableWindow(FALSE);
		m_ButtonForward.EnableWindow(TRUE);
		OnBnClickedStop();
		break;
	default:
		break;
	}
}


void CTSComDlg::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Order2Send = 's';
	m_Com.put_Output(COleVariant(m_Order2Send));
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo,&rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + CString(_T("s\r\n")));
	UpdateData(FALSE);
}

void CTSComDlg::manage_measure_data(CString data)
{
	if (data.GetLength() == 0)
	{
		return;
	}
	char type = (char)data[0];
	switch (type)
	{
	case 'H':
		mHumidity.SetWindowTextW(data.Right(data.GetLength() - 1));
		break;
	case 'T':
		mTemerature.SetWindowTextW(data.Right(data.GetLength() - 1));
		break;
	case 'D':
		mFDistance.SetWindowTextW(data.Right(data.GetLength() - 1));
		break;
	case 'd':
		mBDistance.SetWindowTextW(data.Right(data.GetLength() - 1));
		break;
	case 'M':
		m_CEditDataR.SetSel(1000000, 1000000);
		m_CEditDataR.ReplaceSel(_T("��Ϣ��") + data + CString(_T("\r\n")));
		UpdateData(FALSE);
		break;
	default:
		m_CEditDataR.SetSel(1000000, 1000000);
		m_CEditDataR.ReplaceSel(_T("���룺") + data + CString(_T("\r\n")));
		UpdateData(FALSE);
		break;
	}
}

void CTSComDlg::OnBnClickedButton9()//������ʪ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Com.put_Output(COleVariant(_T("S")));//��������֪ͨ
	m_Com.put_Output(COleVariant(_T("n")));
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + CString(_T("S + n\r\n")));
	UpdateData(FALSE);
}


void CTSComDlg::OnBnClickedRenewFB()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Com.put_Output(COleVariant(_T("S")));//��������֪ͨ
	m_Com.put_Output(COleVariant(_T("N")));
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + CString(_T("S + N\r\n")));
	UpdateData(FALSE);
}


void CTSComDlg::OnBnClickedAutoRenew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (auto_renew)
	{
		m_Com.put_Output(COleVariant(_T("$")));
		mbutton_auto_renew.SetWindowTextW(_T("�ֶ�����"));
		auto_renew = false;
		//��ӡ��־
		char timE[12];
		time_t rawtime = time(0);
		struct tm timeinfo;
		localtime_s(&timeinfo, &rawtime);
		strftime(timE, sizeof(timE), "%X", &timeinfo);
		m_CEditDataR.SetSel(1000000, 1000000);
		m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + CString(_T("$\r\n")));
		UpdateData(FALSE);
		return;
	}
	m_Com.put_Output(COleVariant(_T("S")));//��������֪ͨ
	m_Com.put_Output(COleVariant(_T("#")));
	mbutton_auto_renew.SetWindowTextW(_T("�Զ�����"));
	auto_renew = true;
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + CString(_T("S + #\r\n")));
	UpdateData(FALSE);
}


void CTSComDlg::OnBnClickedAutoMode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (auto_mode)
	{
		OnBnClickedStop();
		mbutton_auto_mode.SetWindowTextW(_T("�ֶ�����"));
		auto_mode = false;
		return;
	}
	m_Com.put_Output(COleVariant(_T("P")));
	mbutton_auto_mode.SetWindowTextW(_T("�Զ�����"));
	auto_mode = true;
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + CString(_T("P\r\n")));
	UpdateData(FALSE);
}


void CTSComDlg::OnBnClickedFineTurn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (is_fine_turning)
	{
		mbutton_fine_turning.SetWindowTextW(_T("���΢��"));
		is_fine_turning = false;
		return;
	}
	mbutton_fine_turning.SetWindowTextW(_T("�ر�΢��"));
	is_fine_turning = true;
}


void CTSComDlg::OnBnClickedL1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Com.put_Output(COleVariant(_T("A")));
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + CString(_T("A\r\n")));
	UpdateData(FALSE);
}


void CTSComDlg::OnBnClickedL2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Com.put_Output(COleVariant(_T("B")));
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + CString(_T("B\r\n")));
	UpdateData(FALSE);
}


void CTSComDlg::OnBnClickedL3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Com.put_Output(COleVariant(_T("C")));
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + CString(_T("C\r\n")));
	UpdateData(FALSE);
}


void CTSComDlg::OnBnClickedL4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Com.put_Output(COleVariant(_T("E")));
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + CString(_T("E\r\n")));
	UpdateData(FALSE);
}


void CTSComDlg::OnBnClickedL5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Com.put_Output(COleVariant(_T("F")));
	//��ӡ��־
	char timE[12];
	time_t rawtime = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	strftime(timE, sizeof(timE), "%X", &timeinfo);
	m_CEditDataR.SetSel(1000000, 1000000);
	m_CEditDataR.ReplaceSel(CString(timE) + _T("�����ͣ�") + CString(_T("F\r\n")));
	UpdateData(FALSE);
}
