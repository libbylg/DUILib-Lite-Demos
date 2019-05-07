#include "StdAfx.h"
#include <exdisp.h>
#include <comdef.h>
#include "ControlEx.h"
#include "resource.h"
#include <ShellAPI.h>
#include "SkinFrame.h"
#include "MainWnd.h"
#include "PopWnd.h"
#include "SplashWnd.h"

#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>

#include "Core/UIResource.h"
#include "Control/UIFactory.h"


void InitResource()
{
	// ��Դ����
#ifdef _DEBUG
	CManagerUI::SetResourceType(UIRES_FILE);
#else
	CManagerUI::SetResourceType(UILIB_ZIPRESOURCE);
#endif
	// ��Դ·��
	CStringUI strResourcePath = CManagerUI::GetInstancePath();
	// ������Դ
	switch(CManagerUI::GetResourceType())
	{
	case UIRES_FILE:
		{
			strResourcePath += _T("skin\\duidemo\\");
			CManagerUI::SetResourcePath(strResourcePath.GetData());
			// ������Դ������
			CResourceUI::GetInstance()->LoadResource(_T("res.xml"), NULL);
			break;
		}
	case UIRES_RESOURCE:
		{
			strResourcePath += _T("skin\\duidemo\\");
			CManagerUI::SetResourcePath(strResourcePath.GetData());
			// ������Դ������
			CResourceUI::GetInstance()->LoadResource(_T("IDR_RES"), _T("xml"));
			break;
		}
	case UIRES_ZIP:
		{
			strResourcePath += _T("skin\\");
			CManagerUI::SetResourcePath(strResourcePath.GetData());
			// ����
			CManagerUI::SetResourceZip(_T("duidemo_pwd.zip"), true, _T("duilib_ultimate"));
			//CManagerUI::SetResourceZip(_T("duidemo.zip"), true);
			// ������Դ������
			CResourceUI::GetInstance()->LoadResource(_T("res.xml"), NULL);
			break;
		}
	case UIRES_ZIPRESOURCE:
		{
			strResourcePath += _T("skin\\duidemo\\");
			CManagerUI::SetResourcePath(strResourcePath.GetData());
			HRSRC hResource = ::FindResource(CManagerUI::GetResourceDll(), _T("IDR_ZIPRES"), _T("ZIPRES"));
			if( hResource != NULL ) {
				DWORD dwSize = 0;
				HGLOBAL hGlobal = ::LoadResource(CManagerUI::GetResourceDll(), hResource);
				if( hGlobal != NULL ) {
					dwSize = ::SizeofResource(CManagerUI::GetResourceDll(), hResource);
					if( dwSize > 0 ) {
						CManagerUI::SetResourceZip((LPBYTE)::LockResource(hGlobal), dwSize);
						// ������Դ������
						CResourceUI::GetInstance()->LoadResource(_T("res.xml"), NULL);
					}
				}
				::FreeResource(hResource);
			}
		}
		break;
	}

	// ע��ؼ�
    UI_REGISTER_CONTROL(CCircleProgressUI);
    UI_REGISTER_CONTROL(CMyComboUI);
    UI_REGISTER_CONTROL(CChartViewUI);
    UI_REGISTER_CONTROL(CWndUI);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtDumpMemoryLeaks();
	// COM
	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) return 0;
	// OLE
	HRESULT hRes = ::OleInitialize(NULL);
	// ��ʼ��UI������
	CManagerUI::SetInstance(hInstance);
	// ��ʼ����Դ
	InitResource();


	CSplashWnd::MessageBox(NULL);

	// ����������
	CMainWnd* pMainWnd = new CMainWnd();
	if( pMainWnd == NULL ) return 0;
	pMainWnd->Create(NULL, _T("duilibʹ�����Ӽ�����By Troy��"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 800, 572);
	pMainWnd->CenterWindow();
	// ��Ϣѭ��
	CManagerUI::MessageLoop();
	// ���ٴ���
	delete pMainWnd;
	pMainWnd = NULL;
	// ������Դ
	CManagerUI::Term();
	// OLE
	OleUninitialize();
	// COM
	::CoUninitialize();

	return 0;
}