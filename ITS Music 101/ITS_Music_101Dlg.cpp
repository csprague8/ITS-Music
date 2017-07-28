
// ITS_Music_101Dlg.cpp : implementation file
//

#include "stdafx.h"

#include "ITS Music 101.h"
#include "ITS_Music_101Dlg.h"
#include "afxdialogex.h"
#include "MusicStaffDlg.h"
#include "GuitarNeckDlg.h"
#include "resource.h"
#include "Scales.h"
#include "MainTextStrings.h"
#include "Rhythms.h"
#include "ProgressLogging.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static int current_category = -1;

static Prog_Map_t progress_map;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CITSMusic101Dlg dialog




CITSMusic101Dlg::CITSMusic101Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CITSMusic101Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CITSMusic101Dlg::~CITSMusic101Dlg()
{
   write_progress_log(current_category, progress_map);
}

void CITSMusic101Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CITSMusic101Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_WM_GETMINMAXINFO()
   ON_WM_SIZE()
   ON_BN_CLICKED(IDC_START_STOP_METRONOME, CITSMusic101Dlg::OnStartStop)
   ON_BN_CLICKED(IDC_TEMPO_UP_BUTTON, CITSMusic101Dlg::OnTempoUp)
   ON_BN_CLICKED(IDC_TEMPO_DOWN_BUTTON, CITSMusic101Dlg::OnTempoDown)
   ON_BN_CLICKED(IDC_TEST_MODE, CITSMusic101Dlg::OnCategoryChanged)
   ON_BN_CLICKED(IDC_CHECK_BUTTON, CITSMusic101Dlg::OnCheckButton)
   ON_EN_CHANGE(IDC_TEMPO_TEXT, CITSMusic101Dlg::OnTempoChanged)
   ON_LBN_SELCHANGE(IDC_COMBO_CATEGORIES, CITSMusic101Dlg::OnCategoryChanged)
   ON_LBN_SELCHANGE(IDC_COMBO_SUBCATEGORIES, CITSMusic101Dlg::OnSubCategoryChanged)
   ON_LBN_SELCHANGE(IDC_COMBO_NOTE_BASE, CITSMusic101Dlg::OnSubCategoryChanged)
END_MESSAGE_MAP()


// CITSMusic101Dlg message handlers

