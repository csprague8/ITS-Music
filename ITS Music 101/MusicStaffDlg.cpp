#include "MusicStaffDlg.h"
#include "TeachingCategories.h"


// ITS_Music_101Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ITS Music 101.h"
#include "ITS_Music_101Dlg.h"
#include "afxdialogex.h"

#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMusicStaffDlg dialog

static HICON m_hIcon_whole_note;
static HICON m_hIcon_half_note;
static HICON m_hIcon_quarter_note;
static HICON m_hIcon_sharp;
static HICON m_hIcon_flat;
static HICON m_hIcon_trebble;
static HICON m_hIcon_bass;
static HICON m_hIcon_rest_whole;
static HICON m_hIcon_rest_half;
static HICON m_hIcon_rest_quarter;
static HICON m_hIcon_rest_eighth;
static HICON m_hIcon_rest_sixteenth;

const int lineSpacing = 14;
const int noteSpacing = lineSpacing / 2;
const int C4 = 63;
const int C2 = 63 + 2 * noteSpacing;
const int octave = e_max_note * noteSpacing;

CMusicStaffDlg::CMusicStaffDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CMusicStaffDlg::IDD, pParent)
{
   m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMusicStaffDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMusicStaffDlg, CDialogEx)
   ON_WM_SYSCOMMAND()
   ON_WM_PAINT()
END_MESSAGE_MAP()


// CMusicStaffDlg message handlers

BOOL CMusicStaffDlg::OnInitDialog()
{
   CDialogEx::OnInitDialog();

   // Set the icon for this dialog.  The framework does this automatically
   //  when the application's main window is not a dialog
   SetIcon(m_hIcon, TRUE);			// Set big icon
   SetIcon(m_hIcon, FALSE);		// Set small icon

   // TODO: Add extra initialization here
   m_hIcon_whole_note     = AfxGetApp()->LoadIcon(IDR_NOTEWHOLE);
   m_hIcon_half_note      = AfxGetApp()->LoadIcon(IDR_NOTEHALF);
   m_hIcon_quarter_note   = AfxGetApp()->LoadIcon(IDR_NOTEQUARTER);
   m_hIcon_sharp          = AfxGetApp()->LoadIcon(IDR_SHARP);
   m_hIcon_flat           = AfxGetApp()->LoadIcon(IDR_FLAT);
   m_hIcon_trebble        = AfxGetApp()->LoadIcon(IDR_TREBLE);
   m_hIcon_bass           = AfxGetApp()->LoadIcon(IDR_BASS);
   m_hIcon_rest_whole     = AfxGetApp()->LoadIcon(IDR_REST_WHOLE);
   m_hIcon_rest_half      = AfxGetApp()->LoadIcon(IDR_REST_HALF);
   m_hIcon_rest_quarter   = AfxGetApp()->LoadIcon(IDR_REST_QUARTER);
   m_hIcon_rest_eighth    = AfxGetApp()->LoadIcon(IDR_REST_EIGHTH);
   m_hIcon_rest_sixteenth = AfxGetApp()->LoadIcon(IDR_REST_SIXTEENTH);

   return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMusicStaffDlg::draw_staff_lines(int width, int height, int h_offset)
{
   const int startX = 0;
   const int endX = width;

   h_offset += 10;

   HDC hDC = ::GetDC(m_hWnd);

   HPEN hPenBlack = CreatePen(0, 0, RGB(0, 0, 0));
   HPEN hPenWhite = CreatePen(0, 0, RGB(255, 255, 255));
   HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));

   ::SelectObject(hDC, hPenWhite);
   ::SelectObject(hDC, hBrush);

   Rectangle(hDC, 0, 0, width, height-20);

   ::SelectObject(hDC, hPenBlack);

   for (int line = 0; line < 5; line++)
   {
      int y = lineSpacing * (line + 1) + h_offset;
      MoveToEx(hDC, startX, y, NULL);
      LineTo(hDC, endX, y);
   }

   DeleteObject(hPenBlack);
   DeleteObject(hPenWhite);
   DeleteObject(hBrush);
   ::ReleaseDC(m_hWnd, hDC);
}

