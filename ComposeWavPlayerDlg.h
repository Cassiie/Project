
// ComposeWavPlayerDlg.h : 头文件
//
#pragma once
#include "MyWave.h"
#include "WavePlay.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "MySlider.h"
#define SAMPLE_FREQUENCY 8000
#define ABS(n) ((n) >= 0 ? (n) : -(n))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))
#define ZERO 1e-5
#define NORMALDRAWNUM 20000
// CComposeWavPlayerDlg 对话框
class CComposeWavPlayerDlg : public CDialogEx
{
// 构造
public:
	CComposeWavPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COMPOSEWAVPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	HICON m_hIconPlay;
	HICON m_hIconPause;
	HICON m_hIconStop;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CNiceSliderCtrl m_process;
	CButton m_play;
	CButton m_pause;
	CButton m_stop;
	CStatic m_likely;
	CStatic m_picDraw1;
	CStatic m_picDraw2;
	CButton m_play2;
	CButton m_pause2;
	CButton m_stop2;
	CButton m_play3;
	CButton m_pause3;
	CButton m_stop3;
	CFont m_newFontSrc;
	CFont m_newFontLog;


	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMReleasedcaptureProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedPlay(UINT nID);
	afx_msg void OnBnClickedPause(UINT nID);
	afx_msg void OnBnClickedStop(UINT nID);

//------------------------------------------------------------------------------------------
	WavePlay m_WavPlay;
	int m_Hour;
	int m_Minute;
	int m_Second;
	int m_Ch;
	int m_Cm;
	int m_Cs;
	int m_Totaltime;
	int m_Currenttime;
	float m_fLikely;
	float m_fPos;//日志音频在模板文件中的位置
	int m_SrcWavDataPointNum;
	int m_LogWavDataPointNum;
	int16_t * m_SrcPaintData;
	int16_t * m_LogPaintData;
	int m_DataBlock;

	CDC m_dcSrcBuffer;//用于存放波形图像的内存DC
	CDC m_dcLogBuffer;//用于存放波形图像的内存DC
	CDC m_dcPlayTime;
	int16_t m_SrcMaxValue;
	int16_t m_LogMaxValue;
	CString m_TempWavPath;//mod转换wav临时文件名
	CString m_TempComposedWavPath;//合成文件临时文件名
	//UINT m_SliderTimer;
	//类型转换
	void ConvertCStringToChar(CString m_srcCstring, char * &m_destChar);
	int ExtractWavFromMod(const CString m_SrcWavFile, const CString m_LogFilePath);	//从mod文件中提取wav

	int GetWavBufferFromLogWav(const CString m_SrcWavFile);
	int ComposeWavToTwoChannel(const CString m_SrcWavFile, float m_Pos, const CString m_LogFilePath,
		const CString m_NewWavFile);
	void DrawWave(CRect &rectPicture, CDC &m_dcBuffer, int16_t *&m_Data, const int m_WavDataPointNum, const int m_MaxValue);
	int CComposeWavPlayerDlg::InitOpen(const CString m_SrcFilePath, const CString m_LogFilePath);
	int CComposeWavPlayerDlg::InitOpenByLog(const CString m_LogFilePath);
	void DrawTime(CString text);
	int16_t GetMaxValue(int16_t *m_Data, int m_length);
	void InitDC(CDC &dc, CRect rect);
	void SetFont(CString m_style, int m_size, UINT nID, CFont &m_font);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);//更换字体颜色
	void WriteFont(UINT nID, CString m_words, CFont &m_font);
	bool isWavFile(const CString m_LogFilePath);
	void ChangeSize(UINT srcID, UINT destID);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void reDrawWindow();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
