#if !defined(AFX_CHAREDITOR_H__40A8E462_06C5_11D2_AC44_444553540000__INCLUDED_)
#define AFX_CHAREDITOR_H__40A8E462_06C5_11D2_AC44_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CharEditor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCharEditor dialog

class CCharEditor : public CDialog
{
// Construction
public:
	CCharEditor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCharEditor)
	enum { IDD = IDD_CHARACTER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCharEditor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCharEditor)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeName();
	afx_msg void OnSelchangeClass();
	afx_msg void OnChangeLevel();
	afx_msg void OnChangeLevelup();
	afx_msg void OnChangeExp();
	afx_msg void OnChangeStr();
	afx_msg void OnChangeMag();
	afx_msg void OnChangeDex();
	afx_msg void OnChangeVit();
	afx_msg void OnChangeLife();
	afx_msg void OnChangeMana();
	afx_msg void OnSave();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAREDITOR_H__40A8E462_06C5_11D2_AC44_444553540000__INCLUDED_)