BOOL CITSMusic101Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

   categories_combo = (CComboBox*)GetDlgItem(IDC_COMBO_CATEGORIES);
   subcategories_combo = (CComboBox*)GetDlgItem(IDC_COMBO_SUBCATEGORIES);
   notes_combo = (CComboBox*)GetDlgItem(IDC_COMBO_NOTE_BASE);
   test_box = (CButton*)GetDlgItem(IDC_TEST_MODE);
   maintxt = (CEdit*)GetDlgItem(IDC_MainText);

   read_progress_log(&current_category, &progress_map);

   categories_combo->Clear();
   for (int cat = 0; cat < e_max_categories; cat++)
   {
      categories_combo->AddString(categories_text[cat]);
   }
   categories_combo->SetWindowTextW(L"Select Category");

   notes_combo->Clear();
   for (int n = 0; n < e_max_note; n++)
   {
      notes_combo->AddString(notes_text[n]);
   }
   notes_combo->SetCurSel(C);

   ::ShowWindow(GetDlgItem(IDC_COMBO_SUBCATEGORIES)->GetSafeHwnd(), SW_HIDE);
   ::ShowWindow(GetDlgItem(IDC_SUBCATEGORY_LABEL)->GetSafeHwnd(), SW_HIDE);
   ::ShowWindow(GetDlgItem(IDC_COMBO_NOTE_BASE)->GetSafeHwnd(), SW_HIDE);
   ::ShowWindow(GetDlgItem(IDC_BASE_NOTE_LABEL)->GetSafeHwnd(), SW_HIDE);
   
   ::SetWindowText(GetDlgItem(IDC_TEMPO_TEXT)->GetSafeHwnd(), L"120");

	// TODO: Add extra initialization here
   MusicStaff1 = new CMusicStaffDlg();
   MusicStaff1->Create(MusicStaff1->IDD, this);

   MusicStaff2 = new CMusicStaffDlg();
   MusicStaff2->Create(MusicStaff1->IDD, this);

   GuitarNeck = new CGuitarNeckDlg();
   GuitarNeck->Create(GuitarNeck->IDD, this);

   CRect rect;
   GetClientRect(&rect);
   int clientWidth = rect.Width();

   if (MusicStaff1)
   {
      MusicStaff1->MoveWindow(10, 150, clientWidth - 20, 140);
      MusicStaff1->ShowWindow(SW_HIDE);
   }

   if (MusicStaff2)
   {
      MusicStaff2->MoveWindow(10, 250, clientWidth - 20, 140);
      MusicStaff2->ShowWindow(SW_HIDE);
   }

   if (GuitarNeck)
   {
      GuitarNeck->MoveWindow(10, 150, clientWidth - 20, 175);
      GuitarNeck->ShowWindow(SW_HIDE);
   }

   maintxt->ShowWindow(SW_HIDE);

   if (current_category == -1)
   {
      std::wstring msg = startup_text;
      msg += nl2;
      msg += window_resize_msg;

      SetDlgItemText(IDC_MainText, msg.c_str());
   }
   else
   {
      int percent = 0;
      int cat = -1;
      int subcat = -1;
      bool needsImproving = false;

      for (Prog_Map_t::iterator it = progress_map.begin(); it != progress_map.end(); ++it)
      {
         cat++;
         subcat = -1;

         for (int sub = 0; sub < it->second.size(); sub++)
         {
            subcat = sub;
            bool viewed = it->second[sub][e_viewed] > 0;

            if (!viewed )
            {
               percent = 0;
               needsImproving = true;
               break;
            }

            int attempts = it->second[sub][e_attempts];
            int accuracy = it->second[sub][e_accuracy];

            int tmpPercent = (int)((float)accuracy / (float)attempts * 100.0);

            if (tmpPercent < 60)
            {
               percent = tmpPercent;
               needsImproving = true;
               break;
            }
         }

         if (needsImproving)
            break;
      }
      //CString txt;
      std::wstring recCat = categories_text[cat];
      if (subcat > 0)
      {
         recCat += L" - " + std::to_wstring(subcat) + L". ";
         switch (cat)
         {
         case e_note_lengths:
         case e_rest_types:
            recCat += note_length_text[subcat];
            break;
         case e_rhythm_patterns:
            recCat += rhythms_text[subcat];
            break;
         case e_scales:
            recCat += scale_text[subcat];
            break;
         case e_music_keys:
            recCat += notes_text2[subcat];
            break;
         case e_note_values:
         case e_note_mapping:
            break;
         }
      }
      wchar_t tmp[512];
      swprintf_s(tmp, startup_progress_text,
         categories_text[current_category],
         recCat.c_str(),
         percent);
      //txt.Format(startup_progress_text, 
      //   categories_text[current_category],
      //   categories_text[cat],
      //   percent);

      std::wstring msg = tmp;
      msg += nl2;
      msg += window_resize_msg;

      SetDlgItemText(IDC_MainText, msg.c_str());
   }


   maintxt->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CITSMusic101Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CITSMusic101Dlg::OnPaint()
{
   CRect rect;
   GetClientRect(&rect);

	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CITSMusic101Dlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
   // set the minimum tracking width
   // and the minimum tracking height of the window
   lpMMI->ptMinTrackSize.x = 700;
   lpMMI->ptMinTrackSize.y = 650;
}

