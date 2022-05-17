// CBinCtrlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "SN2020111414.h"
#include "CBinCtrlDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "SN2020111414Doc.h"
#include "SN2020111414View.h"


// CBinCtrlDlg 대화 상자

IMPLEMENT_DYNAMIC(CBinCtrlDlg, CDialog)

CBinCtrlDlg::CBinCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_binValDisp(0)
{

}

CBinCtrlDlg::~CBinCtrlDlg()
{
}

void CBinCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_binValDisp);
	DDX_Control(pDX, IDC_SLIDER1, m_ctrlSlider);
}


BEGIN_MESSAGE_MAP(CBinCtrlDlg, CDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CBinCtrlDlg::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_BUTTON1, &CBinCtrlDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CBinCtrlDlg::OnChangeEdit1)
END_MESSAGE_MAP()


// CBinCtrlDlg 메시지 처리기


BOOL CBinCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_ctrlSlider.SetRange(0, 255);  // 슬라이더바의 값의 범위 설정
	m_ctrlSlider.SetPos(100);  // 슬라이드바의 초기 상태 설정

	m_binValDisp = m_ctrlSlider.GetPos();  // 현재 설정되어 있는 값을 잡아옴
	UpdateData(FALSE);  // 설정된 데이터값으로 다이얼로그박스의 표시부 갱신

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBinCtrlDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pFrame);
	CChildFrame *pChild = (CChildFrame*)pFrame->GetActiveFrame();
	ASSERT(pChild);
	CSN2020111414Doc *pDoc = (CSN2020111414Doc*)pChild->GetActiveDocument();
	ASSERT(pDoc);
	CSN2020111414View *pView = (CSN2020111414View*)pChild->GetActiveView();
	ASSERT(pView);

	// Slider의 현재 위치를 가져옴
	m_binValDisp = m_ctrlSlider.GetPos();
	UpdateData(FALSE);  // 잡아온 데이터 값으로 다이얼로그 박스의 표시부 갱신

	// 현재 활성화 도큐먼트 클래스 아래의 이치화 계산 함수를 호출
	// pDoc->m_BinThres(256, 256, m_binValDisp);  // 슬라이드 설정 이치화 계수치를 넘겨줌

	// 현재 활성화 도큐먼트 클래스 아래의 영상 블렌딩 함수를 호출
	pDoc->ImageBlend(256, 256, m_binValDisp);  // 슬라이드 현재위치 값을 alpha 값으로 넘겨줌
	pView->Invalidate(FALSE);  // 화면 갱신

	*pResult = 0;
}


void CBinCtrlDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();  // 대화 박스를 종결
}


void CBinCtrlDlg::OnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pFrame);
	CChildFrame *pChild = (CChildFrame*)pFrame->GetActiveFrame();
	ASSERT(pChild);
	CSN2020111414Doc *pDoc = (CSN2020111414Doc*)pChild->GetActiveDocument();
	ASSERT(pDoc);
	CSN2020111414View *pView = (CSN2020111414View*)pChild->GetActiveView();
	ASSERT(pView);

	UpdateData(TRUE);  // 컨트롤 값을 변수에 반영
	m_ctrlSlider.SetPos(m_binValDisp);

	UpdateData(FALSE);  // 변수의 값을 컨트롤에 반영
}
