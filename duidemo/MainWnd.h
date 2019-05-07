#pragma once
#include "PopWnd.h"
#include "ShlObj.h"
#include "MsgWnd.h"
#include "ControlEx.h"
#include "SkinManager.h"

#include "Core/UIControl.h"
#include "Core/UIManager.h"
#include "Core/UIWindow.h"

/////////////////////////

/////////////////////////////////////////////////
///

using namespace DUI;


class CMainPage : public CNotifyPumpUI
{
public:
	CMainPage();

public:
	void SetPaintMagager(CManagerUI* pPaintMgr);

	UI_DECLARE_MESSAGE_MAP()
	virtual void OnClick(TNOTIFY_UI& msg);
	virtual void OnSelectChanged( TNOTIFY_UI &msg );
	virtual void OnItemClick(TNOTIFY_UI&msg );

private:
	CManagerUI* m_pPaintManager;
};

//////////////////////////////////////////////////////////////////////////
///

class CMainWnd : public CWindowUI, public CWebBrowserEventHandler, public SkinChangedReceiver
{
public:
	CMainWnd();
	~CMainWnd();

public:// UI初始化
	DUI::CStringUI GetSkinFile();
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	void InitWindow();
	void OnFinalMessage(HWND hWnd);

public:// 接口回调
	CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual BOOL Receive(SkinChangedParam param);
	LPCTSTR QueryControlText(LPCTSTR lpstrId, LPCTSTR lpstrType);

public:// UI通知消息
	void Notify(TNOTIFY_UI& msg);
	void OnLClick(CControlUI *pControl);

	UI_DECLARE_MESSAGE_MAP()
	

public:// 系统消息
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:// WebBrowser
	virtual HRESULT STDMETHODCALLTYPE UpdateUI(void);
	virtual HRESULT STDMETHODCALLTYPE GetHostInfo(CWebBrowserUI* pWeb, DOCHOSTUIINFO __RPC_FAR *pInfo);
	virtual HRESULT STDMETHODCALLTYPE ShowContextMenu(CWebBrowserUI* pWeb, DWORD dwID, POINT __RPC_FAR *ppt, IUnknown __RPC_FAR *pcmdtReserved, IDispatch __RPC_FAR *pdispReserved);

private:// UI变量
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMaxBtn;
	CButtonUI* m_pRestoreBtn;
	CButtonUI* m_pMinBtn;
	CButtonUI* m_pSkinBtn;
	CMenuWnd* m_pMenu;
	CStdStringPtrMap m_MenuInfos;
	CTrayIcon m_trayIcon;

public:
	CMainPage m_MainPage;
};
