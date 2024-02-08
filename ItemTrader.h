#if !defined(AFX_ITEMTRADER_H__2B6C0882_0601_11D2_AC44_444553540000__INCLUDED_)
#define AFX_ITEMTRADER_H__2B6C0882_0601_11D2_AC44_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ItemTrader.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CItemTrader dialog

class CItemTrader : public CDialog
{
// Construction
public:
	void Refresh(void);
	CItemTrader(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CItemTrader)
	enum { IDD = IDD_ITEM };
	CListBox m_items;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CItemTrader)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CItemTrader)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnImport();
	afx_msg void OnExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ITEMTRADER_H__2B6C0882_0601_11D2_AC44_444553540000__INCLUDED_)
