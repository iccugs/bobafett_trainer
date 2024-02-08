// bobmin.h : main header file for the BoBaMiNi application
//

#if !defined(AFX_BOBMIN_H__A34DB0E5_0586_11D2_AC44_444553540000__INCLUDED_)
#define AFX_BOBMIN_H__A34DB0E5_0586_11D2_AC44_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define VERSION_IDENTIFICATION_108 0x46d826
#define REAL_CHAR_OFFSET_108 0x00688498
#define CHA_CHAR_OFFSET_108 0x0068855a
#define CHARACTER_SPACING_108 0x54D8
#define PERMANENT_NAME_108 0x688340

#define VERSION_IDENTIFICATION_107 0x46d4b6
#define REAL_CHAR_OFFSET_107 0x00687778
#define CHA_CHAR_OFFSET_107 0x0068783A
#define CHARACTER_SPACING_107 0x54D8
#define PERMANENT_NAME_107 0x687620

#define VERSION_IDENTIFICATION_105 0x48e9c6
#define REAL_CHAR_OFFSET_105 0x006A8838
#define CHA_CHAR_OFFSET_105 0x006A88FA
#define PERMANENT_NAME_105 0x6a86e0
#define CHARACTER_SPACING_105 0x54D8

#define VERSION_IDENTIFICATION_104 0x473636
#define REAL_CHAR_OFFSET_PTR_104 0x4A3188
#define PERMANENT_NAME_104 0x6171c8
#define CHARACTER_SPACING_104 0x54D8

/////////////////////////////////////////////////////////////////////////////
// CBOBMINApp:
// See bobmin.cpp for the implementation of this class
//

class CBOBMINApp : public CWinApp
{
public:
	CBOBMINApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBOBMINApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBOBMINApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

typedef struct diabloITEM
{
	//unsigned char top[125];
	unsigned char top[61];
	char earname[64];
	char name[64];
	unsigned char bottom[179];
} ITEM;

typedef struct diabloCHARACTER
{
	unsigned char character[698];

	ITEM helm;
	ITEM rring;
	ITEM lring;
	ITEM amulet;
	ITEM rhand;
	ITEM lhand;
	ITEM armor;

	ITEM inventory[40];
	unsigned char itemcount[4];
	unsigned char itemmap[40];

	ITEM belt[8];
} CHARACTER;

extern const char szHeader[];
extern const char szITM[];
extern CHARACTER cMain;
extern char szName1[32];
extern char szName2[32];
extern char szName3[32];
extern char szName4[32];
extern int nResult;
extern BOOL bCanceled;

extern DWORD dwRealCharOffset;
// the following is only used for these programs:
// Diablo 1.04, 1.03, 1.02 and Hellfire
extern DWORD dwRealCharOffsetPtr;

extern DWORD dwChaCharOffset;
extern DWORD dwCharacterSpacing;
extern DWORD dwPermanentNameOffset;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOBMIN_H__A34DB0E5_0586_11D2_AC44_444553540000__INCLUDED_)
