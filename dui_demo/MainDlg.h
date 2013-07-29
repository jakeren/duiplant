// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "UIHander.h"
#include "wtlhelper/whwindow.h"

class CMainDlg : public CDuiHostWnd
// 	,public CWHRoundRectFrameHelper<CMainDlg>	//��ҪԲ�Ǵ���ʱ����
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose()
	{
		EndDialog(IDCANCEL);
	}
	void OnMaximize()
	{
		SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE);
	}
	void OnRestore()
	{
		SendMessage(WM_SYSCOMMAND,SC_RESTORE);
	}
	void OnMinimize()
	{
		SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
	}

	void OnSize(UINT nType, CSize size)
	{
		SetMsgHandled(FALSE);
		if(!m_bLayoutInited) return;
		if(nType==SIZE_MAXIMIZED)
		{
			FindChildByCmdID(3)->SetVisible(TRUE);
			FindChildByCmdID(2)->SetVisible(FALSE);
		}else if(nType==SIZE_RESTORED)
		{
			FindChildByCmdID(3)->SetVisible(FALSE);
			FindChildByCmdID(2)->SetVisible(TRUE);
		}
	}

	BOOL OnInitDialog(HWND hWnd,LPARAM lp)
	{
		m_bLayoutInited=TRUE;
		SetMsgHandled(FALSE);
		return FALSE;
	}

	int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:

	DUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		DUI_NOTIFY_ID_COMMAND(1, OnClose)
		DUI_NOTIFY_ID_COMMAND(2, OnMaximize)
		DUI_NOTIFY_ID_COMMAND(3, OnRestore)
		DUI_NOTIFY_ID_COMMAND(5, OnMinimize)
	DUI_NOTIFY_MAP_END()	

	BEGIN_MSG_MAP_EX(CMainDlg)
// 		CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CMainDlg>) //��ҪԲ�Ǵ���ʱ����
		MSG_WM_CREATE(OnCreate)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_DUI_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP(CDuiHostWnd)
		CHAIN_MSG_MAP_MEMBER((*m_pUiHandler))
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

private:
	BOOL			m_bLayoutInited;
	CUIHander *    m_pUiHandler; 
};