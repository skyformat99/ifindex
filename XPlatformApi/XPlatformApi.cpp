// XPlatformApi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Indicator/XIndicator.h>
#include <Indicator/XIndicatorApi.h>
#include <Platform/XPlatformApi.h>

wchar_t szAppName[MAX_PATH] = { 0 };
wchar_t szAppPath[MAX_PATH] = { 0 };
wchar_t szAppData[MAX_PATH] = { 0 };

class CPlatformSpi : public XPlatformSpi
{
public:
	//������ƽ̨Join��ʱ��ƽ̨�����OnRun��OnRunĬ�Ͻ�����Ϣѭ��������֤ȯ�����������ϵͳ�ͽ��빤��״̬��
	virtual int OnRun()
	{
		printf("CPlatformSpi::OnRun\n");
		//XPlatformApi::GetInstance()->CreateThread("MyMACD");
		return __super::OnRun();
	}
	//��Ҳ���Դ������̻߳������������Ĳ��ԣ��������Ĳ��Ի��ڻ�������֤ȯ�����������ϵͳ�����У��������Ա�֤�������е�ʵʱ��
	virtual int OnRunThread()
	{
		printf("CPlatformSpi::OnRunThread\n");
		return __super::OnRunThread();
	}
};
CPlatformSpi g_Platform;

DWORD WINAPI PlatformThreadFunc(LPVOID lpParam) 
{
	char szAppNameA[_MAX_FNAME] = { 0 };
	char szAppPathA[_MAX_PATH] = { 0 };
	char szAppDataA[_MAX_PATH] = { 0 };
	wcstombs(szAppNameA, szAppName, _MAX_FNAME);
	wcstombs(szAppPathA, szAppPath, _MAX_PATH);
	wcstombs(szAppDataA, szAppData, _MAX_PATH);

	XPlatformApi* pApi = XPlatformApi::GetInstance();
	if(pApi) {
		pApi->RegisterSpi(&g_Platform);
		pApi->Init(szAppNameA,szAppPathA,szAppDataA);
		pApi->Join();
		pApi->Term();
	}
	XPlatformApi::ReleaseInstance();

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HMODULE hModule = GetModuleHandleW(NULL);
	wchar_t szPath[_MAX_PATH] = { 0 };
	::GetModuleFileNameW(hModule, szPath, _MAX_PATH);

	wchar_t szAppDrive[_MAX_DRIVE] = { 0 };
	wchar_t szAppDir[_MAX_DIR] = { 0 };
	wchar_t szAppExt[_MAX_EXT] = { 0 };
	_wsplitpath(szPath, szAppDrive, szAppDir, szAppName, szAppExt);

	//wchar_t szAppPath[_MAX_PATH] = { 0 };
	_snwprintf(szAppPath, _MAX_PATH, _T("%s%s"), szAppDrive, szAppDir);
	::PathRemoveBackslashW(szAppPath);

	//wchar_t szAppData[MAX_PATH] = { 0 };
	::SHGetSpecialFolderPathW(NULL, szPath, CSIDL_APPDATA, TRUE);
	_sntprintf(szAppData, _MAX_PATH, _T("%s\\%s"), szPath, szAppName);
	::SHCreateDirectoryExW(NULL, szAppData, NULL);

	HANDLE hThread = ::CreateThread(NULL, 0, PlatformThreadFunc, NULL, 0, NULL);

	while(getchar()!='q') { 
		;
	}

	XPlatformApi::GetInstance()->PostQuit();
	DWORD dwRet = ::WaitForSingleObject(hThread, INFINITE);
	if (dwRet == WAIT_TIMEOUT || dwRet == WAIT_FAILED) {
		::TerminateThread(hThread, -1);
	}
	::CloseHandle(hThread);
	hThread = NULL;

	return 0;
}

