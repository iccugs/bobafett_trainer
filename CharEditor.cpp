// CharEditor.cpp : implementation file
//

#include "stdafx.h"
#include "bobmin.h"
#include "CharEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CHARACTER cBuf;

/////////////////////////////////////////////////////////////////////////////
// CCharEditor dialog


CCharEditor::CCharEditor(CWnd* pParent /*=NULL*/)
	: CDialog(CCharEditor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCharEditor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCharEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCharEditor)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCharEditor, CDialog)
	//{{AFX_MSG_MAP(CCharEditor)
	ON_EN_CHANGE(IDC_NAME, OnChangeName)
	ON_CBN_SELCHANGE(IDC_CLASS, OnSelchangeClass)
	ON_EN_CHANGE(IDC_LEVEL, OnChangeLevel)
	ON_EN_CHANGE(IDC_LEVELUP, OnChangeLevelup)
	ON_EN_CHANGE(IDC_EXP, OnChangeExp)
	ON_EN_CHANGE(IDC_STR, OnChangeStr)
	ON_EN_CHANGE(IDC_MAG, OnChangeMag)
	ON_EN_CHANGE(IDC_DEX, OnChangeDex)
	ON_EN_CHANGE(IDC_VIT, OnChangeVit)
	ON_EN_CHANGE(IDC_LIFE, OnChangeLife)
	ON_EN_CHANGE(IDC_MANA, OnChangeMana)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCharEditor message handlers

