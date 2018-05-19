// MyHelpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "COMTOOL.h"
#include "MyHelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyHelpDlg dialog


CMyHelpDlg::CMyHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyHelpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyHelpDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMyHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyHelpDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyHelpDlg, CDialog)
	//{{AFX_MSG_MAP(CMyHelpDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyHelpDlg message handlers
