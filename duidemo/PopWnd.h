#pragma once

//////////////////////////////////////////////////////////////////////////
///

class CPopWnd : public WindowImplBase
{
public:
	CPopWnd(void);
	~CPopWnd(void);

public:
	virtual void OnFinalMessage( HWND );
	virtual CStringUI GetSkinFile();
	virtual LPCTSTR GetWindowClassName( void ) const;
	virtual void Notify( struct TNOTIFY_UI &msg );
	virtual void InitWindow();

	UI_DECLARE_MESSAGE_MAP()
	virtual void OnClick(struct TNOTIFY_UI& msg);
	virtual void OnSelectChanged( struct TNOTIFY_UI &msg );
	virtual void OnItemSelect( struct TNOTIFY_UI &msg );

	virtual LRESULT OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& /*bHandled*/)
	{
		if (uMsg == WM_KEYDOWN)
		{
			switch (wParam)
			{
			case VK_RETURN:
			case VK_ESCAPE:
				return ResponseDefaultKeyEvent(wParam);
			default:
				break;
			}
		}
		return FALSE;
	}
private:
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMaxBtn;
	CButtonUI* m_pRestoreBtn;
	CButtonUI* m_pMinBtn;
	CButtonUI* m_pMenuBtn;
};
