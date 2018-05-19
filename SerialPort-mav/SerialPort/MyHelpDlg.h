#if !defined(AFX_MYHELPDLG_H__005BCB3B_825F_4770_A49A_093DEDC207A1__INCLUDED_)
#define AFX_MYHELPDLG_H__005BCB3B_825F_4770_A49A_093DEDC207A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyHelpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyHelpDlg dialog

class CMyHelpDlg : public CDialog
{
// Construction
public:
	CMyHelpDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyHelpDlg)
	enum { IDD = IDD_DIALOG_HELP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyHelpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyHelpDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYHELPDLG_H__005BCB3B_825F_4770_A49A_093DEDC207A1__INCLUDED_)
