// CharSel.cpp : implementation file
//

#include "stdafx.h"
#include "bobmin.h"
#include "CharSel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCharSel dialog


CCharSel::CCharSel(CWnd* pParent /*=NULL*/)
	: CDialog(CCharSel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCharSel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCharSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCharSel)
	DDX_Control(pDX, IDC_CHAR1, m_char1);
	DDX_Control(pDX, IDC_CHAR2, m_char2);
	DDX_Control(pDX, IDC_CHAR3, m_char3);
	DDX_Control(pDX, IDC_CHAR4, m_char4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCharSel, CDialog)
	//{{AFX_MSG_MAP(CCharSel)
	ON_BN_CLICKED(IDC_CHAR1, OnChar1)
	ON_BN_CLICKED(IDC_CHAR2, OnChar2)
	ON_BN_CLICKED(IDC_CHAR3, OnChar3)
	ON_BN_CLICKED(IDC_CHAR4, OnChar4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCharSel message handlers

BOOL CCharSel::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (szName1[0])
	{
		m_char1.SetWindowText(szName1);
		m_char1.EnableWindow(TRUE);
	}
	if (szName2[0])
	{
		m_char2.SetWindowText(szName2);
		m_char2.EnableWindow(TRUE);
	}
	if (szName3[0])
	{
		m_char3.SetWindowText(szName3);
		m_char3.EnableWindow(TRUE);
	}
	if (szName4[0])
	{
		m_char4.SetWindowText(szName4);
		m_char4.EnableWindow(TRUE);
	}
	
	if (m_char1.IsWindowEnabled())
		m_char1.SetCheck(1);

	nResult = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCharSel::OnOK() 
{	
	CDialog::OnOK();
}

void CCharSel::OnCancel() 
{	
	nResult = -1;
	CDialog::OnCancel();
}

void CCharSel::OnChar1() 
{
	m_char2.SetCheck(0);
	m_char3.SetCheck(0);
	m_char4.SetCheck(0);
	nResult = 0;
}

void CCharSel::OnChar2() 
{
	m_char1.SetCheck(0);
	m_char3.SetCheck(0);
	m_char4.SetCheck(0);
	nResult = 1;
}

void CCharSel::OnChar3() 
{
	m_char1.SetCheck(0);
	m_char2.SetCheck(0);
	m_char4.SetCheck(0);
	nResult = 2;
}

void CCharSel::OnChar4() 
{
	m_char1.SetCheck(0);
	m_char2.SetCheck(0);
	m_char3.SetCheck(0);
	nResult = 3;	
}
