
// ITS_Music_101Dlg.h : header file
//

#pragma once

#include "MusicStaffDlg.h"
#include "GuitarNeckDlg.h"
#include "Metronome.h"


// CITSMusic101Dlg dialog
class CITSMusic101Dlg : public CDialogEx
{
// Construction
public:
	CITSMusic101Dlg(CWnd* pParent = NULL);	// standard constructor
   ~CITSMusic101Dlg();

public:
   // Dialog Data
	enum { IDD = IDD_ITSMUSIC101_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
   afx_msg void OnPaint();
   afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
   afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg void OnStartStop();
   afx_msg void OnTempoUp();
   afx_msg void OnTempoDown();
   afx_msg void OnTempoChanged();
   afx_msg void OnCategoryChanged();
   afx_msg void OnSubCategoryChanged();
   afx_msg void OnCheckButton();

private:
   void on_note_value_category();
   void on_note_types_change(int note_type, bool isRest);
   void on_scale_changed(int scale_type);
   void on_clef_types();
   void on_key_changed();
   void on_rhythm_pattern_change(int rhythm_type);
   void draw_data(std::vector<note_info_t> data, bool draw_bass_clef,
      bool isRhythm, int key = C);
   void draw_neck_data();
   void ShowNotesBox(bool show, bool ext);
   void ShowCatBox(bool show);
   std::wstring get_check_info_text();

public:
   CMusicStaffDlg *MusicStaff1;
   CMusicStaffDlg *MusicStaff2;
   CGuitarNeckDlg *GuitarNeck;

   CComboBox *categories_combo = NULL;
   CComboBox *subcategories_combo = NULL;
   CComboBox *notes_combo = NULL;
   CButton *test_box = NULL;
   CEdit *maintxt = NULL;

private:
   Metronome metronome;

   bool m_running = false;
   bool m_recording = false;
};

