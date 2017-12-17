#ifndef _H_XINDICATORAPI_H_
#define _H_XINDICATORAPI_H_

//////////////////////////////////////////////////////////////////////////

#include "XIndicator.h"

class XINDICATOR_API XIndicatorSpi
{
public:
	//Global
	virtual void OnLog(INDICATOR_LOG_LEVEL level, const char* str) {}

	virtual void OnInit() {}
	virtual void OnTerm() {}
	
	//Calc
	virtual void OnTest(iHandle handle) {}
	virtual void OnCalc(iHandle handle) {}
};

class XINDICATOR_API XIndicatorQuoteProvider
{
public:
	//Symbol
	virtual int OnSymbolsFind(const char* key, unsigned int flags) { return 0; }
	virtual int OnSymbolsTotal(const char* market) { return 0; }
	virtual const char* OnSymbolSelect(int index, char* str, int len) { return str; }

	//Calc Data
	virtual voidptr OnRefCalcData(const char* symbol, int period, unsigned int flags = REF_CALCDATA_DEFAULT) { return 0; }
	virtual const char* OnGetSymbol(voidptr dataptr, char* str, int len) { return str; }
	virtual int OnGetPeriod(voidptr dataptr) { return 0; }
	virtual int OnGetPriceCount(voidptr dataptr) { return 0; }
	virtual unsigned int OnGetPriceDate(voidptr dataptr, int offset) { return 0; }
	virtual unsigned int OnGetPriceTime(voidptr dataptr, int offset) { return 0; }
	virtual double OnGetPriceValue(voidptr dataptr, int price, int offset) { return 0.; }
	virtual double OnGetFinanceValue(voidptr dataptr, int finance, int offset) { return 0.; }
	virtual double OnGetFieldValue(voidptr dataptr, INDICATOR_FIELD field) { return 0.; }
};

class XINDICATOR_API XIndicatorTradeProvider
{
public:
	//User
	virtual int OnUsersTotal() { return 0; }
	virtual void OnUserSelectReset() {}
	virtual int OnUserSelectByIndex(int index) { return -1; }
	virtual int OnUserSelectByName(const char* name) { return -1; }
	virtual int OnUserSelectByObject(const char* symbol) { return -1; }
	virtual double OnUserFieldValue(const char* field) { return 0.; }
	virtual const char* OnUserFieldString(const char* field, char* str, int len) { return str; }

	//Trade
	virtual void OnOrderSend(iHandle handle, const char* symbol, int cmd, double volume, double price
		, int slippage, double stoploss, double takeprofit
		, char* comment, int magic) {}
	virtual int OnOrdersSelect(int pool) { return -1; }
	virtual int OnOrdersTotal() { return 0; }
	virtual void OnOrderSelectReset() {}
	virtual int OnOrderSelectByIndex(int index) { return -1; }
	virtual int OnOrderSelectByTicket(const char* ticket) { return -1; }
	virtual int OnOrderSelectByMagic(int magic) { return -1; }

	virtual void OnOrderClose(double lots, double price, int slippage) {}
	virtual void OnOrderCloseBy(int opposite) {}
	virtual void OnOrderDelete() {}
	virtual void OrderModify(double price,double stoploss,double takeprofit,unsigned long expiration) {}

	virtual double OnGetOrderFieldValue(const char* field) { return 0.; }
	virtual const char* OnGetOrderFieldString(const char* field, char* str, int len) { return str; }

	virtual int OnGetOrderType() { return OP_NONE; }
	virtual const char* OnGetOrderTicket(char* str, int len) { return str; }

	virtual const char* OnGetOrderSymbol(char* str, int len) { return str; }

	virtual double OnGetOrderOpenPrice() { return EMPTY_VALUE; }
	virtual double OnGetOrderClosePrice() { return EMPTY_VALUE; }

	virtual unsigned int OnGetOrderOpenTime(unsigned long* date) { return 0; }
	virtual unsigned int OnGetOrderCloseTime(unsigned long* date) { return 0; }
	virtual unsigned int OnGetOrderExpiration(unsigned long* date) { return 0; }

	virtual double OnGetOrderLots() { return 0.; }
	virtual double OnGetOrderProfit() { return 0.; }
	virtual double OnGetOrderTakeProfit() { return 0.; }
	virtual double OnGetOrderStopLoss() { return 0.; }
	virtual double OnGetOrderCommission() { return 0.; }
	virtual int OnGetOrderMagicNumber() { return 0; }
	virtual const char* OnGetOrderComment(char* str, int len) { return str; }
};

class XINDICATOR_API XIndicatorApi
{
public:
	static XIndicatorApi* GetInstance();
	static XIndicatorApi* GetInstanceA(const char* workdir, const char* datadir);
	static XIndicatorApi* GetInstanceW(const wchar_t* workdir, const wchar_t* datadir);
	static void ReleaseInstance();

public:
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	//virtual void Init() = 0;
	//virtual void Term() = 0;

	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(XIndicatorSpi *pSpi) = 0;
	virtual void RegisterQuoteProvider(XIndicatorQuoteProvider *pProvider) = 0;
	virtual void RegisterTradeProvider(XIndicatorTradeProvider *pProvider) = 0;

	virtual void OnIdle(unsigned int tick) = 0;

	virtual void UpdateHisData(const char* symbol) = 0;

	virtual void UpdateFinanceData(const char* symbol) = 0;

	virtual void UpdateFieldData(const char* symbol) = 0;

	virtual void UpdateOrderData() = 0;

protected:
	virtual ~XIndicatorApi() {};
};

#endif//_H_XINDICATORAPI_H_
