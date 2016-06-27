
// ComposeWavPlayer.cpp : ����Ӧ�ó��������Ϊ��
//

//#include "stdafx.h"
#include "ComposeWavPlayer.h"
#include "ComposeWavPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CComposeWavPlayerApp
CString g_strSampleDir;
CString g_strLogDir;
BEGIN_MESSAGE_MAP(CComposeWavPlayerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CComposeWavPlayerApp ����
CComposeWavPlayerApp::CComposeWavPlayerApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}


// Ψһ��һ�� CComposeWavPlayerApp ����

CComposeWavPlayerApp theApp;


// CComposeWavPlayerApp ��ʼ��

BOOL CComposeWavPlayerApp::InitInstance()
{

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	
	CWinApp::InitInstance();
	LPTSTR cmd = ::GetCommandLine();
	int argc = 0;
	WCHAR  * const *argv;
	argv = ::CommandLineToArgvW(cmd, &argc);
	if (argc == 3)
	{
		bool flag1 = true, flag2 = true;
		g_strSampleDir = argv[1];
		g_strLogDir = argv[2];
	}
	else if (argc == 2)
	{
		g_strLogDir = argv[1];
		g_strSampleDir = "";
		//system("start cmd /c D:\\Compose\\������־���Ź���0427\\ComposeWavPlayer20160424\\Debug\\SampleAbstracter.exe D:\\Compose\\workspace\\1s.wav");
		//return FALSE;
		CFile fpr;
		if (!fpr.Open(g_strLogDir, CFile::modeRead))
		{
			AfxMessageBox(_T("��־�ļ��޷���"));
			return FALSE;
		}
		fpr.Close();
	}
	else
	{
		AfxMessageBox(_T("��������ȷ��ӦΪ��Դ(ģ��)�ļ�·�� ��־�ļ�·��\n"));
		return FALSE;
	}


	AfxEnableControlContainer();


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CComposeWavPlayerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