void CMusicStaffDlg::draw_notes(std::vector<note_info_t> *notes, 
   int clef, int sig_top, int sig_bottom, int key, bool isRhythm,
   bool test)
{
   HICON *note_ico = NULL;
   
   HDC hDC = ::GetDC(m_hWnd);

   double barCnt = 0;

   int number_of_notes = notes->size();

   note_info_t highestNote = { 0, 0, 0, 0, false };
   note_info_t lowestNote = { 0, 0, 12, 0, false };
   
   // determine the highest and lowest notes
   for (auto const& note : *notes)
   {
      if (note.isRest)
         continue;

      int nkey = note.level * 10 + note.note;
      int hkey = highestNote.level * 10 + highestNote.note;
      int lkey = lowestNote.level * 10 + lowestNote.note;

      if (nkey >= hkey)
         memcpy(&highestNote, &note, sizeof(note_info_t));

      if (nkey <= lkey)
         memcpy(&lowestNote, &note, sizeof(note_info_t));
   }

   int hkey = highestNote.level * 10 + highestNote.note;
   int lkey = lowestNote.level * 10 + lowestNote.note;

   int offset = 0;
   int winHightOffset = 0;

   // Get offset (shift down) from high notes
   if (hkey > (5 * 10 + G))
   {
      int base = hkey / 10 - 5;
      int note = abs(G - (hkey % 10));
      offset = 
         (base * (e_max_note * noteSpacing)) + (note * noteSpacing);
   }

   // Get C4 position (E4 if bass clef)
   int C4Key = 4 * 10 + C;
   if (clef == e_bass_clef)
      C4Key = 4 * 10 + E;

   // Get the window height offset based on lowest notes
   if (lkey < C4Key)
   {
      int base = 4 - lkey / 10;
      int note = abs(C - (lkey % 10));

      if (clef == e_bass_clef)
         note = abs(E - (lkey % 10));

      winHightOffset = 
         (base * (e_max_note * noteSpacing)) + (note * noteSpacing);
   }

   // Resize the window based on offsets
   CRect rc;
   GetClientRect(&rc);

   ::SetWindowPos(this->GetSafeHwnd(), 0, 0, 0, 
      rc.Width(), 100 + offset + winHightOffset + 20, 
      SWP_NOMOVE | SWP_NOREPOSITION | SWP_SHOWWINDOW);

   UpdateWindow();

   // Get new window size
   GetClientRect(&rc);

   // Draw the lines of the music staff
   draw_staff_lines(rc.Width(), rc.Height(), offset);

   int x = 5;

   // Draw the clef symbol
   x += draw_clef(hDC, clef, x, offset);

   // Draw the key
   x += draw_key(hDC, key, clef, x, offset);

   // Draw the time signiture values
   x += draw_time_signiture(hDC, sig_top, sig_bottom, x, offset);

   int lowC = (clef == e_trebble_clef ? C4 : C2);


   if (notes == NULL)
      return;

   for (auto const& edit : edit_list)
      ::DestroyWindow(edit.first);
   edit_list.clear();

   for (auto const& note : *notes)
   {
      int y = lowC - note.note * noteSpacing + octave 
         * (4 - note.level) + offset + 10;

      int y2 = y;

      HWND hEdit = CreateWindowEx(
         WS_EX_CLIENTEDGE, L"EDIT", L"",
         WS_CHILD | WS_VISIBLE | (test ? 0 : WS_DISABLED),
         x, rc.bottom - 20, (note.sign != e_no_sign ? 30 : 22), 20,
         this->GetSafeHwnd(), NULL,
         GetModuleHandle(NULL), NULL);

      std::wstring editText = L"";

      if (note.isRest)
      {
         y = 32 + offset;

         editText = note_length_text_abv[note.type];

         switch (note.type)
         {
         case e_whole:
            y = 28 + offset;
            DrawIconEx(hDC, x, y, m_hIcon_rest_whole, 
               28, 28, 0, NULL, DI_NORMAL | DI_COMPAT);
            x += 100;
            barCnt += 4;
            break;
         case e_half:
            y = 35 + offset;
            DrawIconEx(hDC, x, y, m_hIcon_rest_half, 
               28, 28, 0, NULL, DI_NORMAL | DI_COMPAT);
            x += 50;
            barCnt += 2;
            break;
         case e_quarter:
            DrawIconEx(hDC, x, y, m_hIcon_rest_quarter, 
               28, 28, 0, NULL, DI_NORMAL | DI_COMPAT);
            x += 25;
            barCnt += 1;
            break;
         case e_eighth:
            DrawIconEx(hDC, x, y, m_hIcon_rest_eighth, 
               28, 28, 0, NULL, DI_NORMAL | DI_COMPAT);
            barCnt += 0.5;
            x += 20;
            if (barCnt >= sig_top)
               x += 10;
            break;
         case e_sixteenth:
            DrawIconEx(hDC, x, y, m_hIcon_rest_sixteenth, 
               28, 28, 0, NULL, DI_NORMAL | DI_COMPAT);
            barCnt += 0.25;
            x += 15;
            if (barCnt >= sig_top)
               x += 15;
            break;
         }
      }
      else
      {
         std::wstring dispTxt = notes_text[note.note];

         if (note.sign != e_no_sign)
         {
            DrawIconEx(hDC, x, y, 
               (note.sign == e_sharp ? m_hIcon_sharp : m_hIcon_flat),
               28, 28, 0, NULL, DI_NORMAL | DI_COMPAT);
            x += 10;
            dispTxt += (note.sign == e_sharp ? L"#" : L"b");
         }

         if (isRhythm)
            editText = note_length_text_abv[note.type];
         else
            editText = dispTxt;

         switch (note.type)
         {
         case e_whole:
            DrawIconEx(hDC, x, y, m_hIcon_whole_note, 28, 28, 0, 
               NULL, DI_NORMAL | DI_COMPAT);
            x += 100;
            barCnt += 4;
            break;
         case e_half:
            DrawIconEx(hDC, x, y, m_hIcon_half_note, 28, 28, 0, 
               NULL, DI_NORMAL | DI_COMPAT);
            x += 50;
            barCnt += 2;
            break;
         case e_quarter:
            DrawIconEx(hDC, x, y, m_hIcon_quarter_note, 28, 28, 0, 
               NULL, DI_NORMAL | DI_COMPAT);
            x += 25;
            barCnt += 1;
            break;
         case e_eighth:
            DrawIconEx(hDC, x, y, m_hIcon_quarter_note, 28, 28, 0,
               NULL, DI_NORMAL | DI_COMPAT);
            barCnt += 0.5;
            if (barCnt - (int)barCnt != 0)
               draw_connecting_lines(hDC, x, y, y2, note.type);
            x += (barCnt >= sig_top ? 30 : 20);
            break;
         case e_sixteenth:
            DrawIconEx(hDC, x, y, m_hIcon_quarter_note, 28, 28, 0, 
               NULL, DI_NORMAL | DI_COMPAT);
            barCnt += 0.25;
            if (barCnt - (int)barCnt != 0)
               draw_connecting_lines(hDC, x, y, y2, note.type);
            x += (barCnt >= sig_top ? 30 : 15);
            break;
         }

      }

      if (test)
         ::SetWindowText(hEdit, L"");
      else
         ::SetWindowText(hEdit, editText.c_str());

      edit_list[hEdit] = editText;

      if (barCnt >= sig_top)
      {
         ::MoveToEx(hDC, x, 25 + offset, NULL);
         ::LineTo(hDC, x, 80 + offset);
         x += 10;
         barCnt = 0;
      }
   }

   UpdateWindow();
   ::ReleaseDC(m_hWnd, hDC);
}

