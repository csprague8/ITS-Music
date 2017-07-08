#pragma once

#include "afxdialogex.h"
#include "resource.h"
#include "TeachingCategories.h"

#include <vector>


// CGuitarNeckDlg dialog
class CGuitarNeckDlg : public CDialogEx
{
   // Construction
public:
   CGuitarNeckDlg(CWnd* pParent = NULL);	// standard constructor

   // Dialog Data
   enum { IDD = IDD_MUSICSTAFF_DIALOG };

protected:
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


   // Implementation
protected:
   // Generated message map functions
   virtual BOOL OnInitDialog();
   DECLARE_MESSAGE_MAP()

public:
   void draw_guitar_neck();
   void draw_not_positions(int note);
};
