
// SN2020111414View.cpp: CSN2020111414View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SN2020111414.h"
#endif

#include "SN2020111414Doc.h"
#include "SN2020111414View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSN2020111414View

IMPLEMENT_DYNCREATE(CSN2020111414View, CScrollView)

BEGIN_MESSAGE_MAP(CSN2020111414View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSN2020111414View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_REVERSE_IMG, &CSN2020111414View::OnReverseImg)
	ON_COMMAND(IDM_CONST_ADD, &CSN2020111414View::OnConstAdd)
	ON_COMMAND(IDM_CONST_SUB, &CSN2020111414View::OnConstSub)
	ON_COMMAND(IDM_CONST_MUL, &CSN2020111414View::OnConstMul)
	ON_COMMAND(IDM_CONST_DIV, &CSN2020111414View::OnConstDiv)
	ON_COMMAND(IDM_CONTRAST_UP, &CSN2020111414View::OnContrastUp)
	ON_COMMAND(IDM_CONTRAST_DOWN, &CSN2020111414View::OnContrastDown)
	ON_COMMAND(IDM_SALT_AND_PEPPER, &CSN2020111414View::OnSaltAndPepper)
END_MESSAGE_MAP()

// CSN2020111414View 생성/소멸

CSN2020111414View::CSN2020111414View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	height = width = 256;
	int rwsize = (((width * 8) + 31) / 32 * 4);	 // 4바이트의 배수여야 함
	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));

	BmInfo->bmiHeader.biBitCount = 8;
	BmInfo->bmiHeader.biClrImportant = 256;
	BmInfo->bmiHeader.biClrUsed = 256;
	BmInfo->bmiHeader.biCompression = 0;	//  BI_RGB = 0
	BmInfo->bmiHeader.biHeight = height;
	BmInfo->bmiHeader.biPlanes = 1;
	BmInfo->bmiHeader.biSize = 40;
	BmInfo->bmiHeader.biSizeImage = rwsize * height;
	BmInfo->bmiHeader.biWidth = width;
	BmInfo->bmiHeader.biXPelsPerMeter = 0;
	BmInfo->bmiHeader.biYPelsPerMeter = 0;
	for (int i = 0; i < 256; i++)	// 팔레트 넘버는 256
	{
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbBlue = i;
		BmInfo->bmiColors[i].rgbReserved = 0;
	}
}

CSN2020111414View::~CSN2020111414View()
{
}

BOOL CSN2020111414View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CSN2020111414View 그리기

void CSN2020111414View::OnDraw(CDC* pDC)
{
	CSN2020111414Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	for (int i = 0; i < height; i++)	// 입력 영상 출력
		for (int j = 0; j < width; j++)
			m_RevImg[i][j] = pDoc->m_InImg[height - i - 1][j];

	SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width, height,
		0, 0, 0, height, m_RevImg, BmInfo, DIB_RGB_COLORS);

	for (int i = 0; i < height; i++)	// 결과 영상 출력
		for (int j = 0; j < width; j++)
			m_RevImg[i][j] = pDoc->m_OutImg[height - i - 1][j];

	SetDIBitsToDevice(pDC->GetSafeHdc(), 300, 0, width, height,
		0, 0, 0, height, m_RevImg, BmInfo, DIB_RGB_COLORS);

	/*
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			unsigned char InVal = pDoc->m_InImg[i][j];
			unsigned char OutVal = pDoc->m_OutImg[i][j];
			pDC->SetPixel(j, i, RGB(InVal, InVal, InVal));
			pDC->SetPixel(j + 300, i, RGB(OutVal, OutVal, OutVal));
		}
	}
	*/
}

void CSN2020111414View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CSN2020111414View 인쇄


void CSN2020111414View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSN2020111414View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSN2020111414View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSN2020111414View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CSN2020111414View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSN2020111414View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSN2020111414View 진단

#ifdef _DEBUG
void CSN2020111414View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSN2020111414View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSN2020111414Doc* CSN2020111414View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSN2020111414Doc)));
	return (CSN2020111414Doc*)m_pDocument;
}
#endif //_DEBUG


// CSN2020111414View 메시지 처리기


void CSN2020111414View::OnReverseImg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
			pDoc->m_OutImg[i][j] = 255 - pDoc->m_InImg[i][j];
	}

	Invalidate(FALSE);
}


void CSN2020111414View::OnConstAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = pDoc->m_InImg[i][j] + 60;  // 더할 값은 60
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}

	Invalidate(FALSE);
}


void CSN2020111414View::OnConstSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = pDoc->m_InImg[i][j] - 60;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);  // 화면 갱신
}


void CSN2020111414View::OnConstMul()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//int tempVal = pDoc->m_InImg[i][j] * 1.4;
			int tempVal = pDoc->m_InImg[i][j] * 2.0;
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);  // 화면 갱신
}


void CSN2020111414View::OnConstDiv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//int tempVal = pDoc->m_InImg[i][j] / 1.4;
			int tempVal = pDoc->m_InImg[i][j] / 2.0;
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);  // 화면 갱신
}


void CSN2020111414View::OnContrastUp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	double slope = 2.0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = (128 + slope * (pDoc->m_InImg[i][j] - 128));
			tempVal = tempVal < 0 ? 0 : tempVal;
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);
}


void CSN2020111414View::OnContrastDown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	double slope = 1 / 2.0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = (128 + slope * (pDoc->m_InImg[i][j] - 128));
			tempVal = tempVal < 0 ? 0 : tempVal;
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);
}


void CSN2020111414View::OnSaltAndPepper()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	srand(time(0));	 // rand()의 seed 값을 time()를 사용하여 지정
	double randNum;  // 난수를 저장할 변수
	
	
	// 잡음 비율: 2%로 생성
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			randNum = (rand() - RAND_MAX / 2.0) * (2.0 / RAND_MAX);  // 난수를 - 1과 1 사이의 값으로 변환

			int tempVal = pDoc->m_InImg[i][j];
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;

			// 난수가 (1 - 2/100) 보다 크면 salt 잡음 생성
			if (randNum > (1 - 2.0 / 100))
				pDoc->m_OutImg[i][j] = 255;

			// 난수가 -(1 - 2/100) 보다 작으면 pepper 잡음 생성
			if (randNum < (-(1 - 2.0 / 100)))
				pDoc->m_OutImg[i][j] = 0;
		}
	}
	Invalidate(FALSE);
}