void CITSMusic101Dlg::OnSize(UINT nType, int cx, int cy)
{
   CDialogEx::OnSize(nType, cx, cy);

   static bool onInit = true;

   if (!onInit)
   {
      int index = categories_combo->CComboBox::GetCurSel();

      if (index >= 0)
      {
         OnCategoryChanged();
      }
      else
      {
         CRect windowRect;

         GetClientRect(&windowRect);

         maintxt->MoveWindow(10, 150,
            windowRect.Width() - 20, windowRect.Height() - 150 - 10);
         maintxt->ShowWindow(SW_SHOW);
      }
   }

   onInit = false;
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CITSMusic101Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CITSMusic101Dlg::OnStartStop()
{
   m_running = !m_running;

   if (m_running)
   {
      metronome.start();
      SetDlgItemText(IDC_START_STOP_METRONOME, L"Stop");
   }
   else
   {
      metronome.end();
      SetDlgItemText(IDC_START_STOP_METRONOME, L"Start");
   }
}

void CITSMusic101Dlg::OnTempoUp()
{
   int tempo = metronome.get_tempo();
   tempo++;
   metronome.set_tempo(tempo);
   SetDlgItemInt(IDC_TEMPO_TEXT, tempo);
}

void CITSMusic101Dlg::OnTempoDown()
{
   int tempo = metronome.get_tempo();
   tempo--;
   metronome.set_tempo(tempo);
   SetDlgItemInt(IDC_TEMPO_TEXT, tempo);
}

void CITSMusic101Dlg::OnTempoChanged()
{
   int tempo = GetDlgItemInt(IDC_TEMPO_TEXT);
   metronome.set_tempo(tempo);
}


void CITSMusic101Dlg::OnCategoryChanged()
{
   bool test = (test_box->GetCheck() != FALSE);

   subcategories_combo->Clear();

   int num_sub_categories = 0;
   wchar_t (*sub_categories)[32] = NULL;

   bool dispNoteCombo = false;
   bool extCombo = false;

   GuitarNeck->ShowWindow(SW_HIDE);
   MusicStaff1->ShowWindow(SW_SHOW);
   MusicStaff2->ShowWindow(SW_SHOW);

   int index = categories_combo->CComboBox::GetCurSel();
   
   current_category = index;

   std::wstring check_msg = get_check_info_text();

   switch (index)
   {
   case e_note_lengths:
      if (test)
         SetDlgItemText(IDC_MainText, check_msg.c_str());
      else
         SetDlgItemText(IDC_MainText, note_length_info_text);
      num_sub_categories = e_max_lengths;
      sub_categories = note_length_text;
      break;
   case e_rest_types:
      if (test)
         SetDlgItemText(IDC_MainText, check_msg.c_str());
      else
         SetDlgItemText(IDC_MainText, rest_length_info_text);
      num_sub_categories = e_max_lengths;
      sub_categories = note_length_text;
      break;
   case e_note_values:
      if (test)
         SetDlgItemText(IDC_MainText, check_msg.c_str());
      else
         SetDlgItemText(IDC_MainText, note_value_info_text);
      on_note_value_category();
      break;
   case e_rhythm_patterns:
      if (test)
         SetDlgItemText(IDC_MainText, check_msg.c_str());
      else
         SetDlgItemText(IDC_MainText, rhythms_info_text);
      num_sub_categories = e_max_rhythm_patterns;
      sub_categories = rhythms_text;
      break;
   case e_scales:
      if (test)
         SetDlgItemText(IDC_MainText, check_msg.c_str());
      else
         SetDlgItemText(IDC_MainText, scales_info_text);
      dispNoteCombo = true;
      num_sub_categories = e_max_scales;
      sub_categories = scale_text;
      break;
   case e_music_keys:
      if (test)
         SetDlgItemText(IDC_MainText, check_msg.c_str());
      else
         SetDlgItemText(IDC_MainText, keys_info_text);
      dispNoteCombo = true;
      on_key_changed();
      break;
   case e_note_mapping:
      if (test)
         SetDlgItemText(IDC_MainText, check_msg.c_str());
      else
         SetDlgItemText(IDC_MainText, mapping_info_text);
      dispNoteCombo = true;
      extCombo = true;
      draw_neck_data();
      ShowNotesBox(dispNoteCombo, extCombo);
      OnSubCategoryChanged();
      return;
   default:
      return;
   }

   subcategories_combo->ResetContent();
   for (int subcat = 0; subcat < num_sub_categories; subcat++)
   {
      if (test)
      {
         CString tmp;
         tmp.Format(L"%i", subcat);
         subcategories_combo->AddString(tmp);
      }
      else
      {
         subcategories_combo->AddString(sub_categories[subcat]);
      }
   }

   ShowCatBox(num_sub_categories != 0);
   if (num_sub_categories != 0)
   {
      subcategories_combo->SetCurSel(0);
      OnSubCategoryChanged();
   }

   ShowNotesBox(dispNoteCombo, extCombo);
}

void CITSMusic101Dlg::OnSubCategoryChanged()
{
   int noteSel = notes_combo->CComboBox::GetCurSel();
   int catIdx = categories_combo->CComboBox::GetCurSel();
   int subcatIdx = subcategories_combo->CComboBox::GetCurSel();

   progress_map[catIdx][subcatIdx][e_viewed]++;
   
   std::vector<note_info_t> data;

   switch (catIdx)
   {
   case e_note_lengths:
      on_note_types_change(subcatIdx, false);
      break;
   case e_rest_types:
      on_note_types_change(subcatIdx, true);
      break;
   case e_rhythm_patterns:
      on_rhythm_pattern_change(subcatIdx);
      break;
   case e_scales:
      on_scale_changed(subcatIdx);
      break;
   case e_music_keys:
      on_key_changed();
      break;
   case e_note_mapping:
      GuitarNeck->ShowWindow(SW_SHOW);
      GuitarNeck->UpdateWindow();
      GuitarNeck->draw_not_positions(noteSel);
      break;
   }
}

void CITSMusic101Dlg::on_note_value_category()
{
   std::vector<note_info_t> data;

   int value = C;
   int level = 4;

   for (int i = 0; i < 12; i++)
   {
      note_info_t temp = { value, e_no_sign, level, e_quarter, false };
      data.push_back(temp);
      value++;
      if (value >= e_max_note)
      {
         value = value % e_max_note;
         level++;
      }
   }

   draw_data(data, true, false);
}

void CITSMusic101Dlg::on_note_types_change(int note_type, bool isRest)
{
   std::vector<note_info_t> data;
   note_info_t temp = { C, e_no_sign, 5, note_type, isRest };
   int num_of_notes = 0;

   switch (note_type)
   {
   case e_whole:
      num_of_notes = 5;
      break;
   case e_half:
      num_of_notes = 10;
      break;
   case e_quarter:
      num_of_notes = 20;
      break;
   case e_eighth:
      num_of_notes = 24;
      break;
   case e_sixteenth:
      num_of_notes = 32;
      break;
   }

   for (int i = 0; i < num_of_notes; i++)
   {
      data.push_back(temp);
   }

   draw_data(data, false, true);
}

void CITSMusic101Dlg::on_scale_changed(int scale_type)
{
   int noteSel = notes_combo->CComboBox::GetCurSel();

   std::vector<note_info_t> data;

   int baseOffset = 0;

   if (scale_type <= e_locrian)
   {
      noteSel -= scale_type;

      if (noteSel < 0)
      {
         noteSel += e_max_note;
         baseOffset = -1;
      }
      for (int i = 0; i < 8; i++)
      {
         data.push_back(Major_Scales[noteSel][i]);
      }

      for (int i = 0; i < scale_type; i++)
      {
         data.erase(data.begin());
         note_info_t tmp = data.front();
         tmp.level++;
         data.push_back(tmp);
      }

      if (baseOffset != 0)
      {
         for (auto &note : data)
         {
            note.level += baseOffset;
            int bkey = data.front().level * 10 + data.front().note;
            int nkey = note.level * 10 + note.note;

            while (nkey < bkey)
            {
               note.level++;
               nkey = note.level * 10 + note.note;
            }
         }
      }
      else
      {
         int bkey = data.front().level * 10 + data.front().note;

         for (auto &note : data)
         {
            int nkey = note.level * 10 + note.note;

            while (nkey < bkey)
            {
               note.level++;
               nkey = note.level * 10 + note.note;
            }
         }
      }
   }
   else if (scale_type == e_chromatic)
   {
      int value = noteSel;
      int level = 4;

      do
      {
         note_info_t temp = { value, e_no_sign, level, e_quarter, false };
         data.push_back(temp);

         if (value != E && value != B)
         {
            temp = { value, e_sharp, level, e_quarter };
            data.push_back(temp);
         }

         value++;
         if (value >= e_max_note)
         {
            value = value % e_max_note;
            level++;
         }
      } while (value != noteSel);

      note_info_t temp = { value, e_no_sign, level, e_quarter, false };
      data.push_back(temp);
   }

   draw_data(data, true, false);
}

void CITSMusic101Dlg::on_key_changed()
{
   int noteSel = notes_combo->CComboBox::GetCurSel();

   std::vector<note_info_t> data;

   draw_data(data, true, false, noteSel);
}

void CITSMusic101Dlg::on_rhythm_pattern_change(int rhythm_type)
{
   std::vector<note_info_t> data;

   int size = 0;
   int *pattern = NULL;

   switch (rhythm_type)
   {
   case e_rhythm_pattern_1:
      size = sizeof(pattern1) / sizeof(int);
      pattern = pattern1;
      break;
   case e_rhythm_pattern_2:
      size = sizeof(pattern2) / sizeof(int);
      pattern = pattern2;
      break;
   case e_rhythm_pattern_3:
      size = sizeof(pattern3) / sizeof(int);
      pattern = pattern3;
      break;
   case e_rhythm_pattern_4:
      size = sizeof(pattern4) / sizeof(int);
      pattern = pattern4;
      break;
   case e_rhythm_pattern_5:
      size = sizeof(pattern5) / sizeof(int);
      pattern = pattern5;
      break;
   case e_rhythm_pattern_6:
      size = sizeof(pattern6) / sizeof(int);
      pattern = pattern6;
      break;
   case e_rhythm_pattern_7:
      size = sizeof(pattern7) / sizeof(int);
      pattern = pattern7;
      break;
   case e_rhythm_pattern_8:
      size = sizeof(pattern8) / sizeof(int);
      pattern = pattern8;
      break;
   case e_rhythm_pattern_9:
      size = sizeof(pattern9) / sizeof(int);
      pattern = pattern9;
      break;
   case e_rhythm_pattern_10:
      size = sizeof(pattern10) / sizeof(int);
      pattern = pattern10;
      break;
   case e_rhythm_pattern_11:
      size = sizeof(pattern11) / sizeof(int);
      pattern = pattern11;
      break;
   case e_rhythm_pattern_12:
      size = sizeof(pattern12) / sizeof(int);
      pattern = pattern12;
      break;
   case e_rhythm_pattern_13:
      size = sizeof(pattern13) / sizeof(int);
      pattern = pattern13;
      break;
   }

   if (pattern == NULL)
      return;

   for (int i = 0; i < size; i++)
   {
      note_info_t tmp = { C, e_no_sign, 5, pattern[i] % rw, pattern[i] >= rw };
      data.push_back(tmp);
   }

   draw_data(data, false, true);
}

void CITSMusic101Dlg::draw_data(std::vector<note_info_t> data,  
   bool draw_bass_clef, bool isRhythm, int key)
{
   CRect rect;
   CRect tboxRect;
   CRect windowRect;

   GetClientRect(&windowRect);

   bool test = (test_box->GetCheck() != FALSE);

   maintxt->ShowWindow(SW_HIDE);

   int nextY = 150;

   // Clear the staffs
   MusicStaff1->Invalidate();
   MusicStaff2->Invalidate();
   maintxt->Invalidate();

   // Draw trebble staff
   MusicStaff1->MoveWindow(10, nextY, windowRect.Width() - 20, 150);
   MusicStaff1->draw_notes(&data, e_trebble_clef, 4, 4, key, isRhythm, test);
   MusicStaff1->GetClientRect(&rect);

   // Draw bass staff
   if (draw_bass_clef)
   {
      nextY += (rect.Height() + 10);
      MusicStaff2->ShowWindow(SW_SHOW);
      MusicStaff2->MoveWindow(10, nextY, 
         rect.Width(), rect.Height(), TRUE);
      MusicStaff2->draw_notes(&data, e_bass_clef, 4, 4, key, isRhythm, test);
      MusicStaff2->GetClientRect(&rect);
   }
   else
   {
      MusicStaff2->ShowWindow(SW_HIDE);
   }

   nextY += (rect.Height() + 20);

   if (nextY + 10 < windowRect.Height())
   {
      maintxt->MoveWindow(10, nextY,
         windowRect.Width() - 20, windowRect.Height() - nextY - 10);
      maintxt->ShowWindow(SW_SHOW);
   }

   MusicStaff1->UpdateWindow();
   MusicStaff2->UpdateWindow();
   maintxt->UpdateWindow();

   UpdateWindow();
}

void CITSMusic101Dlg::draw_neck_data()
{
   MusicStaff1->ShowWindow(SW_HIDE);
   MusicStaff2->ShowWindow(SW_HIDE);
   maintxt->ShowWindow(SW_HIDE);
   GuitarNeck->ShowWindow(SW_SHOW);

   CRect neckRect;
   CRect tboxRect;
   CRect windowRect;
   GuitarNeck->GetClientRect(&neckRect);
   maintxt->GetClientRect(&tboxRect);
   GetClientRect(&windowRect);

   int y = 150 + neckRect.Height() + 10;

   if (y + 10 < windowRect.Height())
   {
      maintxt->MoveWindow(10, y,
         windowRect.Width() - 20, windowRect.Height() - y - 10);
      maintxt->ShowWindow(SW_SHOW);
   }
}

void CITSMusic101Dlg::ShowNotesBox(bool show, bool ext)
{
   notes_combo->Clear();
   notes_combo->ResetContent();

   if (ext)
   {
      for (int n = 0; n < e_max_note2; n++)
      {
         notes_combo->AddString(notes_text2[n]);
      }
   }
   else
   {
      for (int n = 0; n < e_max_note; n++)
      {
         notes_combo->AddString(notes_text[n]);
      }
   }
   notes_combo->SetCurSel(C);

   if (show)
   {
      ::ShowWindow(GetDlgItem(IDC_COMBO_NOTE_BASE)->GetSafeHwnd(), SW_SHOW);
      ::ShowWindow(GetDlgItem(IDC_BASE_NOTE_LABEL)->GetSafeHwnd(), SW_SHOW);
   }
   else
   {
      ::ShowWindow(GetDlgItem(IDC_COMBO_NOTE_BASE)->GetSafeHwnd(), SW_HIDE);
      ::ShowWindow(GetDlgItem(IDC_BASE_NOTE_LABEL)->GetSafeHwnd(), SW_HIDE);
   }
}

void CITSMusic101Dlg::ShowCatBox(bool show)
{
   if (show)
   {
      ::ShowWindow(GetDlgItem(IDC_COMBO_SUBCATEGORIES)->GetSafeHwnd(), SW_SHOW);
      ::ShowWindow(GetDlgItem(IDC_SUBCATEGORY_LABEL)->GetSafeHwnd(), SW_SHOW);
   }
   else
   {
      ::ShowWindow(GetDlgItem(IDC_COMBO_SUBCATEGORIES)->GetSafeHwnd(), SW_HIDE);
      ::ShowWindow(GetDlgItem(IDC_SUBCATEGORY_LABEL)->GetSafeHwnd(), SW_HIDE);
   }
}

void CITSMusic101Dlg::OnCheckButton()
{
   std::wstring ret;
   std::wstring info_text;

   info_text = get_check_info_text();
   
   ret = MusicStaff1->checkDataText();

   if (MusicStaff2->IsWindowVisible())
   {
      ret += MusicStaff2->checkDataText();
   }

   info_text += nl2;
   info_text += ret;

   MessageBox(ret.c_str(), L"Incorrect Answer", 0);

   std::ofstream file("log.txt", std::ios::app);
   file << (LPCSTR)CT2A(ret.c_str());
   file.close();

   int noteSel = notes_combo->CComboBox::GetCurSel();
   int catIdx = categories_combo->CComboBox::GetCurSel();
   int subcatIdx = subcategories_combo->CComboBox::GetCurSel();

   progress_map[catIdx][subcatIdx][e_attempts]++;
   if (ret.empty())
   {
      progress_map[catIdx][subcatIdx][e_accuracy]++;
   }

   write_progress_log(current_category, progress_map);
}

std::wstring CITSMusic101Dlg::get_check_info_text()
{
   std::wstring ret = tested_for_txt;

   CComboBox *categories_combo = (CComboBox*)GetDlgItem(IDC_COMBO_CATEGORIES);
   int index = categories_combo->CComboBox::GetCurSel();

   switch (index)
   {
      case e_note_lengths:
         ret += L"note lengths.\r\n";
         ret += note_length_check_info_text;
         break;
      case e_rest_types:
         ret += L"rest lengths.\r\n";
         ret = note_length_check_info_text;
         break;
      case e_note_values:
         ret += L"note values.\r\n";
         ret = note_value_check_info_text;
         break;
      case e_rhythm_patterns:
         ret += L"rhythm patterns.\r\n";
         ret = note_length_check_info_text;
         break;
      case e_scales:
         ret += L"scales\r\n";
         ret = note_value_check_info_text;
         break;
      case e_music_keys:
         ret += L"msuic keys\r\n";
         ret = note_value_check_info_text;
         break;
      case e_note_mapping:
         ret += L"note mapping\r\n";
         ret = note_value_check_info_text;
   }

   return ret;
}