BOOL CCharEditor::OnInitDialog() 
{
	CDialog::OnInitDialog();

	memcpy(&cBuf, &cMain, sizeof(cMain));
	
	CComboBox *cbClass = (CComboBox *)GetDlgItem(IDC_CLASS);
	cbClass->SetItemData(0, 0);
	cbClass->SetItemData(1, 1);
	cbClass->SetItemData(2, 2);
	cbClass->SetCurSel(0);

	char *c = (char *)&cBuf.character[0x7E];
	long *l = (long *)&cBuf.character[0x9E];
	SetDlgItemText(IDC_NAME, c);

	cbClass->SetCurSel((int)*l);

	unsigned char *u = (unsigned char *)&cBuf.character[0xF6];
	SetDlgItemInt(IDC_LEVEL, *u);

	l = (long *)&cBuf.character[0xC2];
	SetDlgItemInt(IDC_LEVELUP, *l);
	l = (long *)&cBuf.character[0xFA];
	SetDlgItemInt(IDC_EXP, *l);
	//l = (long *)&cBuf.character[0x102];
	//SetDlgItemInt(IDC_NEXTLEVEL, *l);

	l = (long *)&cBuf.character[0xA2];
	SetDlgItemInt(IDC_STRCUR, *l);
	l = (long *)&cBuf.character[0xA6];
	SetDlgItemInt(IDC_STR, *l);

	l = (long *)&cBuf.character[0xAA];
	SetDlgItemInt(IDC_MAGCUR, *l);
	l = (long *)&cBuf.character[0xAE];
	SetDlgItemInt(IDC_MAG, *l);

	l = (long *)&cBuf.character[0xB2];
	SetDlgItemInt(IDC_DEXCUR, *l);
	l = (long *)&cBuf.character[0xB6];
	SetDlgItemInt(IDC_DEX, *l);

	l = (long *)&cBuf.character[0xBA];
	SetDlgItemInt(IDC_VITCUR, *l);
	l = (long *)&cBuf.character[0xBE];
	SetDlgItemInt(IDC_VIT, *l);

	l = (long *)&cBuf.character[0xD2];
	SetDlgItemInt(IDC_LIFE, (*l / 64));
	l = (long *)&cBuf.character[0xDA];
	SetDlgItemInt(IDC_LIFECUR, (*l / 64));

	l = (long *)&cBuf.character[0xE6];
	SetDlgItemInt(IDC_MANA, (*l / 64));
	l = (long *)&cBuf.character[0xEE];
	SetDlgItemInt(IDC_MANACUR, (*l / 64));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCharEditor::OnChangeName() 
{
	char *p = (char *)&cBuf.character[0x7E];
	char name[32];

	GetDlgItemText(IDC_NAME, name, 32);
	strcpy(p, name);
}

void CCharEditor::OnSelchangeClass() 
{
	CComboBox *cbClass = (CComboBox *)GetDlgItem(IDC_CLASS);
	long *p = (long *)&cBuf.character[0x9E];

	*p = cbClass->GetItemData(cbClass->GetCurSel());
}

void CCharEditor::OnChangeLevel() 
{
	unsigned char *p = (unsigned char *)&cBuf.character[0xF6];
	*p = GetDlgItemInt(IDC_LEVEL, NULL, FALSE);
}

void CCharEditor::OnChangeLevelup() 
{
	long *p = (long *)&cBuf.character[0xC2];
	*p = GetDlgItemInt(IDC_LEVELUP, NULL, TRUE);
}

void CCharEditor::OnChangeExp() 
{
	long *p = (long *)&cBuf.character[0xFA];
	*p = GetDlgItemInt(IDC_EXP, NULL, TRUE);
}

void CCharEditor::OnChangeStr() 
{
	long *p = (long *)&cBuf.character[0xA6];
	*p = GetDlgItemInt(IDC_STR, NULL, TRUE);
}

void CCharEditor::OnChangeMag() 
{
	long *p = (long *)&cBuf.character[0xAE];
	*p = GetDlgItemInt(IDC_MAG, NULL, TRUE);
}

void CCharEditor::OnChangeDex() 
{
	long *p = (long *)&cBuf.character[0xB6];
	*p = GetDlgItemInt(IDC_DEX, NULL, TRUE);
}

void CCharEditor::OnChangeVit() 
{
	long *p = (long *)&cBuf.character[0xBE];
	*p = GetDlgItemInt(IDC_VIT, NULL, TRUE);
}

void CCharEditor::OnChangeLife() 
{
	long *p = (long *)&cBuf.character[0xCE];
	*p = (GetDlgItemInt(IDC_LIFE, NULL, TRUE) * 64);
	p = (long *)&cBuf.character[0xD2];
	*p = (GetDlgItemInt(IDC_LIFE, NULL, TRUE) * 64);
	p = (long *)&cBuf.character[0xD6];
	*p = (GetDlgItemInt(IDC_LIFE, NULL, TRUE) * 64);
	p = (long *)&cBuf.character[0xDA];
	*p = (GetDlgItemInt(IDC_LIFE, NULL, TRUE) * 64);
}

void CCharEditor::OnChangeMana() 
{
	long *p = (long *)&cBuf.character[0xE2];
	*p = (GetDlgItemInt(IDC_MANA, NULL, TRUE) * 64);
	p = (long *)&cBuf.character[0xE6];
	*p = (GetDlgItemInt(IDC_MANA, NULL, TRUE) * 64);
	p = (long *)&cBuf.character[0xEA];
	*p = (GetDlgItemInt(IDC_MANA, NULL, TRUE) * 64);
	p = (long *)&cBuf.character[0xEE];
	*p = (GetDlgItemInt(IDC_MANA, NULL, TRUE) * 64);
}

void CCharEditor::OnSave() 
{
	char oldname[32];
	// Save the old name to search for position in stored location
	// I know there is still a problem that if the user changes the
	// name first and then later decides to change it a second
	// time and store that, this will not work.  I'll fix that later.
	strcpy(oldname, (char *)&cMain.character[0x7E]);

	// Copy temporary changes to permanent place for writing when
	// return to main dialog box.
	memcpy(&cMain, &cBuf, sizeof(cMain));

	CButton *cbPerm = (CButton *)GetDlgItem(IDC_PERMNAME);
	if (cbPerm->GetCheck())
	{
		HANDLE hDiablo;
		DWORD dwProcId;

		GetWindowThreadProcessId(::FindWindow("DIABLO", "DIABLO"), &dwProcId);
		hDiablo = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcId);

		if (!hDiablo)
		{
			MessageBox("Unable to permanently change name!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
			bCanceled = FALSE;
			CDialog::OnOK();
			return;
		}

		char name[32];
		char memname[32];

		memcpy(name, "\x00", 31);
		strcpy(name, (char *)&cMain.character[0x7E]);

		ReadProcessMemory(hDiablo, (LPVOID)dwPermanentNameOffset, &memname, 32, NULL);
		if (strcmp(oldname, memname) == 0)
		{
			WriteProcessMemory(hDiablo, (LPVOID)dwPermanentNameOffset, &name, strlen(name), NULL);
		}
		ReadProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0x20), &memname, 32, NULL);
		if (strcmp(oldname, memname) == 0)
		{
			WriteProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0x20), &name, strlen(name), NULL);
		}
		ReadProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0x40), &memname, 32, NULL);
		if (strcmp(oldname, memname) == 0)
		{
			WriteProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0x40), &name, strlen(name), NULL);
		}
		ReadProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0x60), &memname, 32, NULL);
		if (strcmp(oldname, memname) == 0)
		{
			WriteProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0x60), &name, strlen(name), NULL);
		}
		ReadProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0x80), &memname, 32, NULL);
		if (strcmp(oldname, memname) == 0)
		{
			WriteProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0x80), &name, strlen(name), NULL);
		}
		ReadProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0xa0), &memname, 32, NULL);
		if (strcmp(oldname, memname) == 0)
		{
			WriteProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0xa0), &name, strlen(name), NULL);
		}
		ReadProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0xc0), &memname, 32, NULL);
		if (strcmp(oldname, memname) == 0)
		{
			WriteProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0xc0), &name, strlen(name), NULL);
		}
		ReadProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0xe0), &memname, 32, NULL);
		if (strcmp(oldname, memname) == 0)
		{
			WriteProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0xe0), &name, strlen(name), NULL);
		}
		ReadProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0x100), &memname, 32, NULL);
		if (strcmp(oldname, memname) == 0)
		{
			WriteProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0x100), &name, strlen(name), NULL);
		}
		ReadProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0x120), &memname, 32, NULL);
		if (strcmp(oldname, memname) == 0)
		{
			WriteProcessMemory(hDiablo, (LPVOID)(dwPermanentNameOffset + 0x120), &name, strlen(name), NULL);
		}
		CloseHandle(hDiablo);
	}

	bCanceled = FALSE;
	CDialog::OnOK();
}

void CCharEditor::OnCancel() 
{
	bCanceled = TRUE;
	CDialog::OnCancel();
}
