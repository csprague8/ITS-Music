#pragma once

#include "afxdialogex.h"
#include "resource.h"
#include "TeachingCategories.h"

#include <vector>
#include <map>


// CMusicStaffDlg dialog
class CMusicStaffDlg : public CDialogEx
{
   // Construction
public:
   CMusicStaffDlg(CWnd* pParent = NULL);	// standard constructor

   // Dialog Data
   enum { IDD = IDD_MUSICSTAFF_DIALOG };

protected:
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


   // Implementation
protected:
   HICON m_hIcon;

   // Generated message map functions
   virtual BOOL OnInitDialog();
   DECLARE_MESSAGE_MAP()

public:
   void draw_staff_lines(int width, int height, int h_offset = 0);
   void draw_notes(std::vector<note_info_t> *notes, 
      int clef, int sig_top, int sig_bottom, int key, 
      bool isRhythm, bool test = false);
   void move(int x, int y);
   void draw_connecting_lines(HDC hDC, int x, int y,
      int y2, int type);

   int draw_key(HDC hDC, int key, int clef, int x, int y);
   int draw_clef(HDC hDC, int clef, int x, int y);
   int draw_time_signiture(HDC hDC, int top, int bottom, int x, int y);

   std::wstring checkDataText();

public:
   std::map<HWND, std::wstring> edit_list;
};
