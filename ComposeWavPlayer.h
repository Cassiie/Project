
// ComposeWavPlayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

//#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CComposeWavPlayerApp: 
// �йش����ʵ�֣������ ComposeWavPlayer.cpp
//

class CComposeWavPlayerApp : public CWinApp
{
private:
	CComposeWavPlayerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CComposeWavPlayerApp theApp;
