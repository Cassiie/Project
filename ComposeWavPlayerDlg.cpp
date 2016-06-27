
// ComposeWavPlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ComposeWavPlayer.h"
#include "ComposeWavPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

extern CString g_strSampleDir, g_strLogDir;
int m_isComposed = -1, m_isNoModFile = -1;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CComposeWavPlayerDlg �Ի���



CComposeWavPlayerDlg::CComposeWavPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComposeWavPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_SrcPaintData = NULL;
	m_LogPaintData = NULL;
	m_fPos = -1;
	m_fLikely = 0;
	m_DataBlock = 2;
	m_SrcMaxValue = 0;
	m_LogMaxValue = 0;
}

void CComposeWavPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Process, m_process);
	DDX_Control(pDX, IDC_bnPlay1, m_play);
	DDX_Control(pDX, IDC_bnPause1, m_pause);
	DDX_Control(pDX, IDC_bnStop1, m_stop);
	DDX_Control(pDX, IDC_Likely, m_likely);
	DDX_Control(pDX, IDC_WAVE_DRAW1, m_picDraw1);
	DDX_Control(pDX, IDC_WAVE_DRAW2, m_picDraw2);
	DDX_Control(pDX, IDC_bnPlay2, m_play2);
	DDX_Control(pDX, IDC_bnPause2, m_pause2);
	DDX_Control(pDX, IDC_bnStop2, m_stop2);
	DDX_Control(pDX, IDC_bnPlay3, m_play3);
	DDX_Control(pDX, IDC_bnPause3, m_pause3);
	DDX_Control(pDX, IDC_bnStop3, m_stop3);
	//  DDX_Control(pDX, IDC_StaticSrcError, m_srcText);

	//  DDX_Control(pDX, IDC_PlayTime, m_playtime);
}

BEGIN_MESSAGE_MAP(CComposeWavPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_bnPlay1, IDC_bnPlay3, OnBnClickedPlay)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_bnPause1, IDC_bnPause3, OnBnClickedPause)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_bnStop1, IDC_bnStop3, OnBnClickedStop)

	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CComposeWavPlayerDlg ��Ϣ�������

BOOL CComposeWavPlayerDlg::OnInitDialog()
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

	m_hIconPlay= AfxGetApp()->LoadIconW(IDI_ICON2);
	m_hIconPause = AfxGetApp()->LoadIconW(IDI_ICON3);
	m_hIconStop = AfxGetApp()->LoadIconW(IDI_ICON4);

	m_play.SetIcon(m_hIconPlay);
	m_pause.SetIcon(m_hIconPause);
	m_stop.SetIcon(m_hIconStop);
	m_play2.SetIcon(m_hIconPlay);
	m_pause2.SetIcon(m_hIconPause);
	m_stop2.SetIcon(m_hIconStop);
	m_play3.SetIcon(m_hIconPlay);
	m_pause3.SetIcon(m_hIconPause);
	m_stop3.SetIcon(m_hIconStop);
	m_process.SetRange(0, 100);

	GetDlgItem(IDC_bnPause1)->EnableWindow(FALSE);
	GetDlgItem(IDC_bnPause2)->EnableWindow(FALSE);
	GetDlgItem(IDC_bnPause3)->EnableWindow(FALSE);
	GetDlgItem(IDC_bnStop1)->EnableWindow(FALSE);
	GetDlgItem(IDC_bnStop2)->EnableWindow(FALSE);
	GetDlgItem(IDC_bnStop3)->EnableWindow(FALSE);
	GetDlgItem(IDC_bnPlay1)->EnableWindow(FALSE);
	GetDlgItem(IDC_bnPlay2)->EnableWindow(FALSE);
	GetDlgItem(IDC_bnPlay3)->EnableWindow(FALSE);
	GetDlgItem(IDC_StaticSrcError)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_StaticLogError)->ShowWindow(SW_HIDE);


	//����������������������������������������������������������������������������������������������������������������������������������������������������������������
#ifdef _DEBUG
	/*GetDlgItem(IDC_StaticSrcError)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_StaticLogError)->EnableWindow(SW_SHOW);*/
#endif
	//����������������������������������������������������������������������������������������������������������������������������������������������������������������
	SetDlgItemText(IDC_Likely, _T(""));
	CRect rectPicture1, rectPicture2;

	/*
	���������򿪷���
	����ֵ-10��ʾģ���ļ���ʽ����ȷ���ߴ�ʧ�ܻ���ת��ʧ��
	����ֵ-20��ʾ��־�ļ���ʽ����ȷ���ߴ�ʧ�ܻ�����ȡwavʧ��
	����ֵ-30��ʾ�ϳ�ʧ��,����ģ���ļ�����־�ļ��ɲ��š��ɻ��Ʋ���
	����ֵ10��ʾ�ϳɳɹ�
	*/
	if (g_strSampleDir != _T("") && g_strLogDir != _T(""))
	{
		m_isComposed = InitOpen(g_strSampleDir, g_strLogDir);
		//m_isComposed����-10ʱ,�Ѿ�����InitOpenByLog,�ڴ˲���Ҫ����
		if (m_isComposed != -10)
		{
			m_picDraw1.GetClientRect(&rectPicture1);
			DrawWave(rectPicture1, m_dcSrcBuffer, m_SrcPaintData, m_SrcWavDataPointNum, m_SrcMaxValue);
			if (m_isComposed == 10 || m_isComposed == -30)
			{
				//10��ʾ�ϳɳɹ�
				m_picDraw2.GetClientRect(&rectPicture2);
				DrawWave(rectPicture2, m_dcLogBuffer, m_LogPaintData, m_LogWavDataPointNum, m_LogMaxValue);
				GetDlgItem(IDC_bnPlay1)->EnableWindow(TRUE);
				GetDlgItem(IDC_bnPlay2)->EnableWindow(TRUE);
				if (m_isComposed == 10)
					OnBnClickedPlay(IDC_bnPlay3);
				else
					OnBnClickedPlay(IDC_bnPlay1);
			}
			else if (m_isComposed == -20)
			{
				//-20��ʾ��־�ļ��򿪡���ʽ����ȡ����ȷ
				GetDlgItem(IDC_bnPlay1)->EnableWindow(TRUE);
				OnBnClickedPlay(IDC_bnPlay1);
			}
		}
		else
		{
			if (InitOpenByLog(g_strLogDir) != -1)
			{
				m_picDraw2.GetClientRect(&rectPicture2);
				DrawWave(rectPicture2, m_dcLogBuffer, m_LogPaintData, m_LogWavDataPointNum, m_LogMaxValue);
				OnBnClickedPlay(IDC_bnPlay2);
			}
		}
	}
	else if (g_strLogDir != _T(""))
	{
		m_isNoModFile = 1;
		reDrawWindow();
		if (InitOpenByLog(g_strLogDir) != -1)
		{
			m_picDraw2.GetClientRect(&rectPicture2);
			DrawWave(rectPicture2, m_dcLogBuffer, m_LogPaintData, m_LogWavDataPointNum, m_LogMaxValue);
			OnBnClickedPlay(IDC_bnPlay2);
		}
	}
	CString m_Temp;
	m_Temp.Format(_T("%d:%d:%d / %d:%d:%d"), m_Ch, m_Cm, m_Cs, m_Hour, m_Minute, m_Second);
	SetDlgItemText(IDC_PlayTime, m_Temp);	
	SetDlgItemText(IDC_StaticMod, _T("ģ\r\n��\r\n��\r\nƵ"));
	SetDlgItemText(IDC_StaticLog, _T("��\r\n־\r\n��\r\nƵ")); 
	
	if (m_SrcPaintData != NULL)
	{
		delete[]m_SrcPaintData;
		m_SrcPaintData = NULL;
	}
	if (m_LogPaintData != NULL)
	{
		delete[]m_LogPaintData;
		m_LogPaintData = NULL;
	}


	//system("start cmd /c D:\\Compose\\������־���Ź���0427\\ComposeWavPlayer20160424\\Debug\\SampleAbstracter.exe D:\\Compose\\workspace\\1s.wav");
	return FALSE;
}

void CComposeWavPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CComposeWavPlayerDlg::OnPaint()
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

		//// ���Ʋ���ͼ   
		CRect rectPicture1;
		CRect rectPicture2;
		m_picDraw1.GetClientRect(&rectPicture1);
		m_picDraw2.GetClientRect(&rectPicture2);
		m_picDraw1.GetDC()->BitBlt(rectPicture1.left, rectPicture1.top, rectPicture1.Width(), rectPicture1.Height(), &m_dcSrcBuffer, 0, 0, SRCCOPY);
		m_picDraw2.GetDC()->BitBlt(rectPicture2.left, rectPicture2.top, rectPicture2.Width(), rectPicture2.Height(), &m_dcLogBuffer, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

HCURSOR CComposeWavPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//---------------------------------------------------------------------------------------
void CComposeWavPlayerDlg::ConvertCStringToChar(CString m_srcCstring, char * &m_destChar)
{
	int m_len = WideCharToMultiByte(CP_ACP, 0, m_srcCstring, -1, NULL, 0, NULL, NULL);
	m_destChar = new char[m_len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_srcCstring, -1, m_destChar, m_len, NULL, NULL);
}

int CComposeWavPlayerDlg::ExtractWavFromMod(const CString m_SrcWavFile, const CString m_DesWavFile)
{
	//����ת��
	char *m_SrcModFileTempPath, *m_DesWavFileTempPath;
	ConvertCStringToChar(m_SrcWavFile, m_SrcModFileTempPath);
	ConvertCStringToChar(m_DesWavFile, m_DesWavFileTempPath);

	if (m_SrcPaintData != NULL)
	{
		delete[]m_SrcPaintData;
		m_SrcPaintData = NULL;
	}

	int m_WavDataBytes;
	FILE *fpr, *fpw;
	MyWave m_Wave;
	int m_SampleNum;
	int m_ReadCount = -1;
	fpr = fopen(m_SrcModFileTempPath, "rb");
	if (!fpr)
	{
#ifdef _DEBUG
		AfxMessageBox(_T("��ȡ�ļ�ʱ���ļ�ʧ��!"));
#endif
		fclose(fpr);
		goto FINISH;
	}

	fseek(fpr, -4, SEEK_END);
	fread(&m_WavDataBytes, 4, 1, fpr);

	if (m_WavDataBytes <= 0){
#ifdef _DEBUG
		AfxMessageBox(_T("��ȡ�ļ�������"));
#endif
		fclose(fpr);
		goto FINISH;
	}

	m_SampleNum = m_WavDataBytes / 2;
	m_SrcPaintData = new int16_t[m_SampleNum + 1];//��ͼ�ͺϳ�ʱ��Ҫʹ��
	m_SrcWavDataPointNum = m_SampleNum;////��ͼ�ͺϳ�ʱ��Ҫʹ��

	fseek(fpr, -(m_WavDataBytes + 4), SEEK_END);
	fread(m_SrcPaintData, 1, m_WavDataBytes, fpr);
	m_Wave.fileLen = m_WavDataBytes + sizeof(MyWave)-8;
	m_Wave.voiceLen = m_WavDataBytes;
	fclose(fpr);

	fpw = fopen(m_DesWavFileTempPath, "wb");
	if (!fpw)
	{
#ifdef _DEBUG
		AfxMessageBox(_T("д���ļ�ʱ���ļ�ʧ��!"));
#endif
		fclose(fpw);
		goto FINISH;
	}

	fwrite(&m_Wave, sizeof(MyWave), 1, fpw);
	m_ReadCount = fwrite(m_SrcPaintData, 1, m_WavDataBytes, fpw);
	fclose(fpw);
FINISH:

	delete[]m_SrcModFileTempPath;
	delete[]m_DesWavFileTempPath;
	m_SrcModFileTempPath = NULL;
	m_DesWavFileTempPath = NULL;
	return m_ReadCount;
}


int CComposeWavPlayerDlg::GetWavBufferFromLogWav(const CString m_SrcWavFile)
{
/*
����ֵ��ʾ��Log�ļ��ж�ȡ��pcm���������
 */
	char *m_DestWavFileTempPath;
	ConvertCStringToChar(m_SrcWavFile, m_DestWavFileTempPath);

	int m_FileBytes, m_WavDataBytes, m_SampleNum;
	FILE *fpr;
	int m_ReadCount = -1;
	if (m_LogPaintData != NULL)
	{
		delete[]m_LogPaintData;
		m_LogPaintData = NULL;
	}
	fpr = fopen(m_DestWavFileTempPath, "rb");
	if (!fpr)
	{
#ifdef _DEBUG
		MessageBox(_T("��") + m_SrcWavFile + _T("ʧ��"));
#endif
		goto FINISH;
	}

	fseek(fpr, 0, SEEK_END);
	m_FileBytes = ftell(fpr);

	if (m_FileBytes == 0)
	{
#ifdef _DEBUG
		MessageBox(m_SrcWavFile + _T("Ϊ���ļ�"));
#endif
		goto FINISH;
	}

	fseek(fpr, 40, SEEK_SET);
	fread(&m_WavDataBytes, 4, 1, fpr);
	if (m_WavDataBytes <= 0)
	{
#ifdef _DEBUG
		MessageBox(m_SrcWavFile + _T("�ļ����ݿ��ܱ���"));
#endif
		goto FINISH;
	}

	m_SampleNum = m_WavDataBytes / 2;
	m_LogPaintData = new int16_t[m_SampleNum + 1];

	fseek(fpr, 0, SEEK_CUR);
	m_ReadCount = fread(m_LogPaintData, 2, m_SampleNum, fpr);
	m_LogWavDataPointNum = m_ReadCount;
FINISH:

	fclose(fpr);
	delete[] m_DestWavFileTempPath;
	m_DestWavFileTempPath = NULL;
	return m_ReadCount;
}

int CComposeWavPlayerDlg::ComposeWavToTwoChannel(const CString m_SrcWavFile, float m_Pos, const CString m_DestWavFile,
	const CString m_NewWavFile)
{
	//�ɹ�����0��ʧ�ܷ���-1
	char *m_NewWavFileTempPath;
	ConvertCStringToChar(m_NewWavFile, m_NewWavFileTempPath);

	int16_t *m_Data = NULL;//�洢�ϲ�ʱ���ص�����
	int m_Result = -1;
	int m_DataPointNum[3];
	MyWave mywave;
	int m_Offset1 = (int)m_Pos * SAMPLE_FREQUENCY > 0 ? (int)m_Pos * SAMPLE_FREQUENCY : 0;
	m_DataPointNum[1] = m_LogWavDataPointNum;
	m_DataPointNum[0] = m_SrcWavDataPointNum - m_Offset1;

	if (m_DataPointNum[0] <= 0 || m_DataPointNum[1] <= 0)
	{
		m_Result = -1;
		goto FINISH;
	}

	//�����غϵĲ��������
	m_DataPointNum[2] = min(m_DataPointNum[0], m_DataPointNum[1]);
	m_Data = new int16_t[m_DataPointNum[2]*2];
	int i = 0;

	while (i < m_DataPointNum[2])
	{
		m_Data[2 * i] = m_SrcPaintData[m_Offset1 + i];
		m_Data[2 * i + 1] = m_LogPaintData[i];
		i++;
	}
	mywave.voiceLen = m_DataPointNum[2] * 4;
	mywave.fileLen = mywave.voiceLen + sizeof(MyWave) - 8;
	mywave.chnls = 2;
	mywave.dataRate = mywave.chnls * mywave.sampleRate * 2;
	mywave.dataBlock = 4;

	FILE *fpw;
	fpw = fopen(m_NewWavFileTempPath, "wb");
	if (!fpw)
	{
#ifdef _DEBUG
		MessageBox(_T("д������ʱ���ļ�����"));
#endif
		fclose(fpw);
		goto FINISH;
	}
	else
	{
		fwrite(&mywave, 1, sizeof(MyWave), fpw);
		m_Result = fwrite(m_Data, 2, m_DataPointNum[2]*2, fpw);
		fclose(fpw);
	}
FINISH:
	delete m_Data;
	m_Data = NULL;
	delete[] m_NewWavFileTempPath;
	m_NewWavFileTempPath = NULL;
	return m_Result;
}

void CComposeWavPlayerDlg::OnBnClickedPlay(UINT nID)
{
	//0��mod�� 1��log�� 2��compose
	CString m_Temp;
	GetDlgItemText(nID, m_Temp);
	int ID = nID - IDC_bnPlay1;

	
	if (m_Temp.Compare(_T("pause")) == 0)
	{	// �����ǰ״̬Ϊ��ͣ״̬
		m_WavPlay.ContinuePlay();
		switch (ID)
		{
		case 0:
		{
				  GetDlgItem(IDC_bnPause1)->EnableWindow(TRUE);
				  GetDlgItem(IDC_bnStop1)->EnableWindow(TRUE);
				  GetDlgItem(IDC_bnPlay1)->EnableWindow(FALSE);
				  SetDlgItemText(IDC_bnStop1, _T("play"));
				  SetDlgItemText(IDC_bnPause1, _T("play"));
				  break;

		}
		case 1:
		{
				  GetDlgItem(IDC_bnPause2)->EnableWindow(TRUE);
			      GetDlgItem(IDC_bnStop2)->EnableWindow(TRUE);
				  GetDlgItem(IDC_bnPlay2)->EnableWindow(FALSE);
				  SetDlgItemText(IDC_bnStop2, _T("play"));
				  SetDlgItemText(IDC_bnPause2, _T("play"));
			      break;


		}
		case 2:
		{
				  GetDlgItem(IDC_bnPause3)->EnableWindow(TRUE);
				  GetDlgItem(IDC_bnStop3)->EnableWindow(TRUE);
				  GetDlgItem(IDC_bnPlay3)->EnableWindow(FALSE);
				  SetDlgItemText(IDC_bnStop3, _T("play"));
				  SetDlgItemText(IDC_bnPause3, _T("play"));
				  break;
		}
		}
		SetDlgItemText(nID, _T("play"));
		SetTimer(0, 900, NULL);
		return;
	}
	

	SetDlgItemText(nID, _T("play"));
	CString m_FileName;
	switch (ID)
	{
	case 0:
	{
			  if (g_strSampleDir == _T(""))
			  {
#ifdef _DEBUG
				  MessageBox(_T("ģ����Ƶ·������"));
#endif
				  return;
			  }
			  m_FileName = g_strSampleDir.Left(g_strSampleDir.ReverseFind('.')) + _T(".wav");
			  GetDlgItem(IDC_bnPause1)->EnableWindow(TRUE);
			  GetDlgItem(IDC_bnStop1)->EnableWindow(TRUE);
			  GetDlgItem(IDC_bnPlay1)->EnableWindow(FALSE);
			  if (m_isComposed != -20)
			  {
				  GetDlgItem(IDC_bnPause2)->EnableWindow(FALSE);
				  GetDlgItem(IDC_bnStop2)->EnableWindow(FALSE);
				  GetDlgItem(IDC_bnPlay2)->EnableWindow(TRUE);
			  }

			  if (m_isComposed == 10)
			  {
				  GetDlgItem(IDC_bnPause3)->EnableWindow(FALSE);
				  GetDlgItem(IDC_bnStop3)->EnableWindow(FALSE);
				  GetDlgItem(IDC_bnPlay3)->EnableWindow(TRUE);
			  }
			  SetDlgItemText(IDC_bnPause1, _T("play"));
		      SetDlgItemText(IDC_bnStop1, _T("play"));
			  SetDlgItemText(IDC_bnPlay2, _T("stop"));
			  SetDlgItemText(IDC_bnStop2, _T("stop"));
			  SetDlgItemText(IDC_bnPause2, _T("stop"));
			  SetDlgItemText(IDC_bnPlay3, _T("stop"));
			  SetDlgItemText(IDC_bnStop3, _T("stop"));
			  SetDlgItemText(IDC_bnPause3, _T("stop"));
			  break;

	}
	case 1:
	{
			  if (g_strLogDir == _T(""))
			  {
#ifdef _DEBUG

				  MessageBox(_T("��־��Ƶ·������"));
#endif
				  return;
			  }
			  m_FileName = g_strLogDir;

			  GetDlgItem(IDC_bnPause2)->EnableWindow(TRUE);
			  GetDlgItem(IDC_bnStop2)->EnableWindow(TRUE);
			  GetDlgItem(IDC_bnPlay2)->EnableWindow(FALSE);
			 
			  if (m_isNoModFile != 1)
			  {
				  GetDlgItem(IDC_bnPlay1)->EnableWindow(TRUE);
				  GetDlgItem(IDC_bnPause1)->EnableWindow(FALSE);
				  GetDlgItem(IDC_bnStop1)->EnableWindow(FALSE);
			  }

			  if (m_isComposed == 10)
			  {
				  GetDlgItem(IDC_bnPlay3)->EnableWindow(TRUE);
				  GetDlgItem(IDC_bnPause3)->EnableWindow(FALSE);
				  GetDlgItem(IDC_bnStop3)->EnableWindow(FALSE);
			  }
			  SetDlgItemText(IDC_bnPause2, _T("play"));
			  SetDlgItemText(IDC_bnStop2, _T("play"));
			  SetDlgItemText(IDC_bnPlay1, _T("stop"));
			  SetDlgItemText(IDC_bnStop1, _T("stop"));
			  SetDlgItemText(IDC_bnPause1, _T("stop"));
			  SetDlgItemText(IDC_bnPlay3, _T("stop"));
			  SetDlgItemText(IDC_bnStop3, _T("stop"));
			  SetDlgItemText(IDC_bnPause3, _T("stop"));
			  break;

	}
	case 2:
	{
			  m_FileName = g_strLogDir.Left(g_strLogDir.ReverseFind('.')) + _T("_newComposed.wav");
			  if (m_FileName == _T(""))
			  {
#ifdef _DEBUG
				  MessageBox(_T("�ϳ���Ƶ·������"));
#endif
				  return;
			  }
			  GetDlgItem(IDC_bnPause2)->EnableWindow(FALSE);
			  GetDlgItem(IDC_bnStop2)->EnableWindow(FALSE);
			  GetDlgItem(IDC_bnPlay2)->EnableWindow(TRUE);
			  GetDlgItem(IDC_bnPlay1)->EnableWindow(TRUE);
			  GetDlgItem(IDC_bnPause1)->EnableWindow(FALSE);
			  GetDlgItem(IDC_bnStop1)->EnableWindow(FALSE);

			  GetDlgItem(IDC_bnPlay3)->EnableWindow(FALSE);
			  GetDlgItem(IDC_bnPause3)->EnableWindow(TRUE);
			  GetDlgItem(IDC_bnStop3)->EnableWindow(TRUE);

			  
			  SetDlgItemText(IDC_bnPause3, _T("play"));
			  SetDlgItemText(IDC_bnStop3, _T("play"));
			  SetDlgItemText(IDC_bnPlay1, _T("stop"));
			  SetDlgItemText(IDC_bnStop1, _T("stop"));
			  SetDlgItemText(IDC_bnPause1, _T("stop"));
			  SetDlgItemText(IDC_bnPlay2, _T("stop"));
			  SetDlgItemText(IDC_bnStop2, _T("stop"));
			  SetDlgItemText(IDC_bnPause2, _T("stop"));
			  break;

		}
		}
		m_WavPlay.Stop();
		m_WavPlay.Open(m_hWnd, m_FileName);
		m_WavPlay.Play();

		KillTimer(0);
		SetTimer(0, 900, NULL);

		m_Hour = m_Minute = m_Second = m_Ch = m_Cm = m_Cs = 0;
		m_Temp.Format(_T("%d:%d:%d / %d:%d:%d"), m_Ch, m_Cm, m_Cs, m_Hour, m_Minute, m_Second);
		SetDlgItemText(IDC_PlayTime, m_Temp);
		m_process.SetPos(0);
}

void CComposeWavPlayerDlg::OnBnClickedPause(UINT nID)
{
	CString m_Temp;
	int ID = nID - IDC_bnPause1;
	GetDlgItemText(nID, m_Temp);
	if (m_Temp.Compare(_T("play")) == 0)
	{
		m_WavPlay.Pause();
		SetDlgItemText(nID, _T("pause"));
		KillTimer(0);
		switch (ID)
		{
		case 0:
		{
				  GetDlgItem(IDC_bnPause1)->EnableWindow(FALSE);
				  GetDlgItem(IDC_bnStop1)->EnableWindow(TRUE);
				  GetDlgItem(IDC_bnPlay1)->EnableWindow(TRUE);
				  if (m_isComposed != -20)
				  {
					  GetDlgItem(IDC_bnPause2)->EnableWindow(FALSE);
					  GetDlgItem(IDC_bnStop2)->EnableWindow(FALSE);
					  GetDlgItem(IDC_bnPlay2)->EnableWindow(TRUE);
				  
				  }

				  if (m_isComposed == 10 )
				  {
					  GetDlgItem(IDC_bnPause3)->EnableWindow(FALSE);
					  GetDlgItem(IDC_bnStop3)->EnableWindow(FALSE);
					  GetDlgItem(IDC_bnPlay3)->EnableWindow(TRUE);
				  }
				  
				  SetDlgItemText(IDC_bnPlay1, _T("pause"));
				  SetDlgItemText(IDC_bnStop1, _T("pause"));

				  break;

		}
		case 1:
		{
				  GetDlgItem(IDC_bnPause2)->EnableWindow(FALSE);
				  GetDlgItem(IDC_bnStop2)->EnableWindow(TRUE);
				  GetDlgItem(IDC_bnPlay2)->EnableWindow(TRUE);
				  if (m_isComposed == 10)
				  {
				  
					  GetDlgItem(IDC_bnPause3)->EnableWindow(FALSE);
					  GetDlgItem(IDC_bnStop3)->EnableWindow(FALSE);
					  GetDlgItem(IDC_bnPlay3)->EnableWindow(TRUE);
				  }
				  if (m_isNoModFile != 1)
				  {
					  GetDlgItem(IDC_bnPause1)->EnableWindow(FALSE);
					  GetDlgItem(IDC_bnStop1)->EnableWindow(FALSE);
					  GetDlgItem(IDC_bnPlay1)->EnableWindow(TRUE);
				  }

				  SetDlgItemText(IDC_bnPlay2, _T("pause"));
				  SetDlgItemText(IDC_bnStop2, _T("pause"));
				  break;


		}
		case 2:
		{

				  GetDlgItem(IDC_bnPause3)->EnableWindow(FALSE);
				  GetDlgItem(IDC_bnStop3)->EnableWindow(TRUE);
				  GetDlgItem(IDC_bnPlay3)->EnableWindow(TRUE);
				  GetDlgItem(IDC_bnPause1)->EnableWindow(FALSE);
				  GetDlgItem(IDC_bnStop1)->EnableWindow(FALSE);
				  GetDlgItem(IDC_bnPlay1)->EnableWindow(TRUE);
				  GetDlgItem(IDC_bnPause2)->EnableWindow(FALSE);
				  GetDlgItem(IDC_bnStop2)->EnableWindow(FALSE);
				  GetDlgItem(IDC_bnPlay2)->EnableWindow(TRUE);
				  SetDlgItemText(IDC_bnPlay3, _T("pause"));
				  SetDlgItemText(IDC_bnStop3, _T("pause"));
				  break;
		}

		}
	}
}

void CComposeWavPlayerDlg::OnBnClickedStop(UINT nID)
{
	CString m_Temp;
	int ID = nID - IDC_bnStop1;
	GetDlgItemText(nID, m_Temp);
	KillTimer(0);
	m_WavPlay.Stop();
	if (m_Temp.Compare(_T("play")) == 0 || m_Temp.Compare(_T("pause")) == 0)
	{
		if (m_isNoModFile != 1)
		{
			GetDlgItem(IDC_bnPause1)->EnableWindow(FALSE);
			GetDlgItem(IDC_bnStop1)->EnableWindow(FALSE);
			GetDlgItem(IDC_bnPlay1)->EnableWindow(TRUE);
		}
		if (m_isComposed != -20)
		{
			GetDlgItem(IDC_bnPause2)->EnableWindow(FALSE);
			GetDlgItem(IDC_bnStop2)->EnableWindow(FALSE);
			GetDlgItem(IDC_bnPlay2)->EnableWindow(TRUE);
		}
		if (m_isComposed == 10)
		{
			GetDlgItem(IDC_bnPause3)->EnableWindow(FALSE);
			GetDlgItem(IDC_bnStop3)->EnableWindow(FALSE);
			GetDlgItem(IDC_bnPlay3)->EnableWindow(TRUE);
		}
		switch (ID)
		{
		case 0:
		{
				  SetDlgItemText(IDC_bnPlay1, _T("stop"));
				  SetDlgItemText(IDC_bnStop1, _T("stop"));

				  break;
		}
		case 1:
		{
				
				  SetDlgItemText(IDC_bnPlay2, _T("stop"));
				  SetDlgItemText(IDC_bnStop2, _T("stop"));
				  break;
		}
		case 2:
		{
				  SetDlgItemText(IDC_bnPlay3, _T("stop"));
				  SetDlgItemText(IDC_bnStop3, _T("stop"));
				  break;
		}

		}

	}
	m_Hour = m_Minute = m_Second = m_Ch = m_Cm = m_Cs = 0;
	m_Temp.Format(_T("%d:%d:%d / %d:%d:%d"), m_Ch, m_Cm, m_Cs, m_Hour, m_Minute, m_Second);
	SetDlgItemText(IDC_PlayTime, m_Temp);
	this->m_process.SetPos(0);

}




void CComposeWavPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
		CString m_Temp;
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		m_Totaltime = m_WavPlay.Info(MCI_STATUS_LENGTH);
		m_Currenttime = m_WavPlay.Info(MCI_STATUS_POSITION);
		if (nIDEvent == 0)
		{
			
			if (m_Currenttime >= m_Totaltime)
			{
				m_WavPlay.SeekTo(0);
				OnBnClickedStop(IDC_bnStop1);
				OnBnClickedStop(IDC_bnStop2);
				OnBnClickedStop(IDC_bnStop3);
				return;
			}

			m_Totaltime = m_Totaltime / 1000;
			m_Hour = m_Totaltime / 3600;
			m_Minute = (m_Totaltime / 60) % 60;
			m_Second = m_Totaltime % 60;
			m_Currenttime = m_Currenttime / 1000;

			m_process.SetPos(((m_Currenttime + 1) * 100) / m_Totaltime);
			m_Ch = (m_Currenttime+1) / 3600;
			m_Cm = ((m_Currenttime+1) / 60) % 60;
			m_Cs = (m_Currenttime+1) % 60;
			m_Temp.Format(_T("%d:%d:%d / %d:%d:%d"), m_Ch, m_Cm, m_Cs, m_Hour, m_Minute, m_Second);
			SetDlgItemText(IDC_PlayTime, m_Temp);
		}
	CDialogEx::OnTimer(nIDEvent);
}


