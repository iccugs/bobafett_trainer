; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBOBMINDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"

ClassCount=6
Class1=CBOBMINApp
Class2=CBOBMINDlg
Class3=CAboutDlg

ResourceCount=14
Resource1=IDD_BOBMIN_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CCharSel
Resource4=IDD_CHARSEL
Class5=CItemTrader
Class6=CCharEditor
Resource8=IDD_ITEM
Resource9=IDD_CHARSEL (English (U.S.))
Resource10=IDD_CHARACTER (English (U.S.))
Resource11=IDD_BOBMIN_DIALOG (English (U.S.))
Resource12=IDD_ABOUTBOX (English (U.S.))
Resource13=IDD_ITEM (English (U.S.))
Resource14=IDD_CHARACTER

[CLS:CBOBMINApp]
Type=0
HeaderFile=bobmin.h
ImplementationFile=bobmin.cpp
BaseClass=CWinApp
LastObject=CBOBMINApp
Filter=N

[CLS:CBOBMINDlg]
Type=0
HeaderFile=bobmindlg.h
ImplementationFile=bobmindlg.cpp
BaseClass=CDialog
LastObject=CBOBMINDlg
Filter=D
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=bobmindlg.h
ImplementationFile=bobmindlg.cpp
BaseClass=CDialog
LastObject=CAboutDlg
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_INFO,edit,1352730628

[DLG:IDD_BOBMIN_DIALOG]
Type=1
Class=CBOBMINDlg
ControlCount=18
Control1=IDC_SAVE,button,1342242817
Control2=IDC_RESTORE,button,1342242816
Control3=IDC_ITEMS,button,1342242816
Control4=IDC_CHARACTER,button,1342242816
Control5=IDC_ADDON1,button,1342242816
Control6=IDC_ADDON2,button,1342242816
Control7=IDC_ADDON3,button,1342242816
Control8=IDC_ADDON4,button,1342242816
Control9=IDC_ADDON5,button,1342242816
Control10=IDC_STATIC,static,1342308353
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,button,1342178055
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,button,1342177287

[DLG:IDD_CHARSEL]
Type=1
Class=CCharSel
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHAR1,button,1476395017
Control4=IDC_CHAR2,button,1476395017
Control5=IDC_CHAR3,button,1476395017
Control6=IDC_CHAR4,button,1476395017
Control7=IDC_STATIC,button,1342177287

[CLS:CCharSel]
Type=0
HeaderFile=CharSel.h
ImplementationFile=CharSel.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCharSel

[DLG:IDD_ITEM]
Type=1
Class=CItemTrader
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_IMPORT,button,1342242816
Control4=IDC_EXPORT,button,1342242816
Control5=IDC_ITEMS,listbox,1352728833

[CLS:CItemTrader]
Type=0
HeaderFile=ItemTrader.h
ImplementationFile=ItemTrader.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CItemTrader

[DLG:IDD_CHARACTER]
Type=1
Class=CCharEditor
ControlCount=32
Control1=IDC_NAME,edit,1350631552
Control2=IDC_LEVELUP,edit,1350639744
Control3=IDC_CLASS,combobox,1344339971
Control4=IDC_EXP,edit,1350639744
Control5=IDC_LEVEL,edit,1350639744
Control6=IDC_STR,edit,1350639744
Control7=IDC_DEX,edit,1350639744
Control8=IDC_LIFE,edit,1350639744
Control9=IDC_MAG,edit,1350639744
Control10=IDC_VIT,edit,1350639744
Control11=IDC_MANA,edit,1350639744
Control12=IDC_STRCUR,edit,1350641792
Control13=IDC_DEXCUR,edit,1350641792
Control14=IDC_LIFECUR,edit,1350641792
Control15=IDC_MAGCUR,edit,1350641792
Control16=IDC_VITCUR,edit,1350641792
Control17=IDC_MANACUR,edit,1350641792
Control18=IDC_SAVE,button,1342242817
Control19=IDC_CANCEL,button,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342177296
Control32=IDC_PERMNAME,button,1342242851

[CLS:CCharEditor]
Type=0
HeaderFile=CharEditor.h
ImplementationFile=CharEditor.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCharEditor

[DLG:IDD_CHARACTER (English (U.S.))]
Type=1
Class=CCharEditor
ControlCount=32
Control1=IDC_NAME,edit,1350631552
Control2=IDC_LEVELUP,edit,1350639744
Control3=IDC_CLASS,combobox,1344339971
Control4=IDC_EXP,edit,1350639744
Control5=IDC_LEVEL,edit,1350639744
Control6=IDC_STR,edit,1350639744
Control7=IDC_DEX,edit,1350639744
Control8=IDC_LIFE,edit,1350639744
Control9=IDC_MAG,edit,1350639744
Control10=IDC_VIT,edit,1350639744
Control11=IDC_MANA,edit,1350639744
Control12=IDC_STRCUR,edit,1350641792
Control13=IDC_DEXCUR,edit,1350641792
Control14=IDC_LIFECUR,edit,1350641792
Control15=IDC_MAGCUR,edit,1350641792
Control16=IDC_VITCUR,edit,1350641792
Control17=IDC_MANACUR,edit,1350641792
Control18=IDC_SAVE,button,1342242817
Control19=IDC_CANCEL,button,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342177296
Control32=IDC_PERMNAME,button,1342242851

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_INFO,edit,1352730628

[DLG:IDD_BOBMIN_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=19
Control1=IDC_SAVE,button,1342242817
Control2=IDC_RESTORE,button,1342242816
Control3=IDC_ITEMS,button,1342242816
Control4=IDC_CHARACTER,button,1342242816
Control5=IDC_ADDON1,button,1342242816
Control6=IDC_ADDON2,button,1342242816
Control7=IDC_ADDON3,button,1342242816
Control8=IDC_ADDON4,button,1342242816
Control9=IDC_ADDON5,button,1342242816
Control10=IDC_STATIC,static,1342308353
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,button,1342178055
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC

[DLG:IDD_CHARSEL (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHAR1,button,1476395017
Control4=IDC_CHAR2,button,1476395017
Control5=IDC_CHAR3,button,1476395017
Control6=IDC_CHAR4,button,1476395017
Control7=IDC_STATIC,button,1342177287

[DLG:IDD_ITEM (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_IMPORT,button,1342242816
Control4=IDC_EXPORT,button,1342242816
Control5=IDC_ITEMS,listbox,1352728833

