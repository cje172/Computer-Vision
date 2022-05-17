
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

#include "CBinCtrlDlg.h"

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
	ON_COMMAND(ID_IMGHISTO, &CSN2020111414View::OnImghisto)
	ON_COMMAND(IDM_BINARIZATION, &CSN2020111414View::OnBinarization)
	ON_COMMAND(IDM_BIN_DYNAMIC, &CSN2020111414View::OnBinDynamic)
	ON_COMMAND(IDM_IMGHISTO, &CSN2020111414View::OnImghisto)
	ON_COMMAND(IDM_BITPLANE_7, &CSN2020111414View::OnBitplane7)
	ON_COMMAND(IDM_BITPLANE_4, &CSN2020111414View::OnBitplane4)
	ON_COMMAND(IDM_BITPLANE_0, &CSN2020111414View::OnBitplane0)
	ON_COMMAND(IDM_WATERMARK_INSERTION, &CSN2020111414View::OnWatermarkInsertion)
	ON_COMMAND(IDM_WATERMARK_DETECTION, &CSN2020111414View::OnWatermarkDetection)
	ON_COMMAND(IDM_HISTO_EQUAL, &CSN2020111414View::OnHistoEqual)
	ON_COMMAND(IDM_IMAGE_BLEND, &CSN2020111414View::OnImageBlend)
	ON_COMMAND(IDM_HISTO_STRETCH, &CSN2020111414View::OnHistoStretch)
	ON_COMMAND(IDM_HISTO_UPSTRETCH, &CSN2020111414View::OnHistoUpstretch)
	ON_COMMAND(IDM_HISTO_SPEC, &CSN2020111414View::OnHistoSpec)
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


void CSN2020111414View::OnImghisto()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->m_ImgHisto(256, 256);
	Invalidate(FALSE);
}


void CSN2020111414View::OnBinarization()
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
			if (pDoc->m_InImg[i][j] > 100) pDoc->m_OutImg[i][j] = 255;
			else pDoc->m_OutImg[i][j] = 0;
		}
	}
	Invalidate(FALSE);
}


void CSN2020111414View::OnBinDynamic()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CBinCtrlDlg pbinCtrlDlg;  // 슬라이드컨트롤 클래스 변수의 선언
	pbinCtrlDlg.DoModal();  // 슬라이드컨트롤박스의 호출
}


void CSN2020111414View::OnBitplane7()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int position = 7;
	
	unsigned char mask = 0x01;
	mask <<= position;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			pDoc->m_OutImg[i][j] = (mask & pDoc->m_InImg[i][j]) ? 255 : 0;
		}
	}
	Invalidate(FALSE);
}


void CSN2020111414View::OnBitplane4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int position = 4;

	unsigned char mask = 0x01;
	mask <<= position;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			pDoc->m_OutImg[i][j] = (mask & pDoc->m_InImg[i][j]) ? 255 : 0;
		}
	}
	Invalidate(FALSE);
}


void CSN2020111414View::OnBitplane0()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int position = 0;

	unsigned char mask = 0x01;
	mask <<= position;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			pDoc->m_OutImg[i][j] = (mask & pDoc->m_InImg[i][j]) ? 255 : 0;
		}
	}
	Invalidate(FALSE);
}


void CSN2020111414View::OnWatermarkInsertion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 최하위 비트 평면에 정보 넣기
	int position = 0;

	unsigned char mask = 0x01;
	mask <<= position;

	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 256; j++)
			pDoc->m_OutImg[j][i] = 0;

	for (int i = 64; i < 128; i++)
		for (int j = 0; j < 256; j++)
			pDoc->m_OutImg[j][i] = 255;
	
	for (int i = 128; i < 192; i++)
		for (int j = 0; j < 256; j++)
			pDoc->m_OutImg[j][i] = 0;

	for (int i = 192; i < 256; i++)
		for (int j = 0; j < 256; j++)
			pDoc->m_OutImg[j][i] = 255;
	

	// Image Combine
	unsigned char tmpImg[256][256];

	for (int p = 1; p <= 7; p++) // 1부터 7까지 반복
	{
		mask = 0x01; // 초기화
		mask <<= p;
		
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				tmpImg[i][j] = (mask & pDoc->m_InImg[i][j]) ? 255 : 0;

		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				pDoc->m_OutImg[i][j] += tmpImg[i][j] & mask;
	}
	

	// 출력 영상을 "wm.raw" 파일로도 저장
	FILE *outfile;
	fopen_s(&outfile, "wm.raw", "wb");
	fwrite(pDoc->m_OutImg, sizeof(char), 256 * 256, outfile);
	fclose(outfile);

	Invalidate(FALSE);
}


void CSN2020111414View::OnWatermarkDetection()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 위에서 저장한 "wm.raw" 파일을 입력 영상으로 읽어오기
	FILE *infile;
	errno_t err = fopen_s(&infile, "wm.raw", "rb");

	if (err != 0) 
	{ 
		printf("File open error!!"); 
		return;
	}

	fread(pDoc->m_InImg, sizeof(char), 256 * 256, infile);
	fclose(infile);

	// 0번 비트평면 이미지를 표시하는 함수 호출
	OnBitplane0();

	Invalidate(FALSE);
}


void CSN2020111414View::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 도큐먼트 클래스에 있는 히스토그램 평활화 함수 호출
	pDoc->m_HistoEqual(256, 256);

	Invalidate(FALSE);		// 화면 갱신
}


void CSN2020111414View::OnImageBlend()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->TwoImgLoad();

	CBinCtrlDlg pbinCtrlDlg;  // 슬라이드컨트롤 클래스 변수의 선언
	pbinCtrlDlg.DoModal();  // 슬라이드컨트롤박스의 호출
}


void CSN2020111414View::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 도큐먼트 클래스에 있는 히스토그램 스트레칭 함수 호출
	pDoc->m_HistoStretch(256, 256);

	Invalidate(FALSE);  // 화면 갱신
}


void CSN2020111414View::OnHistoUpstretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->m_HistoUpstretch(256, 256, 20, 20);

	Invalidate(FALSE);  // 화면 갱신
}


void CSN2020111414View::OnHistoSpec()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111414Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFile file;
	CFileDialog opendlg1(TRUE);

	if (opendlg1.DoModal() == IDOK)
	{
		file.Open(opendlg1.GetPathName(), CFile::modeRead);
		file.Read(pDoc->m_InImg1, sizeof(pDoc->m_InImg1));
		file.Close();
	}

	pDoc->m_HistoSpec(256, 256);

	Invalidate(FALSE);  // 화면 갱신
}