void CComposeWavPlayerDlg::DrawWave(CRect &rectPicture, CDC &m_dcBuffer, int16_t *&m_Data, const int m_WavDataPointNum, const int m_MaxValue)
{
	if (m_dcBuffer.m_hDC != NULL)		//��DC�Ѿ�������ɾ����
		m_dcBuffer.DeleteDC();
	if (m_Data == NULL)
		return;

	InitDC(m_dcBuffer, rectPicture);		//��ʼ��DC
	float fDeltaX;     // x������������ͼ����������   
	float fDeltaY;     // y��ÿ���߼���λ��Ӧ������ֵ   
	int nX;      // ������ʱ���ڴ洢��ͼ��ĺ�����   
	int nY;      // ������ʱ���ڴ洢��ͼ���������   
	CPen newPen1;       // ���ڴ����»��� 
	CPen newPen2;     // ���ڴ�Ż��ظ�Ƭ�εĻ���  
	CBrush newBrush;   // ���ڴ����»�ˢ   
	int step = 1;//��ͼ�Ĳ���
	// ����fDeltaX��fDeltaY   
	fDeltaY = (float)rectPicture.Height() / (2 * (m_MaxValue + 5));

	// ������ɫ�»�ˢ   
	newBrush.CreateSolidBrush(RGB(0, 0, 0));
	// ѡ���»�ˢ�������ɻ�ˢ��ָ�뱣�浽pOldBrush   
	m_dcBuffer.SelectObject(&newBrush);
	// �Ժ�ɫ��ˢΪ��ͼ�ؼ�����ɫ���γɺ�ɫ����   
	m_dcBuffer.Rectangle(rectPicture);
	// ɾ���»�ˢ   
	newBrush.DeleteObject();

	// ����ʵ�Ļ���1���ֶ�Ϊ1����ɫΪ��ɫ   
	newPen1.CreatePen(PS_SOLID, 1, RGB(102, 255, 51));
	// ����ʵ�Ļ���2���ظ�Ƭ�Σ��ֶ�Ϊ1����ɫΪ������
	newPen2.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_dcBuffer.SelectObject(&newPen1);
	int m_MaxPointNum;
	m_MaxPointNum = MAX(m_SrcWavDataPointNum, m_LogWavDataPointNum);
	int m_Begin = m_fPos * SAMPLE_FREQUENCY > 0 ? m_fPos * SAMPLE_FREQUENCY : 0;
	int m_End = min(m_Begin + m_LogWavDataPointNum, m_SrcWavDataPointNum);
	if (m_WavDataPointNum > NORMALDRAWNUM)
		step = MAX(int((m_WavDataPointNum / NORMALDRAWNUM)), 1);
	if (m_WavDataPointNum == m_MaxPointNum)
	{//Ҫ���ǲ���
		fDeltaX = (float)rectPicture.Width() / m_WavDataPointNum;

		m_dcBuffer.MoveTo(rectPicture.left, rectPicture.bottom);

		if (m_SrcWavDataPointNum >= m_LogWavDataPointNum && m_fLikely > ZERO)
		{//��ģ���ļ�
			for (int i = 0; i < m_WavDataPointNum; i = i + step)
			{
				m_dcBuffer.SelectObject(&newPen1);
			
				if (i >= m_Begin && i < m_End)
				{
					m_dcBuffer.SelectObject(&newPen2);
					nX = (int)(i * fDeltaX);
					nY = rectPicture.Height() / 2 - (int)(m_Data[i] * fDeltaY);
					m_dcBuffer.LineTo(nX, nY);
					continue;
				}
				nX = (int)(i * fDeltaX);
				nY = rectPicture.Height() / 2 - (int)(m_Data[i] * fDeltaY);
				m_dcBuffer.LineTo(nX, nY);
			}
		}
		else if (m_SrcWavDataPointNum < m_LogWavDataPointNum || m_fLikely <= ZERO)
		{//����־�ļ�����ʱģ���ļ�С����־�ļ�
		//���߻���ƥ���ģ���ļ�
		//�������߳�����Ȳ�ƥ���ģ������־
			for (int i = 0; i < m_WavDataPointNum; i = i + step)
			{
				nX = (int)(i * fDeltaX);
				nY = rectPicture.Height() / 2 - (int)(m_Data[i] * fDeltaY);
				m_dcBuffer.LineTo(nX, nY);
			}
		}
	}
	else if (m_WavDataPointNum == MIN(m_SrcWavDataPointNum, m_LogWavDataPointNum))
	{
		float m_XOffset = 0;
		m_XOffset = (float)rectPicture.Width() * (m_MaxPointNum - m_WavDataPointNum) / 2 / m_MaxPointNum;
		fDeltaX = (float)rectPicture.Width() / MAX(m_SrcWavDataPointNum, m_LogWavDataPointNum);
		m_dcBuffer.MoveTo(rectPicture.left + m_XOffset, rectPicture.bottom);
		if (m_SrcWavDataPointNum >= m_LogWavDataPointNum && m_fLikely > ZERO)
		{//����־�ļ�,��ʱ����ƥ��,��־�ļ�����λ�ø���ģ�����
			m_dcBuffer.SelectObject(&newPen2);
			for (int i = 0; i < m_WavDataPointNum; i = i + step)
			{
				nX = (int)(i * fDeltaX + m_XOffset);
				nY = rectPicture.Height() / 2 - (int)(m_Data[i] * fDeltaY);
				m_dcBuffer.LineTo(nX, nY);
			}
		}
		else if (m_SrcWavDataPointNum >= m_LogWavDataPointNum && m_fLikely <= ZERO)
		{
			//����־�ļ�,���߲�ƥ�䣬������
			m_dcBuffer.MoveTo(rectPicture.left, rectPicture.bottom);
			fDeltaX = (float)rectPicture.Width() / m_WavDataPointNum;
			m_dcBuffer.SelectObject(&newPen1);
			for (int i = 0; i < m_WavDataPointNum; i = i + step)
			{
				nX = (int)(i * fDeltaX);
				nY = rectPicture.Height() / 2 - (int)(m_Data[i] * fDeltaY);
				m_dcBuffer.LineTo(nX, nY);
			}

		}
		else if (m_fLikely > ZERO)
		{//��ģ���ļ�,��ʱ�����������ģ�����־�̣�����������
			for (int i = 0; i < m_WavDataPointNum; i = i + step)
			{
				m_dcBuffer.SelectObject(&newPen1);
				if (i >= m_Begin && i < m_End)
				{
					m_dcBuffer.SelectObject(&newPen2);
					nX = (int)(i * fDeltaX+m_XOffset);
					nY = rectPicture.Height() / 2 - (int)(m_Data[i] * fDeltaY);
					m_dcBuffer.LineTo(nX, nY);
					continue;
				}
				nX = (int)(i * fDeltaX);
				nY = rectPicture.Height() / 2 - (int)(m_Data[i] * fDeltaY);
				m_dcBuffer.LineTo(nX, nY);
			}
			
		}
		else
		{
			//��ģ���ļ�,��ʱ�����������ģ�����־�̣������߲�����
			m_dcBuffer.MoveTo(rectPicture.left, rectPicture.bottom);
			fDeltaX = (float)rectPicture.Width() / m_WavDataPointNum;
			m_dcBuffer.SelectObject(&newPen1);
			for (int i = 0; i < m_WavDataPointNum; i = i + step)
			{
				nX = (int)(i * fDeltaX);
				nY = rectPicture.Height() / 2 - (int)(m_Data[i] * fDeltaY);
				m_dcBuffer.LineTo(nX, nY);
			}
		}
	}

	// ɾ������   
	newPen1.DeleteObject();
	newPen2.DeleteObject();
	delete[]m_Data;
	m_Data = NULL;
}