void CMusicStaffDlg::move(int x, int y)
{
   CRect rect;
   GetClientRect(&rect);
   MoveWindow(rect);
   UpdateWindow();
}

void CMusicStaffDlg::draw_connecting_lines(HDC hDC, int x, int y,
   int y2, int type)
{

   HPEN hPen = CreatePen(0, 3, RGB(0, 0, 0));
   HGDIOBJ oldPen = ::SelectObject(hDC, hPen);

   if (type == e_eighth)
   {
      MoveToEx(hDC, x + 18, y, NULL);
      LineTo(hDC, x + 37, y);
   }
   else
   {
      MoveToEx(hDC, x + 18, y, NULL);
      LineTo(hDC, x + 32, y);

      MoveToEx(hDC, x + 18, y + 5, NULL);
      LineTo(hDC, x + 32, y + 5);
   }

   ::SelectObject(hDC, oldPen);
   DeleteObject(hPen);
}

int CMusicStaffDlg::draw_key(HDC hDC, int key, int clef, int x, int y)
{
   int keyWidth = 10;

   static const HICON m_hIcon_sharp = AfxGetApp()->LoadIcon(IDR_SHARP);
   static const HICON m_hIcon_flat = AfxGetApp()->LoadIcon(IDR_FLAT);

   int lowC = (clef == e_trebble_clef ? C4 : C2);

   for (int i = 0; i < 7; i++)
   {
      int sharpOff = 0;
      int bassOff = 0;
      int sharpLevel = 4;
      int bassLevel = 4;

      switch (i)
      {
      case C:
         sharpLevel = 5;
         bassLevel = 5;
         sharpOff += 10;
         bassOff += 50;
         break;
      case D:
         sharpLevel = 5;
         bassLevel = 5;
         sharpOff += 30;
         bassOff += 30;
         break;
      case E:
         sharpLevel = 5;
         bassLevel = 5;
         sharpOff += 50;
         bassOff += 10;
         break;
      case F:
         sharpLevel = 5;
         bassLevel = 4;
         sharpOff += 0;
         bassOff += 60;
         break;
      case G:
         sharpLevel = 5;
         bassLevel = 4;
         sharpOff += 20;
         bassOff += 40;
         break;
      case A:
         sharpLevel = 4;
         bassLevel = 4;
         sharpOff += 40;
         bassOff += 20;
         break;
      case B:
         sharpLevel = 5;
         bassLevel = 4;
         sharpOff += 60;
         bassOff += 0;
         break;
      }

      int level = (keys[key][i] == e_sharp ? sharpLevel : bassLevel);
      int off = (keys[key][i] == e_sharp ? sharpOff : bassOff);

      int dy = lowC - i * noteSpacing + octave
         * (4 - level) + y + (keys[key][i] == e_sharp ? 23 : 20);

      int sign = keys[key][i];

      if (sign != e_no_sign)
      {
         DrawIconEx(hDC, x + off, dy,
            (keys[key][i] == e_sharp ? m_hIcon_sharp : m_hIcon_flat),
            20, 20, 0, NULL, DI_NORMAL | DI_COMPAT);
         keyWidth += 10;
      }
   }

   return keyWidth;
}

