// bobminDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bobmin.h"
#include "bobminDlg.h"
#include "CharSel.h"
#include "ItemTrader.h"
#include "CharEditor.h"
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char szHeader[] = "DIABLO CHAR FILE\r\n1\x1a\0";
const char szITM[] = "ITM01.I'll get that al'Thor!\0\0\0";
CHARACTER cMain;
char szName1[32];
char szName2[32];
char szName3[32];
char szName4[32];
int nResult;
BOOL bCanceled;

DWORD dwRealCharOffset;
DWORD dwRealCharOffsetPtr;
DWORD dwChaCharOffset;
DWORD dwCharacterSpacing;
DWORD dwPermanentNameOffset;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBOBMINDlg dialog

CBOBMINDlg::CBOBMINDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBOBMINDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBOBMINDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBOBMINDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBOBMINDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBOBMINDlg, CDialog)
	//{{AFX_MSG_MAP(CBOBMINDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_RESTORE, OnRestore)
	ON_BN_CLICKED(IDC_ADDON1, OnAddon1)
	ON_BN_CLICKED(IDC_ADDON2, OnAddon2)
	ON_BN_CLICKED(IDC_ADDON3, OnAddon3)
	ON_BN_CLICKED(IDC_ADDON4, OnAddon4)
	ON_BN_CLICKED(IDC_ADDON5, OnAddon5)
	ON_BN_CLICKED(IDC_ITEMS, OnItems)
	ON_BN_CLICKED(IDC_CHARACTER, OnCharacter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBOBMINDlg message handlers

BOOL CBOBMINDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);

	char szDesc1[256];
	char szDesc2[256];
	char szDesc3[256];
	char szDesc4[256];
	char szDesc5[256];

	GetPrivateProfileString("Add-Ons", "AddOn1Desc", "\0", szDesc1, 256, "bobmin.ini");
	GetPrivateProfileString("Add-Ons", "AddOn2Desc", "\0", szDesc2, 256, "bobmin.ini");
	GetPrivateProfileString("Add-Ons", "AddOn3Desc", "\0", szDesc3, 256, "bobmin.ini");
	GetPrivateProfileString("Add-Ons", "AddOn4Desc", "\0", szDesc4, 256, "bobmin.ini");
	GetPrivateProfileString("Add-Ons", "AddOn5Desc", "\0", szDesc5, 256, "bobmin.ini");
	
	m_tooltip.AddTool(GetDlgItem(IDC_SAVE), "Saves your character.");
	m_tooltip.AddTool(GetDlgItem(IDC_RESTORE), "Restores your character.");
	m_tooltip.AddTool(GetDlgItem(IDC_ITEMS), "Edits your items.");
	m_tooltip.AddTool(GetDlgItem(IDC_CHARACTER), "Edits your character.");
	m_tooltip.AddTool(GetDlgItem(IDC_ADDON1), szDesc1[0] ? szDesc1 : "Shift-click to change or add.");
	m_tooltip.AddTool(GetDlgItem(IDC_ADDON2), szDesc2[0] ? szDesc2 : "Shift-click to change or add.");
	m_tooltip.AddTool(GetDlgItem(IDC_ADDON3), szDesc3[0] ? szDesc2 : "Shift-click to change or add.");
	m_tooltip.AddTool(GetDlgItem(IDC_ADDON4), szDesc4[0] ? szDesc3 : "Shift-click to change or add.");
	m_tooltip.AddTool(GetDlgItem(IDC_ADDON5), szDesc5[0] ? szDesc4 : "Shift-click to change or add.");

	DWORD dwProcId;
	HANDLE hDiablo;

	GetWindowThreadProcessId(::FindWindow("DIABLO", "DIABLO"), &dwProcId);
	hDiablo = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcId);
	if (hDiablo)
	{
		if (GetDiabloVersion(hDiablo) == 8)
		{
			dwRealCharOffset = REAL_CHAR_OFFSET_108;
//			MessageBox("Diablo v1.08", AfxGetAppName(), MB_OK|MB_ICONEXCLAMATION);
			dwChaCharOffset = CHA_CHAR_OFFSET_108;
			dwCharacterSpacing = CHARACTER_SPACING_108;
			dwPermanentNameOffset = PERMANENT_NAME_108;
		}
		if (GetDiabloVersion(hDiablo) == 7)
		{
			dwRealCharOffset = REAL_CHAR_OFFSET_107;
//			MessageBox("Diablo v1.07", AfxGetAppName(), MB_OK|MB_ICONEXCLAMATION);
			dwChaCharOffset = CHA_CHAR_OFFSET_107;
			dwCharacterSpacing = CHARACTER_SPACING_107;
			dwPermanentNameOffset = PERMANENT_NAME_107;
		}
		if (GetDiabloVersion(hDiablo) == 5)
		{
			dwRealCharOffset = REAL_CHAR_OFFSET_105;
//			MessageBox("Diablo v1.05", AfxGetAppName(), MB_OK|MB_ICONEXCLAMATION);
			dwChaCharOffset = CHA_CHAR_OFFSET_105;
			dwCharacterSpacing = CHARACTER_SPACING_105;
			dwPermanentNameOffset = PERMANENT_NAME_105;
		}
		if (GetDiabloVersion(hDiablo) == 4)
		{
			dwRealCharOffsetPtr = REAL_CHAR_OFFSET_PTR_104;
			MessageBox("The Diablo v1.04 support is REALLY bad!", AfxGetAppName(), MB_OK|MB_ICONEXCLAMATION);
			dwCharacterSpacing = CHARACTER_SPACING_104;
			dwPermanentNameOffset = PERMANENT_NAME_104;
		}
	}

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBOBMINDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBOBMINDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CBOBMINDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBOBMINDlg::OnSave() 
{
	CFileDialog *fd;
	CString s;

	char name[32];

	HANDLE hDiablo = GetHandle();
	if (!hDiablo)
		return;

	GetNames();
	CCharSel dlg;
	dlg.DoModal();

	if (nResult == -1)
		return;

	char *p = (char *)&cMain.character[0x7E];
	GetBuffer(hDiablo, nResult);
	strcpy(name, p);

	fd = new CFileDialog(FALSE, "CHA", name, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, "Diablo Character Files (*.CHA)|*.CHA|All Files (*.*)|*.*||");
	if (fd->DoModal() == IDCANCEL)
	{
		delete fd;
		return;
	}
	s = fd->GetFileName();
	delete fd;

	FILE *fp = fopen(s, "wb");
	if (!fp)
	{
		MessageBox("Unable to dump to file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	fwrite(&szHeader, 22, 1, fp);
	fwrite(&cMain, sizeof(cMain), 1, fp);
	fclose(fp);
	CloseHandle(hDiablo);

	MessageBox("Successfully dumped to file!", AfxGetAppName(), MB_OK|MB_ICONINFORMATION);
}

void CBOBMINDlg::OnRestore() 
{	
	CFileDialog *fd;
	CString s;

	HANDLE hDiablo = GetHandle();
	if (!hDiablo)
		return;

	char header[22];
	
	GetNames();
	CCharSel dlg;
	dlg.DoModal();

	if (nResult == -1)
		return;

	fd = new CFileDialog(TRUE, "CHA", "*.CHA", OFN_HIDEREADONLY|OFN_FILEMUSTEXIST, "Diablo Character Files (*.CHA)|*.CHA|All Files (*.*)|*.*||");
	if (fd->DoModal() == IDCANCEL)
	{
		delete fd;
		return;
	}
	s = fd->GetFileName();
	delete fd;
	
	FILE *fp = fopen(s, "rb");
	if (!fp)
	{
		MessageBox("Unable to open file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	fread(&header, 22, 1, fp);
	if (strcmp(szHeader, header) != 0)
	{
		fclose(fp);
		MessageBox("Invalid file format!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	fread(&cMain, sizeof(cMain), 1, fp);
	fclose(fp);

	WriteBuffer(hDiablo, nResult);
	CloseHandle(hDiablo);

	MessageBox("Successfully restored character!", AfxGetAppName(), MB_OK|MB_ICONINFORMATION);
}

HANDLE CBOBMINDlg::GetHandle()
{
	HWND hDiablo;
	DWORD dwProcId;

	hDiablo = ::FindWindow("DIABLO", "DIABLO");

	if (!hDiablo)
	{
		MessageBox("Diablo is not running!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return NULL;
	}
	GetWindowThreadProcessId(hDiablo, &dwProcId);
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcId);
}

void CBOBMINDlg::OnAddon1() 
{
	if (GetAsyncKeyState(VK_SHIFT) == -32767)
	{
		CFileDialog *fd;
		CString s;
		fd = new CFileDialog(TRUE, "EXE", NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST, "Program Files (*.EXE)|*.EXE|All Files (*.*)|*.*||");
		if (fd->DoModal() == IDCANCEL)
		{
			delete fd;
			return;
		}
		s = fd->GetPathName();
		delete fd;

		char szDesc[256];
		strcpy(szDesc, s);
		
		char *p = szDesc;
		char *q;
		char *lpszDesc;

		q = strchr(p, '\\');

		while (q)
		{
			p = ++q;
			q = strchr(p, '\\');
		}

		lpszDesc = p;

		q = strchr(p, '.');
		while (q)
		{
			p = ++q;
			q = strchr(p, '.');
		}
		
		if (p)
		{
			p--;
			*p = '\0';
		}
		
		WritePrivateProfileString("Add-Ons", "AddOn1", s, "bobmin.ini");
		WritePrivateProfileString("Add-Ons", "AddOn1Desc", lpszDesc, "bobmin.ini");
		m_tooltip.AddTool(GetDlgItem(IDC_ADDON1), lpszDesc);
		return;
	}

	char szApp[MAX_PATH];
	
	HANDLE hDiablo = GetHandle();
	if (!hDiablo)
		return;

	GetPrivateProfileString("Add-Ons", "AddOn1", "\0", szApp, MAX_PATH, "bobmin.ini");

	GetNames();
	CCharSel dlg;
	dlg.DoModal();

	if (nResult == -1)
		return;

	GetBuffer(hDiablo, nResult);

	FILE *fp = fopen("C:\\Temp_BMT.CHA", "wb");
	if (!fp)
	{
		MessageBox("Unable to write to file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	fwrite(&szHeader, 22, 1, fp);
	fwrite(&cMain, sizeof(cMain), 1, fp);
	fclose(fp);

	if (spawnlp(_P_WAIT, szApp, szApp, "C:\\Temp_BMT.CHA", NULL) == -1)
	{
		MessageBox("Could not spawn external program!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	
	char header[22];
	fp = fopen("C:\\Temp_BMT.CHA", "rb");
	if (!fp)
	{
		MessageBox("Unable to open file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}

	fread(&header, 22, 1, fp);
	if (strcmp(szHeader, header) != 0)
	{
		fclose(fp);
		MessageBox("Invalid file format!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}

	fread(&cMain, sizeof(cMain), 1, fp);
	fclose(fp);

	WriteBuffer(hDiablo, nResult);
	CloseHandle(hDiablo);

	MessageBox("Add-On returned successfully. Character modified.", AfxGetAppName(), MB_OK|MB_ICONINFORMATION);
}

void CBOBMINDlg::GetNames()
{
	HANDLE hDiablo = GetHandle();
	if (!hDiablo)
		return;

	szName1[0] = '\0';
	szName2[0] = '\0';
	szName3[0] = '\0';
	szName4[0] = '\0';

	BOOL bRet;

	if (GetDiabloVersion(hDiablo) == 5 || GetDiabloVersion(hDiablo) == 7|| GetDiabloVersion(hDiablo) == 8)
	{
		bRet = ReadProcessMemory(hDiablo, (LPVOID)(dwRealCharOffset + 0x140 + (0 * dwCharacterSpacing)), &szName1, 32, NULL);
		if (bRet == 0)
			return;
		ReadProcessMemory(hDiablo, (LPVOID)(dwRealCharOffset + 0x140 + (1 * dwCharacterSpacing)), &szName2, 32, NULL);
		ReadProcessMemory(hDiablo, (LPVOID)(dwRealCharOffset + 0x140 + (2 * dwCharacterSpacing)), &szName3, 32, NULL);
		ReadProcessMemory(hDiablo, (LPVOID)(dwRealCharOffset + 0x140 + (3 * dwCharacterSpacing)), &szName4, 32, NULL);
	}
	if (GetDiabloVersion(hDiablo) == 4)
	{
		char *c;
		bRet = ReadProcessMemory(hDiablo, (LPVOID)0x4A3188, &c, 4, NULL);
		if (bRet == 0)
			return;
		ReadProcessMemory(hDiablo, (LPVOID)(c + 0x0140), &szName1, 32, NULL);
		ReadProcessMemory(hDiablo, (LPVOID)(c + 0x5618), &szName2, 32, NULL);
		ReadProcessMemory(hDiablo, (LPVOID)(c + 0xAAF0), &szName3, 32, NULL);
		ReadProcessMemory(hDiablo, (LPVOID)(c + 0xFFC8), &szName4, 32, NULL);
	}
}

void CBOBMINDlg::OnAddon2() 
{
	if (GetAsyncKeyState(VK_SHIFT) == -32767)
	{
		CFileDialog *fd;
		CString s;
		fd = new CFileDialog(TRUE, "EXE", NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST, "Program Files (*.EXE)|*.EXE|All Files (*.*)|*.*||");
		if (fd->DoModal() == IDCANCEL)
		{
			delete fd;
			return;
		}
		s = fd->GetPathName();
		delete fd;
		
		char szDesc[256];
		strcpy(szDesc, s);
		
		char *p = szDesc;
		char *q;
		char *lpszDesc;

		q = strchr(p, '\\');

		while (q)
		{
			p = ++q;
			q = strchr(p, '\\');
		}

		lpszDesc = p;

		q = strchr(p, '.');
		while (q)
		{
			p = ++q;
			q = strchr(p, '.');
		}
		
		if (p)
		{
			p--;
			*p = '\0';
		}
		
		WritePrivateProfileString("Add-Ons", "AddOn2", s, "bobmin.ini");
		WritePrivateProfileString("Add-Ons", "AddOn2Desc", lpszDesc, "bobmin.ini");
		m_tooltip.AddTool(GetDlgItem(IDC_ADDON2), lpszDesc);
		return;
	}

	char szApp[MAX_PATH];
	
	HANDLE hDiablo = GetHandle();
	if (!hDiablo)
		return;

	GetPrivateProfileString("Add-Ons", "AddOn2", "\0", szApp, MAX_PATH, "bobmin.ini");

	GetNames();
	CCharSel dlg;
	dlg.DoModal();

	if (nResult == -1)
		return;

	GetBuffer(hDiablo, nResult);
	FILE *fp = fopen("C:\\Temp_BMT.CHA", "wb");
	if (!fp)
	{
		MessageBox("Unable to write to file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	fwrite(&szHeader, 22, 1, fp);
	fwrite(&cMain, sizeof(cMain), 1, fp);
	fclose(fp);

	if (spawnlp(_P_WAIT, szApp, szApp, "C:\\Temp_BMT.CHA", NULL) == -1)
	{
		MessageBox("Could not spawn external program!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	
	char header[22];
	fp = fopen("C:\\Temp_BMT.CHA", "rb");
	if (!fp)
	{
		MessageBox("Unable to open file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}

	fread(&header, 22, 1, fp);
	if (strcmp(szHeader, header) != 0)
	{
		fclose(fp);
		MessageBox("Invalid file format!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}

	fread(&cMain, sizeof(cMain), 1, fp);
	fclose(fp);

	WriteBuffer(hDiablo, nResult);
	CloseHandle(hDiablo);

	MessageBox("Add-On returned successfully. Character modified.", AfxGetAppName(), MB_OK|MB_ICONINFORMATION);
}

void CBOBMINDlg::OnAddon3() 
{
	if (GetAsyncKeyState(VK_SHIFT) == -32767)
	{
		CFileDialog *fd;
		CString s;
		fd = new CFileDialog(TRUE, "EXE", NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST, "Program Files (*.EXE)|*.EXE|All Files (*.*)|*.*||");
		if (fd->DoModal() == IDCANCEL)
		{
			delete fd;
			return;
		}
		s = fd->GetPathName();
		delete fd;
		
		char szDesc[256];
		strcpy(szDesc, s);
		
		char *p = szDesc;
		char *q;
		char *lpszDesc;

		q = strchr(p, '\\');

		while (q)
		{
			p = ++q;
			q = strchr(p, '\\');
		}

		lpszDesc = p;

		q = strchr(p, '.');
		while (q)
		{
			p = ++q;
			q = strchr(p, '.');
		}
		
		if (p)
		{
			p--;
			*p = '\0';
		}
		
		WritePrivateProfileString("Add-Ons", "AddOn3", s, "bobmin.ini");
		WritePrivateProfileString("Add-Ons", "AddOn3Desc", lpszDesc, "bobmin.ini");
		m_tooltip.AddTool(GetDlgItem(IDC_ADDON3), lpszDesc);
		return;
	}

	char szApp[MAX_PATH];

	HANDLE hDiablo = GetHandle();
	if (!hDiablo)
		return;

	GetPrivateProfileString("Add-Ons", "AddOn3", "\0", szApp, MAX_PATH, "bobmin.ini");

	GetNames();
	CCharSel dlg;
	dlg.DoModal();

	if (nResult == -1)
		return;

	GetBuffer(hDiablo, nResult);
	FILE *fp = fopen("C:\\Temp_BMT.CHA", "wb");
	if (!fp)
	{
		MessageBox("Unable to write to file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	fwrite(&szHeader, 22, 1, fp);
	fwrite(&cMain, sizeof(cMain), 1, fp);
	fclose(fp);

	if (spawnlp(_P_WAIT, szApp, szApp, "C:\\Temp_BMT.CHA", NULL) == -1)
	{
		MessageBox("Could not spawn external program!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	
	char header[22];
	fp = fopen("C:\\Temp_BMT.CHA", "rb");
	if (!fp)
	{
		MessageBox("Unable to open file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}

	fread(&header, 22, 1, fp);
	if (strcmp(szHeader, header) != 0)
	{
		fclose(fp);
		MessageBox("Invalid file format!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}

	fread(&cMain, sizeof(cMain), 1, fp);
	fclose(fp);

	WriteBuffer(hDiablo, nResult);
	CloseHandle(hDiablo);

	MessageBox("Add-On returned successfully. Character modified.", AfxGetAppName(), MB_OK|MB_ICONINFORMATION);
}

void CBOBMINDlg::OnAddon4() 
{
	if (GetAsyncKeyState(VK_SHIFT) == -32767)
	{
		CFileDialog *fd;
		CString s;
		fd = new CFileDialog(TRUE, "EXE", NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST, "Program Files (*.EXE)|*.EXE|All Files (*.*)|*.*||");
		if (fd->DoModal() == IDCANCEL)
		{
			delete fd;
			return;
		}
		s = fd->GetPathName();
		delete fd;
		
		char szDesc[256];
		strcpy(szDesc, s);
		
		char *p = szDesc;
		char *q;
		char *lpszDesc;

		q = strchr(p, '\\');

		while (q)
		{
			p = ++q;
			q = strchr(p, '\\');
		}

		lpszDesc = p;

		q = strchr(p, '.');
		while (q)
		{
			p = ++q;
			q = strchr(p, '.');
		}
		
		if (p)
		{
			p--;
			*p = '\0';
		}
		
		WritePrivateProfileString("Add-Ons", "AddOn4", s, "bobmin.ini");
		WritePrivateProfileString("Add-Ons", "AddOn4Desc", lpszDesc, "bobmin.ini");
		m_tooltip.AddTool(GetDlgItem(IDC_ADDON4), lpszDesc);
		return;
	}

	char szApp[MAX_PATH];

	HANDLE hDiablo = GetHandle();
	if (!hDiablo)
		return;

	GetPrivateProfileString("Add-Ons", "AddOn4", "\0", szApp, MAX_PATH, "bobmin.ini");

	GetNames();
	CCharSel dlg;
	dlg.DoModal();

	if (nResult == -1)
		return;

	GetBuffer(hDiablo, nResult);
	FILE *fp = fopen("C:\\Temp_BMT.CHA", "wb");
	if (!fp)
	{
		MessageBox("Unable to write to file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	fwrite(&szHeader, 22, 1, fp);
	fwrite(&cMain, sizeof(cMain), 1, fp);
	fclose(fp);

	if (spawnlp(_P_WAIT, szApp, szApp, "C:\\Temp_BMT.CHA", NULL) == -1)
	{
		MessageBox("Could not spawn external program!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	
	char header[22];
	fp = fopen("C:\\Temp_BMT.CHA", "rb");
	if (!fp)
	{
		MessageBox("Unable to open file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}

	fread(&header, 22, 1, fp);
	if (strcmp(szHeader, header) != 0)
	{
		fclose(fp);
		MessageBox("Invalid file format!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}

	fread(&cMain, sizeof(cMain), 1, fp);
	fclose(fp);

	WriteBuffer(hDiablo, nResult);
	CloseHandle(hDiablo);

	MessageBox("Add-On returned successfully. Character modified.", AfxGetAppName(), MB_OK|MB_ICONINFORMATION);
}

void CBOBMINDlg::OnAddon5() 
{
	if (GetAsyncKeyState(VK_SHIFT) == -32767)
	{
		CFileDialog *fd;
		CString s;
		fd = new CFileDialog(TRUE, "EXE", NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST, "Program Files (*.EXE)|*.EXE|All Files (*.*)|*.*||");
		if (fd->DoModal() == IDCANCEL)
		{
			delete fd;
			return;
		}
		s = fd->GetPathName();
		delete fd;
		
		char szDesc[256];
		strcpy(szDesc, s);
		
		char *p = szDesc;
		char *q;
		char *lpszDesc;

		q = strchr(p, '\\');

		while (q)
		{
			p = ++q;
			q = strchr(p, '\\');
		}

		lpszDesc = p;

		q = strchr(p, '.');
		while (q)
		{
			p = ++q;
			q = strchr(p, '.');
		}
		
		if (p)
		{
			p--;
			*p = '\0';
		}
		
		WritePrivateProfileString("Add-Ons", "AddOn5", s, "bobmin.ini");
		WritePrivateProfileString("Add-Ons", "AddOn5Desc", lpszDesc, "bobmin.ini");
		m_tooltip.AddTool(GetDlgItem(IDC_ADDON5), lpszDesc);
		return;
	}

	char szApp[MAX_PATH];

	HANDLE hDiablo = GetHandle();
	if (!hDiablo)
		return;

	GetPrivateProfileString("Add-Ons", "AddOn5", "\0", szApp, MAX_PATH, "bobmin.ini");

	GetNames();
	CCharSel dlg;
	dlg.DoModal();

	if (nResult == -1)
		return;

	GetBuffer(hDiablo, nResult);
	FILE *fp = fopen("C:\\Temp_BMT.CHA", "wb");
	if (!fp)
	{
		MessageBox("Unable to write to file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	fwrite(&szHeader, 22, 1, fp);
	fwrite(&cMain, sizeof(cMain), 1, fp);
	fclose(fp);

	if (spawnlp(_P_WAIT, szApp, szApp, "C:\\Temp_BMT.CHA", NULL) == -1)
	{
		MessageBox("Could not spawn external program!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	
	char header[22];
	fp = fopen("C:\\Temp_BMT.CHA", "rb");
	if (!fp)
	{
		MessageBox("Unable to open file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}

	fread(&header, 22, 1, fp);
	if (strcmp(szHeader, header) != 0)
	{
		fclose(fp);
		MessageBox("Invalid file format!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}

	fread(&cMain, sizeof(cMain), 1, fp);
	fclose(fp);

	WriteBuffer(hDiablo, nResult);
	CloseHandle(hDiablo);

	MessageBox("Add-On returned successfully. Character modified.", AfxGetAppName(), MB_OK|MB_ICONINFORMATION);
}

void CBOBMINDlg::OnItems() 
{
	HANDLE hDiablo = GetHandle();
	if (!hDiablo)
		return;

	GetNames();
	CCharSel dlg;
	dlg.DoModal();

	if (nResult == -1)
		return;

	GetBuffer(hDiablo, nResult);
	
	CItemTrader cit;
	cit.DoModal();

	if (!bCanceled)
	{
		WriteBuffer(hDiablo, nResult);
		CloseHandle(hDiablo);
	
		MessageBox("Items changed successfully!", AfxGetAppName(), MB_OK|MB_ICONINFORMATION);
	}
	else
		CloseHandle(hDiablo);
}

void CBOBMINDlg::OnCharacter() 
{
	HANDLE hDiablo = GetHandle();
	if (!hDiablo)
		return;

	GetNames();
	CCharSel dlg;
	dlg.DoModal();

	if (nResult == -1)
		return;

	GetBuffer(hDiablo, nResult);

	CCharEditor cce;
	cce.DoModal();

	if (!bCanceled)
	{
		WriteBuffer(hDiablo, nResult);
		CloseHandle(hDiablo);
	
		MessageBox("Character changed successfully!", AfxGetAppName(), MB_OK|MB_ICONINFORMATION);
	}
	else
		CloseHandle(hDiablo);
}

BOOL CBOBMINDlg::GetBuffer(HANDLE hDiablo, int nIndex)
{
	if (GetDiabloVersion(hDiablo) == 5 || GetDiabloVersion(hDiablo) == 7 || GetDiabloVersion(hDiablo) == 8)
	{
//		bRet = ReadProcessMemory(hDiablo, (LPVOID)(dwRealCharOffset + (nIndex * dwCharacterSpacing)), &cRealMain, sizeof(cRealMain), NULL);
//		if (bRet == 0)
//			return 0;
		return ReadProcessMemory(hDiablo, (LPVOID)(dwChaCharOffset + (nIndex * dwCharacterSpacing)), &cMain, sizeof(cMain), NULL);
	}
	if (GetDiabloVersion(hDiablo) == 4)
	{
		char *c = 0;
		BOOL bRet;

		SuspendThread(hDiablo);
		ReadProcessMemory(hDiablo, (LPVOID)0x4A3188, &c, 4, NULL);
		bRet = ReadProcessMemory(hDiablo, (LPVOID)(c + (nIndex * 0x54D8) + 0xC2), &cMain, sizeof(cMain), NULL);
		ResumeThread(hDiablo);
		
		return bRet;
	}

	MessageBox("An unsupported version of Diablo is running.", AfxGetAppName(), MB_OK|MB_ICONSTOP);
	return FALSE;
}

BOOL CBOBMINDlg::WriteBuffer(HANDLE hDiablo, int nIndex)
{
	if (GetDiabloVersion(hDiablo) == 5 || GetDiabloVersion(hDiablo) == 7 || GetDiabloVersion(hDiablo) == 8)
		return WriteProcessMemory(hDiablo, (LPVOID)(dwChaCharOffset + (nIndex * dwCharacterSpacing)), &cMain, sizeof(cMain), NULL);

	if (GetDiabloVersion(hDiablo) == 4)
	{
		char *c = 0;
		BOOL bRet;

		SuspendThread(hDiablo);
		ReadProcessMemory(hDiablo, (LPVOID)0x4A3188, &c, 4, NULL);
		bRet = WriteProcessMemory(hDiablo, (LPVOID)(c + (nIndex * dwCharacterSpacing) + 0xC2), &cMain, sizeof(cMain), NULL);
		ResumeThread(hDiablo);
		
		return bRet;
	}
	
	MessageBox("An unsupported version of Diablo is running.", AfxGetAppName(), MB_OK|MB_ICONSTOP);
	return FALSE;
}

BOOL CBOBMINDlg::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char szMessage[] = 
		"Get the latest version of this trainer from http://www.greatbobafett.com\r\n"
		"BoBaFeTT's Mini Diablo Trainer v6.7\r\n"
		"\xa9 2001 by Great_BoBaFeTT@hotmail.com\r\n"
		"This trainer has been developped mainly for backup purposes "
		"and item importing and exporting. It is designed to comply with "
		"the Battle.net End User Liscence Agreement.\r\n"
		"I am not responsible for anything you may do with this trainer. "
		"If you get banned from battle.net for cheating it's your fault, not "
		"mine.\r\n"
		"If you see the hex edited version of this trainer called\r\n"
		"Stu's Trainer, please delete it\r\n";

		SetDlgItemText(IDC_INFO, szMessage);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

DWORD CBOBMINDlg::GetDiabloVersion(HANDLE hDiablo)
{
	char szVersion[256];
	ReadProcessMemory(hDiablo, (LPVOID)VERSION_IDENTIFICATION_108, &szVersion, 6, NULL);
	if (stricmp(szVersion, "\377\025\264\260\107") == 0)
		return 8;

	ReadProcessMemory(hDiablo, (LPVOID)VERSION_IDENTIFICATION_107, &szVersion, 6, NULL);
	if (stricmp(szVersion, "\377\025\020\241\107") == 0)
		return 7;

	ReadProcessMemory(hDiablo, (LPVOID)VERSION_IDENTIFICATION_105, &szVersion, 6, NULL);
	if (stricmp(szVersion, "\377\025\324\260\111") == 0)
		return 5;

	ReadProcessMemory(hDiablo, (LPVOID)VERSION_IDENTIFICATION_104, &szVersion, 6, NULL);
	if (stricmp(szVersion, "\377\025\164\305\151") == 0)
		return 4;

	return 0;
}
