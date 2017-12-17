// XThreadApi.h
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _H_XTHREADAPI_H_
#define _H_XTHREADAPI_H_

#include "XPlatformApiDef.h"
#include <Indicator/XIndicatorApi.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined(__cplusplus)
extern "C" {
#endif//

	//

#if defined(__cplusplus)
}

class XPLATFORM_API XThreadSpi 
	: public XIndicatorSpi //指标系统
{
public:
	virtual int OnRun();
	virtual int OnRunThread();
};

class XPLATFORM_API XThreadApi 
{
public:
	///获取当前线程Api实例
	///@param 
	static XThreadApi* GetInstance();
	///释放
	///@remark 释放当前线程实例
	static void ReleaseInstance();

public:
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	//virtual void RegisterSpi(XThreadSpi *pSpi) = 0;

	///初始化
	///@remark 初始化运行环境
	//virtual int Init(const char* name, const char* workdir, const char* datadir) = 0;

	//终止
	///@remark 终止运行环境，释放所有资源
	//virtual void Term() = 0;

	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;

	///获取线程ID
	///@return 线程ID
	virtual unsigned int GetThreadId() = 0;

	//virtual int Send(UINT Msg, WPARAM wParam, LPARAM lParam);
	//virtual int Post(UINT Msg, WPARAM wParam, LPARAM lParam);

	///通知线程退出
	///@return 通知是否发送成功
	virtual int PostQuit() = 0;

protected:
	virtual ~XThreadApi();
};

#endif//

#endif//_H_XTHREADAPI_H_