int CComposeWavPlayerDlg::InitOpen(const CString m_ModFilePath, const CString m_LogFilePath)
{
	/*
	���������򿪷���
	����ֵ-10��ʾģ���ļ���ʽ����ȷ���ߴ�ʧ�ܻ���ת��ʧ��
	����ֵ-20��ʾ��־�ļ���ʽ����ȷ���ߴ�ʧ�ܻ�����ȡwavʧ��
	����ֵ-30��ʾ�ϳ�ʧ��,����ģ���ļ�����־�ļ��ɲ��š��ɻ��Ʋ���
	����ֵ10��ʾ�ϳɳɹ�
	*/
	CFile fpr;
	CFileException ex;
	int returnType = 10;
	if ((m_ModFilePath.Right(3)).MakeLower() != _T("mod"))
	{
#ifdef _DEBUG
		MessageBox(_T("��һ���������Ͳ���ȷ������������"));
#endif
		WriteFont(IDC_StaticSrcError, _T("����\n     ��һ������Ӧ��������ģ���ļ�����·����"), m_newFontSrc);
		m_isNoModFile = 1;
		//InitOpenByLog(m_LogFilePath);
		return -10;
	}


	if (!fpr.Open(m_ModFilePath, CFile::modeRead, &ex))
	{
#ifdef _DEBUG
		ex.ReportError();
#endif
		fpr.Abort();
		WriteFont(IDC_StaticSrcError, _T("����\n     �޷���ģ���ļ�������·��"), m_newFontSrc);
		m_isNoModFile = 1;
		return -10;
	}
	fpr.Close();


	if (!fpr.Open(m_LogFilePath, CFile::modeRead, &ex))
	{

		fpr.Abort();
#ifdef _DEBUG
		ex.ReportError();
#endif
		//�޸�ʱ��20160408
		WriteFont(IDC_StaticLogError, _T("����\n     �޷�����־�ļ�������·��"), m_newFontLog);
		returnType = -20;
	}
	else
		fpr.Close();

	if (returnType != -20 && !isWavFile(m_LogFilePath))
	{
#ifdef _DEBUG
		MessageBox(_T("�ڶ����������Ͳ���ȷ������������"));
#endif
		WriteFont(IDC_StaticLogError, _T("����\n     �ڶ�������Ӧ����������־WAV�����ļ�"), m_newFontLog);
		returnType = -20;
	}
	//������������������������������������������������������������������������������������������������������������������������������������������������������������
	//��mod��ȡwav
	//������������������������������������������������������������������������������������������������������������������������������������������������������������

	int m_sFlag = -1;
	m_TempWavPath = m_ModFilePath.Left(m_ModFilePath.ReverseFind('.')) + _T(".wav");
	m_sFlag = ExtractWavFromMod(m_ModFilePath, m_TempWavPath);
	if (m_sFlag <= 0)
	{
#ifdef _DEBUG
		MessageBox(_T("δ�ܳɹ���mod�ļ�ת��Ϊwav�ļ�"));
#endif
		WriteFont(IDC_StaticSrcError, _T("����\n     ��ģ���ļ���ȡwav����ʧ�ܣ�"), m_newFontSrc);
		m_isNoModFile = 1;
		//InitOpenByLog(m_LogFilePath);
		return -10;
	}
	//������������������������������������������������������������������������������������������������������������������������������������������������������������
	//��Log��ȡwav
	//������������������������������������������������������������������������������������������������������������������������������������������������������������
	if (returnType != -20 && GetWavBufferFromLogWav(m_LogFilePath) <= 0)
	{
		WriteFont(IDC_StaticLogError, _T("����\n     ����־�ļ���ȡwav����ʧ�ܣ�"), m_newFontLog);
		returnType = -20;
	}

	//������������������������������������������������������������������������������������������������������������������������������������������������������������
	//�ϳɲ���,�޸�ʱ��20160408
	//�����е�����˵��ģ���ļ�ת��wav�ɹ�
	//log������ȡ�ɹ��ſ���ִ�кϳɲ���
	//������������������������������������������������������������������������������������������������������������������������������������������������������������
	if (returnType != -20)
	{
		m_TempComposedWavPath = m_LogFilePath.Left(m_LogFilePath.ReverseFind('.')) + _T("_newComposed.wav");

		fpr.Open(m_LogFilePath, CFile::modeRead);
		fpr.Seek(-252, CFile::end);
		fpr.Read(&m_fLikely, 4);

		fpr.Seek(76, CFile::current);
		fpr.Read(&m_fPos, 4);
		fpr.Close();

		int m_Result = -1;
		CString m_Temp;
		if (m_fPos >= 0 && m_fLikely > ZERO && m_fLikely < 1.0001)
		{
			m_Result = ComposeWavToTwoChannel(m_TempWavPath, m_fPos, m_LogFilePath, m_TempComposedWavPath);
			if (m_Result <= ZERO)
			{
				m_Temp.Format(_T("�������ȶ��ļ��ϳ�ʧ�ܣ�"));
				SetDlgItemText(IDC_Likely, m_Temp);
				returnType = -30;
			}
			else
			{
				m_Temp.Format(_T("�������ȶ��ļ��Ѻϳɣ� ƥ��λ��Ϊ��%.3fs   ���ƶ�Ϊ�� %.3f"), m_fPos, m_fLikely);
				SetDlgItemText(IDC_Likely, m_Temp);
				//OnBnClickedPlay(IDC_bnPlay3);
			}
		}
		else
			returnType = -30;
		m_LogMaxValue = GetMaxValue(m_LogPaintData, m_LogWavDataPointNum);
	}
	m_SrcMaxValue = GetMaxValue(m_SrcPaintData, m_SrcWavDataPointNum);
	return returnType;
}

void CComposeWavPlayerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	KillTimer(0);
	CFile DelFile;
	if (DelFile.Open(m_TempWavPath, CFile::modeRead) != 0){
		DelFile.Close();
		DelFile.Remove(m_TempWavPath);
	}
	if (DelFile.Open(m_TempComposedWavPath, CFile::modeRead) != 0){
		DelFile.Close();
		DelFile.Remove(m_TempComposedWavPath);
	}
}

int16_t CComposeWavPlayerDlg::GetMaxValue(int16_t *m_Data, int length)
{
	int16_t m_TempMax = 0;
	if (m_Data != NULL)
	{
		for (int i = 0; i < length; i++)
		{
			if (m_TempMax < ABS(m_Data[i]))
				m_TempMax = ABS(m_Data[i]);
		}
	}
	return m_TempMax;
}
void CComposeWavPlayerDlg::InitDC(CDC &dc, CRect rect)		//��ʼ���ڴ�DC
{
	if (dc.m_hDC != NULL)
		dc.DeleteDC();

	//��ʼ��DC��������ɺ��ʵĴ�С��ͨ����һ��ָ����С��λͼѡ����ʵ�֣�
	CBitmap bmpTemp;
	dc.CreateCompatibleDC(GetDC());
	bmpTemp.CreateCompatibleBitmap(GetDC(), rect.Width(), rect.Height());
	dc.SelectObject(&bmpTemp);
	bmpTemp.DeleteObject();
}
void CComposeWavPlayerDlg::SetFont(CString m_style, int m_size, UINT nID, CFont &m_font)
{
	m_font.DeleteObject();
	m_font.CreatePointFont(m_size, m_style);
	GetDlgItem(nID)->SetFont(&m_font);
}
HBRUSH CComposeWavPlayerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_StaticSrcError:
	case IDC_StaticLogError:
		pDC->SetTextColor(RGB(255, 0, 0));
		break;
	}
	return hbr;
}


