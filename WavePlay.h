#pragma once
#include "stdafx.h"
#include <windows.h>
#include "mmsystem.h"
#include <digitalv.h>
#pragma comment(lib, "winmm.lib")
class WavePlay
{
public:
	WavePlay(void);
	~WavePlay(void);
	HWND hWnd;
	DWORD DeviceID;
	MCI_OPEN_PARMS MCIOpenParms;
	void Open(HWND hwnd, CString StrFilePath);
	DWORD Info(DWORD Item);
	void Play();
	void Pause();
	void ContinuePlay();
	void Stop();
	void SeekTo(DWORD To);
};

