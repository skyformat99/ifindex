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
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(XPlatformSpi *pSpi) = 0;

	///初始化
	///@remark 初始化运行环境
	virtual int Init(const char* appname, const char* workdir, const char* datadir) = 0;

	//终止
	///@remark 终止运行环境，释放所有资源
	virtual void Term() = 0;

	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;

	///登录
	///@return 非0表示成功，0表示失败
	virtual int Login(const char* user, const char* password, const char* xml = NULL) = 0;

	///获取线程ID
	///@return 线程ID
	virtual unsigned int GetThreadId() = 0;

	//virtual int Send(UINT Msg, WPARAM wParam, LPARAM lParam);
	//virtual int Post(UINT Msg, WPARAM wParam, LPARAM lParam);

	///通知线程退出
	///@return 通知是否发送成功
	virtual int PostQuit() = 0;

	///创建线程实例
	///@return 线程实例
	virtual XThreadApi* CreateThread(const char* name, XThreadSpi *pSpi = NULL) = 0;

	///销毁线程实例
	///@return 无
	virtual void DestroyThread(XThreadApi* pThread) = 0;

	///获取线程实例
	///@return 线程实例
	virtual XThreadApi* GetThread(unsigned int nThreadId) = 0;

protected:
	virtual ~XPlatformApi();
};

#endif//

#endif//_H_XPLATFORMAPI_H_