int CComposeWavPlayerDlg::InitOpenByLog(const CString m_LogFilePath)
{
	/*
	*	-1 ��ʾ��־�ļ���ʧ�ܻ�����־�ļ����ݶ�ȡʧ�ܣ� 1��ʾ��־�ļ����Դ�
	*	�޸�ʱ��2016/04/08
	*/
	CFile fpr;
	CFileException ex;

	/*
	������־�ļ��Ƿ��ܴ�
	*/
	if (!fpr.Open(m_LogFilePath, CFile::modeRead, &ex))
	{
		fpr.Abort();
#ifdef _DEBUG
		ex.ReportError();
#endif
		WriteFont(IDC_StaticLogError, _T("����\n     �޷�����־�ļ�������·��"), m_newFontLog);
		return -1;
	}
	fpr.Close();

	/*
	������־�ļ���ʽ�Ƿ�Ϊwav
	*/
	if (!isWavFile(m_LogFilePath))
	{
#ifdef _DEBUG
		MessageBox(_T("�������Ͳ���ȷ������������"));
#endif
		WriteFont(IDC_StaticLogError, _T("����\n     ����Ӧ����������־WAV�����ļ�"), m_newFontLog);
		return -1;
	}

	fpr.Open(m_LogFilePath, CFile::modeRead);
	fpr.Seek(-252, CFile::end);
	fpr.Read(&m_fLikely, 4);

	fpr.Seek(76, CFile::current);
	fpr.Read(&m_fPos, 4);
	fpr.Close();

	int m_Result = -1;
	CString m_Temp;


	m_Result = GetWavBufferFromLogWav(m_LogFilePath);
	if (m_Result <= ZERO)
	{
		WriteFont(IDC_StaticLogError, _T("����\n     ��־�ļ����ݲ���������������"), m_newFontLog);
		return -1;
	}
	//OnBnClickedPlay(IDC_bnPlay2);

	m_LogMaxValue = GetMaxValue(m_LogPaintData, m_LogWavDataPointNum);
	return 1;
}

