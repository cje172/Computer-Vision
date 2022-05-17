#pragma once


// CBinCtrlDlg 대화 상자

class CBinCtrlDlg : public CDialog
{
	DECLARE_DYNAMIC(CBinCtrlDlg)

public:
	CBinCtrlDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBinCtrlDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_binValDisp;
	CSliderCtrl m_ctrlSlider;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnChangeEdit1();
};
