// ItemTrader.cpp : implementation file
//

#include "stdafx.h"
#include "bobmin.h"
#include "ItemTrader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CHARACTER cBuffer;
/////////////////////////////////////////////////////////////////////////////
// CItemTrader dialog


CItemTrader::CItemTrader(CWnd* pParent /*=NULL*/)
	: CDialog(CItemTrader::IDD, pParent)
{
	//{{AFX_DATA_INIT(CItemTrader)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CItemTrader::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CItemTrader)
	DDX_Control(pDX, IDC_ITEMS, m_items);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CItemTrader, CDialog)
	//{{AFX_MSG_MAP(CItemTrader)
	ON_BN_CLICKED(IDC_IMPORT, OnImport)
	ON_BN_CLICKED(IDC_EXPORT, OnExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CItemTrader message handlers

BOOL CItemTrader::OnInitDialog() 
{
	CDialog::OnInitDialog();

	memcpy(&cBuffer, &cMain, sizeof(cMain));

	Refresh();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CItemTrader::OnOK() 
{
	memcpy(&cMain, &cBuffer, sizeof(cMain));
	bCanceled = FALSE;
	CDialog::OnOK();
}

void CItemTrader::OnCancel() 
{
	bCanceled = TRUE;
	CDialog::OnCancel();
}

void CItemTrader::OnImport() 
{
	int nItem = m_items.GetItemData(m_items.GetCurSel());

	CFileDialog *fd;
	CString s;

	fd = new CFileDialog(TRUE, "ITM", "*.ITM", OFN_HIDEREADONLY|OFN_PATHMUSTEXIST, "Item Files (*.ITM)|*.ITM|All Files (*.*)|*.*||");
	if (fd->DoModal() == IDCANCEL)
	{
		delete fd;
		return;
	}
	s = fd->GetFileName();
	delete fd;

	char hdr[32];
	ITEM itm;

	FILE *fp = fopen(s, "rb");
	if (!fp)
	{
		MessageBox("Unable to read from file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}

	fread(&hdr, 32, 1, fp);
	if (strcmp(szITM, hdr) != 0)
	{
		fclose(fp);
		MessageBox("Invalid file format!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	fread(&itm, sizeof(itm), 1, fp);
	fclose(fp);

	if (nItem >= 1 && nItem <= 40)
	{
		cBuffer.inventory[nItem - 1] = itm;
	}

	if (nItem >= 60 && nItem <= 66)
	{
		
		switch (nItem)
		{
		case 60:
			cBuffer.helm = itm;
			break;

		case 61:
			cBuffer.rring = itm;
			break;

		case 62:
			cBuffer.lring = itm;
			break;

		case 63:
			cBuffer.amulet = itm;
			break;

		case 64:
			cBuffer.rhand = itm;
			break;

		case 65:
			cBuffer.lhand = itm;
			break;

		case 66:
			cBuffer.armor = itm;
			break;
		}
	}

	if (nItem >= 70 && nItem <= 77)
	{
		cBuffer.belt[nItem - 70] = itm;
	}
	MessageBox("Successfully imported item!", AfxGetAppName(), MB_OK|MB_ICONINFORMATION);
	Refresh();
}

void CItemTrader::OnExport() 
{	
	int nItem = m_items.GetItemData(m_items.GetCurSel());

	CFileDialog *fd;
	CString s;

	ITEM itm;
	
	if (nItem >= 1 && nItem <= 40)
	{
		itm = cBuffer.inventory[nItem - 1];
	}

	if (nItem >= 60 && nItem <= 66)
	{
		switch (nItem)
		{
		case 60:
			itm = cBuffer.helm;
			break;

		case 61:
			itm = cBuffer.rring;
			break;

		case 62:
			itm = cBuffer.lring;
			break;

		case 63:
			itm = cBuffer.amulet;
			break;

		case 64:
			itm = cBuffer.rhand;
			break;

		case 65:
			itm = cBuffer.lhand;
			break;

		case 66:
			itm = cBuffer.armor;
			break;
		}
	}

	if (nItem >= 70 && nItem <= 77)
	{
		itm = cBuffer.belt[nItem - 70];
	}

	BOOL bHeart = FALSE;
	if (stricmp(itm.name, "Heart") == 0)
		bHeart = TRUE;
	
	fd = new CFileDialog(FALSE, "ITM", bHeart == FALSE ? itm.name : itm.earname, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, "Item Files (*.ITM)|*.ITM|All Files (*.*)|*.*||");
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
		MessageBox("Unable to write to file!", AfxGetAppName(), MB_OK|MB_ICONSTOP);
		return;
	}
	fwrite(&szITM, 32, 1, fp);
	fwrite(&itm, sizeof(itm), 1, fp);
	fclose(fp);
	MessageBox("Successfully exported item!", AfxGetAppName(), MB_OK|MB_ICONINFORMATION);
}

void CItemTrader::Refresh()
{
	char szItem[96];
	int nIndex;

	m_items.ResetContent();

	if (cBuffer.helm.name[0] && cBuffer.helm.top[8] != 0xFF)
		wsprintf(szItem, "Helm: %s", cBuffer.helm.name);
	else
		wsprintf(szItem, "Helm: <Empty>");
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 60);

	if (cBuffer.rring.name[0] && cBuffer.rring.top[8] != 0xFF)
		wsprintf(szItem, "Right Ring: %s", cBuffer.rring.name);
	else
		wsprintf(szItem, "Right Ring: <Empty>");
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 61);

	if (cBuffer.lring.name[0] && cBuffer.lring.top[8] != 0xFF)
		wsprintf(szItem, "Left Ring: %s", cBuffer.lring.name);
	else
		wsprintf(szItem, "Left Ring: <Empty>");
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 62);

	if (cBuffer.amulet.name[0] && cBuffer.amulet.top[8] != 0xFF)
		wsprintf(szItem, "Amulet: %s", cBuffer.amulet.name);
	else
		wsprintf(szItem, "Amulet: <Empty>");
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 63);

	if (cBuffer.rhand.name[0] && cBuffer.rhand.top[8] != 0xFF)
		wsprintf(szItem, "Right Hand: %s", cBuffer.rhand.name);
	else
		wsprintf(szItem, "Right Hand: <Empty>");
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 64);

	if (cBuffer.lhand.name[0] && cBuffer.lhand.top[8] != 0xFF)
		wsprintf(szItem, "Left Hand: %s", cBuffer.lhand.name);
	else
		wsprintf(szItem, "Left Hand: <Empty>");
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 65);

	if (cBuffer.armor.name[0] && cBuffer.armor.top[8] != 0xFF)
		wsprintf(szItem, "Armor: %s", cBuffer.armor.name);
	else
		wsprintf(szItem, "Armor: <Empty>");
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 66);

	BOOL bHeart = FALSE;
	for (int x = 0; x < 40; x++)
	{
		if (cBuffer.itemmap[x] >= 1 && cBuffer.itemmap[x] <= 40)
		{
			if (stricmp(cBuffer.inventory[cBuffer.itemmap[x] - 1].name, "Heart") == 0)
				bHeart = TRUE;
			wsprintf(szItem, "Inventory: %s", bHeart == FALSE ? cBuffer.inventory[cBuffer.itemmap[x] - 1].name : cBuffer.inventory[cBuffer.itemmap[x] - 1].earname);
			nIndex = m_items.AddString(szItem);
			m_items.SetItemData(nIndex, cBuffer.itemmap[x]);
		}
	}

	wsprintf(szItem, "Belt: %s", cBuffer.belt[0].name);
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 70);

	wsprintf(szItem, "Belt: %s", cBuffer.belt[1].name);
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 71);

	wsprintf(szItem, "Belt: %s", cBuffer.belt[2].name);
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 72);

	wsprintf(szItem, "Belt: %s", cBuffer.belt[3].name);
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 73);

	wsprintf(szItem, "Belt: %s", cBuffer.belt[4].name);
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 74);

	wsprintf(szItem, "Belt: %s", cBuffer.belt[5].name);
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 75);

	wsprintf(szItem, "Belt: %s", cBuffer.belt[6].name);
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 76);

	wsprintf(szItem, "Belt: %s", cBuffer.belt[7].name);
	nIndex = m_items.AddString(szItem);
	m_items.SetItemData(nIndex, 77);
}
