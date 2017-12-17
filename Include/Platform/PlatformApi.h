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
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(PlatformSpi *pSpi) = 0;

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
	virtual ThreadApi* CreateThread(const char* name, ThreadSpi *pSpi = NULL) = 0;

	///销毁线程实例
	///@return 无
	virtual void DestroyThread(ThreadApi* pThread) = 0;

	///获取线程实例
	///@return 线程实例
	virtual ThreadApi* GetThread(unsigned int nThreadId) = 0;

protected:
	virtual ~PlatformApi();
};

#endif//

#endif//_H_PLATFORMAPI_H_
