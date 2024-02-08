// bobminDlg.h : header file
//

#if !defined(AFX_BOBMINDLG_H__A34DB0E7_0586_11D2_AC44_444553540000__INCLUDED_)
#define AFX_BOBMINDLG_H__A34DB0E7_0586_11D2_AC44_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CBOBMINDlg dialog

class CBOBMINDlg : public CDialog
{
// Construction
public:
	DWORD GetDiabloVersion(HANDLE hDiablo);
	BOOL WriteBuffer(HANDLE hDiablo, int nIndex);
	BOOL GetBuffer(HANDLE hDiablo, int nIndex);
	void GetNames(void);
	HANDLE GetHandle(void);
	CBOBMINDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBOBMINDlg)
	enum { IDD = IDD_BOBMIN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBOBMINDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBOBMINDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSave();
	afx_msg void OnRestore();
	afx_msg void OnAddon1();
	afx_msg void OnAddon2();
	afx_msg void OnAddon3();
	afx_msg void OnAddon4();
	afx_msg void OnAddon5();
	afx_msg void OnItems();
	afx_msg void OnCharacter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOBMINDLG_H__A34DB0E7_0586_11D2_AC44_444553540000__INCLUDED_)
