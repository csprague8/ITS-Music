
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
#include "../Fister/Pipe.h"
#include <vector>
#include <fstream>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



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

void CITSMusic101Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CITSMusic101Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_START_STOP_METRONOME, CITSMusic101Dlg::OnStartStop)
   ON_BN_CLICKED(IDC_TEMPO_UP_BUTTON, CITSMusic101Dlg::OnTempoUp)
   ON_BN_CLICKED(IDC_TEMPO_DOWN_BUTTON, CITSMusic101Dlg::OnTempoDown)
   ON_BN_CLICKED(IDC_TEST_MODE, CITSMusic101Dlg::OnCategoryChanged)
   ON_BN_CLICKED(IDC_CHECK_BUTTON, CITSMusic101Dlg::OnCheckButton)
   ON_BN_CLICKED(IDC_RECORD, CITSMusic101Dlg::OnRecord)
   ON_BN_CLICKED(IDC_TEST_RECORD, CITSMusic101Dlg::OnTestRecord)
   ON_EN_CHANGE(IDC_TEMPO_TEXT, CITSMusic101Dlg::OnTempoChanged)
   ON_LBN_SELCHANGE(IDC_COMBO_CATEGORIES, CITSMusic101Dlg::OnCategoryChanged)
   ON_LBN_SELCHANGE(IDC_COMBO_SUBCATEGORIES, CITSMusic101Dlg::OnSubCategoryChanged)
   ON_LBN_SELCHANGE(IDC_COMBO_NOTE_BASE, CITSMusic101Dlg::OnSubCategoryChanged)
END_MESSAGE_MAP()


// CITSMusic101Dlg message handlers

