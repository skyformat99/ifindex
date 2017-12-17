// PlatformApi.h
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _H_PLATFORMAPI_H_
#define _H_PLATFORMAPI_H_

#include "ThreadApi.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined(__cplusplus)
extern "C" {
#endif//

PLATFORM_API int Platform_Init(const char* appname, const char* workdir, const char* datadir);
PLATFORM_API void Platform_Term();

PLATFORM_API int Platform_Join();

#if defined(__cplusplus)
}

class PLATFORM_API PlatformSpi 
	: public ThreadSpi
{
public:
};

class PLATFORM_API PlatformApi
{
public:
	static PlatformApi* GetInstance();
	static void ReleaseInstance();

public:
	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual void RegisterSpi(PlatformSpi *pSpi) = 0;

	///��ʼ��
	///@remark ��ʼ�����л���
	virtual int Init(const char* appname, const char* workdir, const char* datadir) = 0;

	//��ֹ
	///@remark ��ֹ���л������ͷ�������Դ
	virtual void Term() = 0;

	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	virtual int Join() = 0;

	///��¼
	///@return ��0��ʾ�ɹ���0��ʾʧ��
	virtual int Login(const char* user, const char* password, const char* xml = NULL) = 0;

	///��ȡ�߳�ID
	///@return �߳�ID
	virtual unsigned int GetThreadId() = 0;

	//virtual int Send(UINT Msg, WPARAM wParam, LPARAM lParam);
	//virtual int Post(UINT Msg, WPARAM wParam, LPARAM lParam);

	///֪ͨ�߳��˳�
	///@return ֪ͨ�Ƿ��ͳɹ�
	virtual int PostQuit() = 0;

	///�����߳�ʵ��
	///@return �߳�ʵ��
	virtual ThreadApi* CreateThread(const char* name, ThreadSpi *pSpi = NULL) = 0;

	///�����߳�ʵ��
	///@return ��
	virtual void DestroyThread(ThreadApi* pThread) = 0;

	///��ȡ�߳�ʵ��
	///@return �߳�ʵ��
	virtual ThreadApi* GetThread(unsigned int nThreadId) = 0;

protected:
	virtual ~PlatformApi();
};

#endif//

#endif//_H_PLATFORMAPI_H_