int CMusicStaffDlg::draw_clef(HDC hDC, int clef, int x, int y)
{
   int width = 0;

   if (clef == e_trebble_clef)
   {
      DrawIconEx(hDC, x, 17 + y, m_hIcon_trebble,
         70, 70, 0, NULL, DI_NORMAL | DI_COMPAT);
      width = 30;
   }
   else if (clef == e_bass_clef)
   {
      DrawIconEx(hDC, x, 25 + y, m_hIcon_bass,
         50, 50, 0, NULL, DI_NORMAL | DI_COMPAT);
      width = 40;
   }

   return width;
}

int CMusicStaffDlg::draw_time_signiture(HDC hDC, int top, int bottom, int x, int y)
{
   int width = 30;

   TCHAR sig_top_t[3];
   TCHAR sig_bottom_t[3];
   swprintf_s(sig_top_t, 3, L"%i", top);
   swprintf_s(sig_bottom_t, 3, L"%i", bottom);
   RECT sigTopRect = { x, 20 + y, x + 40, 50 + y };
   RECT sigBottomRect = { x, 50 + y, x + 40, 80 + y };

   HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
   LOGFONT logfont;
   GetObject(hFont, sizeof(LOGFONT), &logfont);

   logfont.lfHeight = 35;

   HFONT hNewFont = CreateFontIndirect(&logfont);
   HFONT hOldFont = (HFONT)SelectObject(hDC, hNewFont);

   DrawText(hDC, sig_top_t, wcslen(sig_top_t), &sigTopRect, 0);
   DrawText(hDC, sig_bottom_t, wcslen(sig_bottom_t), &sigBottomRect, 0);

   SelectObject(hDC, hOldFont);
   DeleteObject(hFont);

   return width;
}

std::wstring CMusicStaffDlg::checkDataText()
{
   std::wstring retMsg = L"";

   HDC hDC = ::GetDC(m_hWnd);

   for (auto const& edit : edit_list)
   {
      wchar_t student_answer[8];
      wchar_t actual_answer[8];
      HWND editHwnd = edit.first;
      
      swprintf_s(actual_answer, 8, L"%s", edit.second.c_str());
      ::GetWindowText(editHwnd, student_answer, 8);

      CString sa = student_answer;
      CString aa = actual_answer;

      if (aa.CompareNoCase(sa) != 0)
      {
         retMsg += L"Incorrect: ";
         retMsg += student_answer;
         retMsg += L", Correct: ";
         retMsg += actual_answer;
         retMsg += L"\r\n";
      }
      else
      {
         ::EnableWindow(editHwnd, false);
      }
   }

   return retMsg;
}