BOOL CITSMusic101Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

   CComboBox *categories_combo = (CComboBox*)GetDlgItem(IDC_COMBO_CATEGORIES);
   categories_combo->Clear();
   for (int cat = 0; cat < e_max_categories; cat++)
   {
      categories_combo->AddString(categories_text[cat]);
   }
   categories_combo->SetWindowTextW(L"Select Category");


   CComboBox *notes_combo = (CComboBox*)GetDlgItem(IDC_COMBO_NOTE_BASE);
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

   if (MusicStaff1)
   {
      GetClientRect(&rect);
      int clientWidth = rect.Width();
      MusicStaff1->MoveWindow(10, 150, clientWidth - 20, 140);
      MusicStaff1->ShowWindow(SW_SHOW);
   }

   if (MusicStaff2)
   {
      GetClientRect(&rect);
      int clientWidth = rect.Width();
      MusicStaff2->MoveWindow(10, 250, clientWidth - 20, 140);
      MusicStaff2->ShowWindow(SW_SHOW);
   }

   if (GuitarNeck)
   {
      GetClientRect(&rect);
      int clientWidth = rect.Width();
      GuitarNeck->MoveWindow(10, 150, clientWidth - 20, 175);
      GuitarNeck->ShowWindow(SW_SHOW);
   }

   SetDlgItemText(IDC_MainText, startup_text);

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
   CComboBox *categories_combo = (CComboBox*)GetDlgItem(IDC_COMBO_CATEGORIES);
   CComboBox *subcategories_combo = (CComboBox*)GetDlgItem(IDC_COMBO_SUBCATEGORIES);
   CButton *test_box = (CButton*)GetDlgItem(IDC_TEST_MODE);

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
   
   switch (index)
   {
   case e_note_lengths:
      SetDlgItemText(IDC_MainText, note_length_info_text);
      num_sub_categories = e_max_lengths;
      sub_categories = note_length_text;
      break;
   case e_rest_types:
      SetDlgItemText(IDC_MainText, rest_length_info_text);
      num_sub_categories = e_max_lengths;
      sub_categories = note_length_text;
      break;
   case e_note_values:
      SetDlgItemText(IDC_MainText, note_value_info_text);
      on_note_value_category();
      break;
   case e_rhythm_patterns:
      SetDlgItemText(IDC_MainText, rhythms_info_text);
      num_sub_categories = e_max_rhythm_patterns;
      sub_categories = rhythms_text;
      break;
   case e_scales:
      SetDlgItemText(IDC_MainText, scales_info_text);
      dispNoteCombo = true;
      num_sub_categories = e_max_scales;
      sub_categories = scale_text;
      break;
   case e_music_keys:
      SetDlgItemText(IDC_MainText, keys_info_text);
      dispNoteCombo = true;
      on_key_changed();
      break;
   case e_note_mapping:
      SetDlgItemText(IDC_MainText, mapping_info_text);
      dispNoteCombo = true;
      extCombo = true;
      MusicStaff1->ShowWindow(SW_HIDE);
      MusicStaff2->ShowWindow(SW_HIDE);
      GuitarNeck->ShowWindow(SW_SHOW);

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
   CComboBox *categories_combo = (CComboBox*)GetDlgItem(IDC_COMBO_CATEGORIES);
   CComboBox *subcategories_combo = (CComboBox*)GetDlgItem(IDC_COMBO_SUBCATEGORIES);
   CComboBox *notes_combo = (CComboBox*)GetDlgItem(IDC_COMBO_NOTE_BASE);
   int noteSel = notes_combo->CComboBox::GetCurSel();
   int catIdx = categories_combo->CComboBox::GetCurSel();
   int subcatIdx = subcategories_combo->CComboBox::GetCurSel();

   int num_sub_categories = 0;

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
   CComboBox *notes_combo = (CComboBox*)GetDlgItem(IDC_COMBO_NOTE_BASE);
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
   CComboBox *notes_combo = (CComboBox*)GetDlgItem(IDC_COMBO_NOTE_BASE);
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
   /*case e_rhythm_pattern_14:
      size = sizeof(pattern14) / sizeof(int);
      pattern = pattern14;
      break;
   case e_rhythm_pattern_15:
      size = sizeof(pattern15) / sizeof(int);
      pattern = pattern15;
      break;
   case e_rhythm_pattern_16:
      size = sizeof(pattern16) / sizeof(int);
      pattern = pattern16;
      break;
   case e_rhythm_pattern_17:
      size = sizeof(pattern17) / sizeof(int);
      pattern = pattern17;
      break;
   case e_rhythm_pattern_18:
      size = sizeof(pattern18) / sizeof(int);
      pattern = pattern18;
      break;
   case e_rhythm_pattern_19:
      size = sizeof(pattern19) / sizeof(int);
      pattern = pattern19;
      break;
   case e_rhythm_pattern_20:
      size = sizeof(pattern20) / sizeof(int);
      pattern = pattern20;
      break;*/
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

   CButton *test_box = (CButton*)GetDlgItem(IDC_TEST_MODE);
   bool test = (test_box->GetCheck() != FALSE);

   // Clear the staffs
   MusicStaff1->Invalidate();
   MusicStaff2->Invalidate();

   // Draw trebble staff
   MusicStaff1->draw_notes(&data, e_trebble_clef, 4, 4, key, isRhythm, test);
   MusicStaff1->UpdateWindow();
   MusicStaff1->GetClientRect(&rect);

   // Draw bass staff
   if (draw_bass_clef)
   {
      MusicStaff2->ShowWindow(SW_SHOW);
      MusicStaff2->MoveWindow(10, 150 + rect.Height() + 10,
         rect.Width(), rect.Height(), TRUE);
      MusicStaff2->UpdateWindow();
      MusicStaff2->draw_notes(&data, e_bass_clef, 4, 4, key, isRhythm, test);
      MusicStaff2->UpdateWindow();
   }
   else
   {
      MusicStaff2->ShowWindow(SW_HIDE);
   }
}

void CITSMusic101Dlg::ShowNotesBox(bool show, bool ext)
{
   CComboBox *notes_combo = (CComboBox*)GetDlgItem(IDC_COMBO_NOTE_BASE);
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
   std::wstring ret = MusicStaff1->checkDataText();

   if (MusicStaff2->IsWindowVisible())
   {
      ret += MusicStaff2->checkDataText();
   }

   SetDlgItemText(IDC_MainText, ret.c_str());

   std::ofstream file("log.txt", std::ios::app);
   file << (LPCSTR)CT2A(ret.c_str());
   file.close();
}

void CITSMusic101Dlg::OnRecord()
{
   NPipe::CPipe pipe;
   m_recording = !m_recording;
   
   if (m_recording)
   {
      SetDlgItemText(IDC_RECORD, L"Stop");
      pipe.StartRecordingToFile();
   }
   else
   {
      pipe.StopRecordingToFile();
      SetDlgItemText(IDC_RECORD, L"Record");
   }
}

void CITSMusic101Dlg::OnTestRecord()
{
}
