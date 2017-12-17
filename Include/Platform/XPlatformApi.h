// XPlatformApi.h
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _H_XPLATFORMAPI_H_
#define _H_XPLATFORMAPI_H_

#include "XThreadApi.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined(__cplusplus)
extern "C" {
#endif//

XPLATFORM_API int XPlatform_Init(const char* appname, const char* workdir, const char* datadir);
XPLATFORM_API void XPlatform_Term();

XPLATFORM_API int XPlatform_Join();

#if defined(__cplusplus)
}

class XPLATFORM_API XPlatformSpi 
	: public XThreadSpi
{
public:
	
};

class XPLATFORM_API XPlatformApi
{
public:
	static XPlatformApi* GetInstance();
	static void ReleaseInstance();

public:
	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual void RegisterSpi(XPlatformSpi *pSpi) = 0;

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
	virtual XThreadApi* CreateThread(const char* name, XThreadSpi *pSpi = NULL) = 0;

	///�����߳�ʵ��
	///@return ��
	virtual void DestroyThread(XThreadApi* pThread) = 0;

	///��ȡ�߳�ʵ��
	///@return �߳�ʵ��
	virtual XThreadApi* GetThread(unsigned int nThreadId) = 0;

protected:
	virtual ~XPlatformApi();
};

#endif//

#endif//_H_XPLATFORMAPI_H_