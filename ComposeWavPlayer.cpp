
// ComposeWavPlayer.cpp : 定义应用程序的类行为。
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


// CComposeWavPlayerApp 构造
CComposeWavPlayerApp::CComposeWavPlayerApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}


// 唯一的一个 CComposeWavPlayerApp 对象

CComposeWavPlayerApp theApp;


// CComposeWavPlayerApp 初始化

BOOL CComposeWavPlayerApp::InitInstance()
{

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	
	CWinApp::InitInstance();
	//LPTSTR cmd = ::GetCommandLine();
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
		//system("start cmd /c D:\\Compose\\样例日志播放工具0427\\ComposeWavPlayer20160424\\Debug\\SampleAbstracter.exe D:\\Compose\\workspace\\1s.wav");
		//return FALSE;
		CFile fpr;
		if (!fpr.Open(g_strLogDir, CFile::modeRead))
		{
			AfxMessageBox(_T("日志文件无法打开"));
			return FALSE;
		}
		fpr.Close();
	}
	else
	{
		AfxMessageBox(_T("参数不正确，应为：源(模板)文件路径 日志文件路径\n"));
		return FALSE;
	}


	AfxEnableControlContainer();


	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CComposeWavPlayerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