void CComposeWavPlayerDlg::WriteFont(UINT nID, CString words, CFont &m_font)
{
	GetDlgItem(nID)->ShowWindow(SW_SHOW);
	GetDlgItem(nID)->SetWindowTextW(words);
	SetFont(_T("����"), 150, nID, m_font);
}

bool CComposeWavPlayerDlg::isWavFile(const CString m_LogFilePath)
{
	CFile fpr;
	char fileTypeFlag[4];
	fpr.Open(m_LogFilePath, CFile::modeRead);
	fpr.Seek(8, CFile::begin);
	fpr.Read(&fileTypeFlag, 4);
	fpr.Close();
	if (fileTypeFlag[0] == 'W' && fileTypeFlag[1] == 'A' && fileTypeFlag[2] == 'V' && fileTypeFlag[3]=='E')
		return true;
	else
		return false;
}

void CComposeWavPlayerDlg::ChangeSize(UINT srcID, UINT destID)
{
	CWnd *pWnd = GetDlgItem(srcID);   //��ȡ�ؼ����;
	if (pWnd)  //�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ����
	{

		CRect destRect, srcRect;  //��ȡĿ�Ŀؼ�
		GetDlgItem(destID)->GetWindowRect(&destRect);
		ScreenToClient(&destRect); //���ؼ�λ��ת��Ϊ�ڶԻ����е���������
		GetDlgItem(srcID)->GetWindowRect(&srcRect);
		ScreenToClient(&srcRect); //���ؼ�λ��ת��Ϊ�ڶԻ����е���������
		if (srcID != IDC_Process && srcID != IDC_PlayTime)
			pWnd->MoveWindow(destRect.left, destRect.top, srcRect.Width(), srcRect.Height(),1);
		if (srcID == IDC_Process)
			pWnd->MoveWindow(destRect.left - 8, destRect.bottom + 15, srcRect.Width(), srcRect.Height());
		else if (srcID == IDC_PlayTime)
			pWnd->MoveWindow(destRect.right - srcRect.Width() - 8, destRect.top - 15, srcRect.Width(), srcRect.Height());
		
	}
}


void CComposeWavPlayerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������

	if (m_isComposed == -1 && nType != SIZE_MINIMIZED)
	{
		
		ChangeSize(IDC_Process,IDC_WAVE_DRAW1);
		//GetDlgItem(IDC_Process)->SetFocus();
		ChangeSize(IDC_WAVE_DRAW2, IDC_WAVE_DRAW1);
		ChangeSize(IDC_PlayTime, IDC_Process);
		ChangeSize(IDC_bnPlay2, IDC_bnPlay1);
		ChangeSize(IDC_bnPause2, IDC_bnPause1);
		ChangeSize(IDC_bnStop2, IDC_bnStop1);
		ChangeSize(IDC_StaticLog, IDC_StaticMod);
		ChangeSize(IDC_StaticLogError, IDC_StaticSrcError);
		//SetFocus();

	}
}
void CComposeWavPlayerDlg::reDrawWindow()
{
	GetDlgItem(IDC_WAVE_DRAW1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_StaticSrcError)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_StaticMod)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_bnPlay1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_bnPause1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_bnStop1)->ShowWindow(SW_HIDE);
	CRect window;
	GetClientRect(&window);
	CRect newWindow(0, 0, window.Width() + 8, window.bottom * 0.63);
	CWnd::SetWindowPos(NULL, 0, 0, newWindow.Width(), newWindow.Height(), SWP_NOZORDER | SWP_NOMOVE);
}
void CComposeWavPlayerDlg::DrawTime(CString text)
{
}


BOOL CComposeWavPlayerDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CDialogEx::OnEraseBkgnd(pDC);
	//return TRUE;
}


void CComposeWavPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (pScrollBar->GetSafeHwnd() == this->m_process.GetSafeHwnd())
	{
		if (this->m_process)
		{
			DWORD time = m_WavPlay.Info(MCI_STATUS_LENGTH);
			DWORD currenttime;
			currenttime = time*(this->m_process.GetPos()) / 100;
			m_WavPlay.SeekTo(currenttime);
			m_WavPlay.Play();
			CString m_Temp;
			GetDlgItemText(IDC_bnPause1, m_Temp);
			if (m_Temp.Compare(_T("pause")) == 0)
			{

				SetDlgItemText(IDC_bnPause1, _T("play"));
				GetDlgItem(IDC_bnPause1)->EnableWindow(TRUE);
				GetDlgItem(IDC_bnStop1)->EnableWindow(TRUE);
				GetDlgItem(IDC_bnPlay1)->EnableWindow(FALSE);
				return;
			}
			GetDlgItemText(IDC_bnPause2, m_Temp);
			if (m_Temp.Compare(_T("pause")) == 0)
			{
				SetDlgItemText(IDC_bnPause2, _T("play"));
				GetDlgItem(IDC_bnPause2)->EnableWindow(TRUE);
				GetDlgItem(IDC_bnStop2)->EnableWindow(TRUE);
				GetDlgItem(IDC_bnPlay2)->EnableWindow(FALSE);
				return;
			}
			GetDlgItemText(IDC_bnPause3, m_Temp);
			if (m_Temp.Compare(_T("pause")) == 0)
			{
				SetDlgItemText(IDC_bnPause3, _T("play"));
				GetDlgItem(IDC_bnPause3)->EnableWindow(TRUE);
				GetDlgItem(IDC_bnStop3)->EnableWindow(TRUE);
				GetDlgItem(IDC_bnPlay3)->EnableWindow(FALSE);
				return;
			}
		}
	}
	else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}
