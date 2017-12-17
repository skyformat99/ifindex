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
	: public XIndicatorSpi //ָ��ϵͳ
{
public:
	virtual int OnRun();
	virtual int OnRunThread();
};

class XPLATFORM_API XThreadApi 
{
public:
	///��ȡ��ǰ�߳�Apiʵ��
	///@param 
	static XThreadApi* GetInstance();
	///�ͷ�
	///@remark �ͷŵ�ǰ�߳�ʵ��
	static void ReleaseInstance();

public:
	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	//virtual void RegisterSpi(XThreadSpi *pSpi) = 0;

	///��ʼ��
	///@remark ��ʼ�����л���
	//virtual int Init(const char* name, const char* workdir, const char* datadir) = 0;

	//��ֹ
	///@remark ��ֹ���л������ͷ�������Դ
	//virtual void Term() = 0;

	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	virtual int Join() = 0;

	///��ȡ�߳�ID
	///@return �߳�ID
	virtual unsigned int GetThreadId() = 0;

	//virtual int Send(UINT Msg, WPARAM wParam, LPARAM lParam);
	//virtual int Post(UINT Msg, WPARAM wParam, LPARAM lParam);

	///֪ͨ�߳��˳�
	///@return ֪ͨ�Ƿ��ͳɹ�
	virtual int PostQuit() = 0;

protected:
	virtual ~XThreadApi();
};

#endif//

#endif//_H_XTHREADAPI_H_