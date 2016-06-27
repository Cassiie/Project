#include "stdafx.h"
#include "WavePlay.h"
#include<stdlib.h>
WavePlay::WavePlay(void)
{
	MCIOpenParms.lpstrDeviceType = _T("waveaudio");
	//通过指定设备名打开设备

	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE, (DWORD)(LPVOID)&MCIOpenParms))
	{
		char buffer[256];
		mciGetErrorString(dwReturn, (LPWSTR)buffer, 256);
		AfxMessageBox((LPWSTR)buffer);
	}
	DeviceID = MCIOpenParms.wDeviceID;
}

WavePlay::~WavePlay(void)
{
}

void WavePlay::Open(HWND hwnd, CString StrFilePath)
{
	this->hWnd = hwnd;
	mciSendCommand(DeviceID, MCI_CLOSE, 0, 0);
	MCIOpenParms.lpstrElementName = StrFilePath;

	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&MCIOpenParms))
	{
		char buffer[256];
		mciGetErrorString(dwReturn, (LPWSTR)buffer, 256);
		AfxMessageBox((LPWSTR)buffer);
	}
	DeviceID = MCIOpenParms.wDeviceID;
}

DWORD WavePlay::Info(DWORD item)
{
	MCI_STATUS_PARMS MCIStatusParms;
	MCIStatusParms.dwItem = item;
	MCIStatusParms.dwReturn = 0;
	mciSendCommand(DeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&MCIStatusParms);
	return MCIStatusParms.dwReturn;
}

void WavePlay::Play()
{
	MCI_PLAY_PARMS MCIPlayParms;
	MCIPlayParms.dwCallback = (DWORD)hWnd;
	MCIPlayParms.dwFrom = 0;
	mciSendCommand(DeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&MCIPlayParms);
}

void WavePlay::Pause()
{
	mciSendCommand(DeviceID, MCI_PAUSE, 0, 0);
}
void WavePlay::ContinuePlay()
{
	mciSendCommand(DeviceID, MCI_RESUME, 0, 0);
}
void WavePlay::Stop()
{
	mciSendCommand(DeviceID, MCI_STOP, 0, 0);
	mciSendCommand(DeviceID, MCI_CLOSE, 0, 0);
}


void WavePlay::SeekTo(DWORD to)
{
	MCI_SEEK_PARMS MCISeek;
	MCISeek.dwTo = to;
	mciSendCommand(DeviceID, MCI_SEEK, MCI_TO, (DWORD)&MCISeek);
}
