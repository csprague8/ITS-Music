#include "stdafx.h"
#include "GuitarNeckDlg.h"


static CBitmap m_hbmp_guitar_neck;
static HICON m_hIcon_note;

static const int string_spacing = 10;

CGuitarNeckDlg::CGuitarNeckDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CGuitarNeckDlg::IDD, pParent)
{
}

void CGuitarNeckDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGuitarNeckDlg, CDialogEx)
   ON_WM_SYSCOMMAND()
   ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CGuitarNeckDlg::OnInitDialog()
{
   CDialogEx::OnInitDialog();

   // TODO: Add extra initialization here
   int ret = m_hbmp_guitar_neck.LoadBitmapW(IDB_GUITAR_NECK);
   m_hIcon_note = AfxGetApp()->LoadIcon(IDR_NOTEWHOLE);

   return TRUE;  // return TRUE  unless you set the focus to a control
}


void CGuitarNeckDlg::draw_guitar_neck()
{
   HDC hDC = ::GetDC(m_hWnd);

   CBitmap bitmap; // Sequence is important
   CDC memDC;

   CDC *pDC = CDC::FromHandle(hDC);
   
   bitmap.LoadBitmap(IDB_GUITAR_NECK);

   memDC.CreateCompatibleDC(pDC);
   memDC.SelectObject(&bitmap);

   pDC->BitBlt(0, 0, 428, 170, &memDC, 0, 0, SRCCOPY);
}

void CGuitarNeckDlg::draw_not_positions(int note)
{
   HDC hDC = ::GetDC(m_hWnd);

   draw_guitar_neck();

   int baseE = eE;
   int baseA = eA;
   int baseD = eD;
   int baseG = eG;
   int baseB = eB;

   int x = 13;

   for (int i = 0; i < 17; i++)
   {
      if (baseE == note)
         DrawIconEx(hDC, x, 119, m_hIcon_note, 20, 20, 0, NULL, DI_NORMAL | DI_COMPAT);
      if (baseA == note)
         DrawIconEx(hDC, x, 100, m_hIcon_note, 20, 20, 0, NULL, DI_NORMAL | DI_COMPAT);
      if (baseD == note)
         DrawIconEx(hDC, x, 81, m_hIcon_note, 20, 20, 0, NULL, DI_NORMAL | DI_COMPAT);
      if (baseG == note)
         DrawIconEx(hDC, x, 62, m_hIcon_note, 20, 20, 0, NULL, DI_NORMAL | DI_COMPAT);
      if (baseB == note)
         DrawIconEx(hDC, x, 43, m_hIcon_note, 20, 20, 0, NULL, DI_NORMAL | DI_COMPAT);
      if (baseE == note)
         DrawIconEx(hDC, x, 24, m_hIcon_note, 20, 20, 0, NULL, DI_NORMAL | DI_COMPAT);

      baseE = (baseE + 1) % e_max_note2;
      baseA = (baseA + 1) % e_max_note2;
      baseD = (baseD + 1) % e_max_note2;
      baseG = (baseG + 1) % e_max_note2;
      baseB = (baseB + 1) % e_max_note2;

      x += 22;
   }
}


