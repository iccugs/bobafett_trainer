#if !defined(AFX_CHARSEL_H__A34DB0EF_0586_11D2_AC44_444553540000__INCLUDED_)
#define AFX_CHARSEL_H__A34DB0EF_0586_11D2_AC44_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CharSel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCharSel dialog

class CCharSel : public CDialog
{
// Construction
public:
	CCharSel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCharSel)
	enum { IDD = IDD_CHARSEL };
	CButton m_char1;
	CButton m_char2;
	CButton m_char3;
	CButton m_char4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCharSel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCharSel)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChar1();
	afx_msg void OnChar2();
	afx_msg void OnChar3();
	afx_msg void OnChar4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARSEL_H__A34DB0EF_0586_11D2_AC44_444553540000__INCLUDED_)
