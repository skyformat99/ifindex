#ifndef _H_INDICATORDEF_H_
#define _H_INDICATORDEF_H_

#pragma pack(1) 

typedef void* iHandle;
typedef void* voidptr;
#define INVALID_INDICATOR_HANDLE NULL

#define CHARTS_MAX				100

#ifndef CLR_NONE
#define CLR_NONE                0xFFFFFFFFL
#endif//CLR_NONE

#define EMPTY_VALUE				(1e16)
//#define INVALID_HANDLE		-1
#define WHOLE_ARRAY				-1
#define WRONG_VALUE				-1

#define MAX_DECIMAL_NUM			7

#define MAX_INPUT_VALUE			32

enum INDICATOR_LOG_LEVEL
{
	LOGLEVEL_DEBUG	= 0,
	LOGLEVEL_INFO,
	LOGLEVEL_WARN,
	LOGLEVEL_ERROR,
};

enum INDICATOR_COORD_TYPE
{
	CT_NORMAL	=	0,			//普通等分坐标
	CT_LOG		=	0x01,		//对数坐标
	CT_MASK1	=	0X0F,
	CT_DIFF		=	0x10,		//等差坐标(三等分坐标)
	CT_SCALE	=	0x20,		//等比坐标
	CT_PERCENT	=	0x40,		//百分比坐标
	CT_GOLDEN	=	0x80,		//黄金分割
	CT_MASK2	=	0XF0,
};

//技术指标的计算要求价格价值和成交量价值，该计算将执行，有7个预先的标识符在INDICATOR_APPLIED_PRICE 项目中，以指定计算的期望价值基础。
enum INDICATOR_APPLIED_PRICE
{
	PRICE_CLOSE,		//收盘价格
	PRICE_OPEN,			//开盘价格
	PRICE_HIGH,			//最高价格
	PRICE_LOW,			//最低价格
	PRICE_MEDIAN,		//中间值（高+低）/2
	PRICE_TYPICAL,		//典型价格（高+低+收盘价）/3
	PRICE_WEIGHTED,		//平均价格（高+低+收盘价格+开盘价格）/4
	PRICE_AMOUNT,		//成交额
	PRICE_VOLUME,		//成交量
	PRICE_TICKVOLUME,	//跳动量
	PRICE_AVPRICE,		//平均价（成交额/成交量）
};

//Period
#define INDICATOR_PERIOD_TICK		0
//#define INDICATOR_PERIOD_1SEC		1
#define INDICATOR_PERIOD_5SEC		5
#define INDICATOR_PERIOD_1MIN		60
#define INDICATOR_PERIOD_5MIN		60*5
#define INDICATOR_PERIOD_15MIN		60*15
#define INDICATOR_PERIOD_30MIN		60*30
#define INDICATOR_PERIOD_60MIN		60*60
#define INDICATOR_PERIOD_DAY		60*60*24
#define INDICATOR_PERIOD_WEEK		60*60*24*7
#define INDICATOR_PERIOD_MONTH		60*60*24*30
#define INDICATOR_PERIOD_SEASON		60*60*24*90
#define INDICATOR_PERIOD_YEAR		60*60*24*365

//最大值最小值定义
enum INDICATOR_MMX_TYPE
{
	MMX_MIN = 0,
	MMX_MAX,

	MMX_MINDISPVALUE,
	MMX_MAXDISPVALUE,

	MMX_INDEX_COUNT,

	MMX_MINOPEN = MMX_INDEX_COUNT,
	MMX_MAXOPEN,
	MMX_MINHIGH,
	MMX_MAXHIGH,
	MMX_MINLOW,
	MMX_MAXLOW,
	MMX_MINCLOSE,
	MMX_MAXCLOSE,
	MMX_MINVOLUME,
	MMX_MAXVOLUME,
	MMX_MINAMOUNT,
	MMX_MAXAMOUNT,

	MMX_MINDISPPRICE,
	MMX_MAXDISPPRICE,
	MMX_MINDISPVOLUME,
	MMX_MAXDISPVOLUME,
	MMX_MINDISPAMOUNT,
	MMX_MAXDISPAMOUNT,

	MMX_COUNT,
};

enum INDICATOR_STO_PRICE
{
	STO_LOWHIGH,	//基于最低价/最高价的计算
	STO_OPENCLOSE,	//基于开盘价/收盘价的计算
};

enum INDICATOR_MA_METHOD
{
	MODE_SMA,	//简单移动平均线 (SMA)：Simple Moving Average
	MODE_EMA,	//指数移动平均线 (EMA)：Exponential MA
	MODE_SMMA,	//通畅移动平均线 (SMMA)：Smoothed MA
	MODE_LWMA,	//线性权数移动平均线 (LWMA)：Linear Weighted MA
	MODE_DMA,	//动态移动平均线 Dynamic Moving Average
	//MDOE_TMA, //递归移动平均
	//MODE_WMA, //加权移动平均
};

enum INDICATOR_TRADE_TYPE
{
	TT_BUY=0,
	TT_BUYSHORT=1,
	TT_SELL=2,
	TT_SELLSHORT=3,
	TT_LOSS=4,		//止损
	TT_WIN=5,		//止赢
	TT_DROP=6,		//回落
	TT_STATIC=7,	//横盘
};

enum INDICATOR_PRICE_TYPE
{
	PT_CLOSE=0,
	PT_MARKET=1,
	PT_LIMIT=2,
	PT_STOP=3,
};

enum INDICATOR_KLINE_TYPE
{
	KLINE_K = 0,	//K线
	KLINE_BAR,		//美国线
	KLINE_TREND,	//走势线
	KLINE_MAX,
};

enum INDICATOR_STICK_TYPE
{
	STICK_LINE = 0,	//柱状线
	STICK_BAR,		//柱状图
	STICK_MAX,
};

enum INDICATOR_HISTOGRAM_TYPE
{
	HISTOGRAM_LINE = 0,	//柱状线
	HISTOGRAM_BAR,		//美国线
	HISTOGRAM_K,		//K线
	HISTOGRAM_MAX,
};

enum INDICATOR_TYPE
{
	INDICATOR_TYPE_MAIN			= 0,			//主图指标
	INDICATOR_TYPE_SECOND,						//幅图指标
	INDICATOR_TYPE_POOL,						//策略/池指标
};

enum INDICATOR_STYLE
{
	INDICATOR_STYLE_TRADER		= 0X01,			//交易指标
	INDICATOR_STYLE_CONTAINER	= 0X02,			//容器指标
	INDICATOR_STYLE_DRAWLINE	= 0X04,			//划线指标
};

//根据以上类型和风格，可以有个股分析指标，个股分析交易指标，策略分析指标，策略分析交易指标等
//这些指标必须在INDICATOR_STYLE_CONTAINER风格的指标容器下运行，通常就是在显示指标/策略下运行
//个股分析交易指标可以划线交易
//对于脚本的话，可以有个股脚本和策略脚本，脚本可以交易
//脚本必须在INDICATOR_STYLE_CONTAINER风格的指标容器下运行，通常就是在显示指标/策略下运行

#define MAX_INDICATOR_REFLINE	16
#define MAX_INDICATOR_INDEX		16
#define MAX_INDICATOR_NAME		32
#define MAX_INDICATOR_STRING	64

enum INDICATOR_INDEX_TYPE
{
	INDEX_LINE = 0,		//指标线
	INDEX_CALC,			//辅助计算
};

enum INDICATOR_DRAW_TYPE
{
	DRAW_LINE,				//画线
	DRAW_SECTION,			//线条
	DRAW_STICK,				//基于基线画柱状线
	DRAW_HISTOGRAM,			//基于基线画柱状图
	DRAW_HISTOGRAM2,		//两个指标命令的柱状图
	DRAW_HISTOGRAM3,		//三个指标命令的柱状图
	DRAW_HISTOGRAM4,		//四个指标命令的柱状图
	DRAW_CANDLES,			//以蜡烛台序列展示
	DRAW_ARROW,				//画箭头
	DRAW_FILLING,			//两层间的颜色
	DRAW_ZIGZAG,			//之字设计允许垂直界面
	DRAW_BARS,				//以字符序列展示

	DRAW_COLOR_LINE,		//多色线
	DRAW_COLOR_SECTION,		//多色分段
	DRAW_COLOR_HISTOGRAM,	//基于基线的多色直方图
	DRAW_COLOR_HISTOGRAM2,	//两个指标缓冲区的多色直方图
	DRAW_COLOR_CANDLES,		//多色蜡烛台
	DRAW_COLOR_ARROW,		//描绘多色箭头
	DRAW_COLOR_ZIGZAG,		//多色之字形
	DRAW_COLOR_BARS,		//多色字节
};

enum INDICATOR_LINE_TYPE
{
	LINE_SOLID,		//实线
	LINE_DASH,		//折线
	LINE_DOT,			//虚线
	LINE_DASHDOT,		//折点线
	LINE_DASHDOTDOT,	//双折点线
};

enum INDICATOR_CUSTOMIND_PROPERTY_STRING
{
	INDICATOR_SHORTNAME,
	INDICATOR_LEVELTEXT,
};

enum INDICATOR_REFVALUE_TYPE
{
	REFVALUE_NONE	= 0,
	REFVALUE_BOOL,
	REFVALUE_INTEGER,
	REFVALUE_DATE,
	REFVALUE_TIME,
	REFVALUE_FLOAT,
	REFVALUE_STRINGA,
	REFVALUE_STRINGW,
#ifndef UNICODE
	REFVALUE_STRING = REFVALUE_STRINGA,
#else
	REFVALUE_STRING = REFVALUE_STRINGW,
#endif//
	REFVALUE_POINT,
};

typedef struct tagRefValue
{
	int type:4;
	int size:14;
	int maxsize:14;
	void* ptr;							//refvalue ptr
}REFVALUE,*PREFVALUE;

//#define SYMBOL_SHSE "SH" //上海市场
//#define SYMBOL_SZSE "SZ" //深圳市场

//typedef const char* SYMBOL; //code.market,eg：000001.SZ 平安银行

enum INDICATOR_FIELD
{
	INDICATOR_FIELD_0 = 0,
	INDICATOR_FIELD_DATE,
	INDICATOR_FIELD_TIME,
	INDICATOR_FIELD_CLOSE,
	INDICATOR_FIELD_OPEN, //0-4
	INDICATOR_FIELD_HIGH,
	INDICATOR_FIELD_LOW,
	INDICATOR_FIELD_NOW,
	INDICATOR_FIELD_VOLUME,
	INDICATOR_FIELD_LAST_VOLUME, //5-9
	INDICATOR_FIELD_AMOUNT,
	INDICATOR_FIELD_AVERAGE_PRICE,
	INDICATOR_FIELD_DELTA,
	INDICATOR_FIELD_RANGE_PERCENT,
	INDICATOR_FIELD_DELTA_PERCENT, //10-14
	INDICATOR_FIELD_WEIBI,
	INDICATOR_FIELD_BID_ASK_VOLUME_DIFF,
	INDICATOR_FIELD_VOLUME_RATIO,
	INDICATOR_FIELD_BID_VOLUME,
	INDICATOR_FIELD_ASK_VOLUME, //15-19
	INDICATOR_FIELD_BID_PRICE,
	INDICATOR_FIELD_ASK_PRICE,
	INDICATOR_FIELD_SOLD_VOLUME,
	INDICATOR_FIELD_BOUGHT_VOLUME,
	INDICATOR_FIELD_RECENT_DELTA_PERCENT, //20-24
	INDICATOR_FIELD_TURNOVER_RATE,
	INDICATOR_FIELD_AVERAGE_VOLUME,
	INDICATOR_FIELD_PRICE_EARNING_RATIO,
	INDICATOR_FIELD_POSITION,
	INDICATOR_FIELD_INTEREST, //25-29
	INDICATOR_FIELD_FULL_PRICE,
	INDICATOR_FIELD_BARGAIN,
	INDICATOR_FIELD_AVERAGE_BARGAIN_VOLUME,
	INDICATOR_FIELD_CEILING_PRICE,
	INDICATOR_FIELD_FLOOR_PRICE, //30-34
	INDICATOR_FIELD_TOTAL_VALUE,
	INDICATOR_FIELD_CURRENT_VALUE,
	INDICATOR_FIELD_PRICE_BOOK_VALUE_RATIO,
	INDICATOR_FIELD_PREV_POSITION,
	INDICATOR_FIELD_PREV_SETTLEMENT, //35-39
	INDICATOR_FIELD_SETTLEMENT,
	INDICATOR_FIELD_LAST_DELTA_POSITION,
	INDICATOR_FIELD_DELTA_POSITION,
	INDICATOR_FIELD_LAST_OPEN_CLOSE_POSITION,
	INDICATOR_FIELD_RISE_COUNT, //40-44
	INDICATOR_FIELD_DROP_COUNT,
	INDICATOR_FIELD_EQUAL_COUNT, //45-46
	INDICATOR_FIELD_DIGITS,
	INDICATOR_FIELD_BASE_MAX,
	//QUOTE
	INDICATOR_FIELD_ASK_PRICE_10 = INDICATOR_FIELD_BASE_MAX, // 卖十价		是(元)/是
	INDICATOR_FIELD_ASK_PRICE_9, // 卖九价		是(元)/是
	INDICATOR_FIELD_ASK_PRICE_8, // 卖八价		是(元)/是
	INDICATOR_FIELD_ASK_PRICE_7, // 卖七价		是(元)/是
	INDICATOR_FIELD_ASK_PRICE_6, // 卖六价		是(元)/是
	INDICATOR_FIELD_ASK_PRICE_5, // 卖五价		是(元)/是
	INDICATOR_FIELD_ASK_PRICE_4, // 卖四价		是(元)/是
	INDICATOR_FIELD_ASK_PRICE_3, // 卖三价		是(元)/是
	INDICATOR_FIELD_ASK_PRICE_2, // 卖二价		是(元)/是
	INDICATOR_FIELD_ASK_PRICE_1, // 卖一价，同卖出价IDF_ASK_PRICE
	INDICATOR_FIELD_BID_PRICE_1, // 买一价，同买入价IDF_BID_PRICE
	INDICATOR_FIELD_BID_PRICE_2, // 买二价		是(元)/是
	INDICATOR_FIELD_BID_PRICE_3, // 买三价		是(元)/是
	INDICATOR_FIELD_BID_PRICE_4, // 买四价		是(元)/是
	INDICATOR_FIELD_BID_PRICE_5, // 买五价		是(元)/是
	INDICATOR_FIELD_BID_PRICE_6, // 买六价		是(元)/是
	INDICATOR_FIELD_BID_PRICE_7, // 买七价		是(元)/是
	INDICATOR_FIELD_BID_PRICE_8, // 买八价		是(元)/是
	INDICATOR_FIELD_BID_PRICE_9, // 买九价		是(元)/是
	INDICATOR_FIELD_BID_PRICE_10, // 买十价		是(元)/是
	INDICATOR_FIELD_ASK_VOLUME_10, // 卖十量		是(股、张、份)
	INDICATOR_FIELD_ASK_VOLUME_9, // 卖九量		是(股、张、份)
	INDICATOR_FIELD_ASK_VOLUME_8, // 卖八量		是(股、张、份)
	INDICATOR_FIELD_ASK_VOLUME_7, // 卖七量		是(股、张、份)
	INDICATOR_FIELD_ASK_VOLUME_6, // 卖六量		是(股、张、份)
	INDICATOR_FIELD_ASK_VOLUME_5, // 卖五量		是(股、张、份)
	INDICATOR_FIELD_ASK_VOLUME_4, // 卖四量		是(股、张、份)
	INDICATOR_FIELD_ASK_VOLUME_3, // 卖三量		是(股、张、份)
	INDICATOR_FIELD_ASK_VOLUME_2, // 卖二量		是(股、张、份)
	INDICATOR_FIELD_ASK_VOLUME_1, // 卖一量		是(股、张、份)
	INDICATOR_FIELD_BID_VOLUME_1, // 买一量		是(股、张、份)
	INDICATOR_FIELD_BID_VOLUME_2, // 买二量		是(股、张、份)
	INDICATOR_FIELD_BID_VOLUME_3, // 买三量		是(股、张、份)
	INDICATOR_FIELD_BID_VOLUME_4, // 买四量		是(股、张、份)
	INDICATOR_FIELD_BID_VOLUME_5, // 买五量		是(股、张、份)
	INDICATOR_FIELD_BID_VOLUME_6, // 买六量		是(股、张、份)
	INDICATOR_FIELD_BID_VOLUME_7, // 买七量		是(股、张、份)
	INDICATOR_FIELD_BID_VOLUME_8, // 买八量		是(股、张、份)
	INDICATOR_FIELD_BID_VOLUME_9, // 买九量		是(股、张、份)
	INDICATOR_FIELD_BID_VOLUME_10, // 买十量	IDF_ASK_VOL_DIFF_
	INDICATOR_FIELD_MAX,
};

enum 
{
	REF_CALCDATA_NONE				= 0,	//默认只查找数据缓存
	REF_CALCDATA_LOADDATA			= 0X01,	//加载计算数据
	REF_CALCDATA_LOADFINANCE		= 0X02, //加载财务数据
	REF_CALCDATA_LOADFIELD			= 0X04,	//加载字段数据
	REF_CALCDATA_AUTOREQDATA		= 0X10,	//自动请求计算数据
	REF_CALCDATA_AUTOREQFINANCE		= 0X20,	//自动请求财务数据
	REF_CALCDATA_AUTOREQFIELD		= 0X40,	//自动请求字段数据
	REF_CALCDATA_AUTOREQQUOTEFIELD	= 0X80,	//自动请求报价字段数据
	REF_CALCDATA_DEFAULT			= (REF_CALCDATA_LOADDATA|REF_CALCDATA_AUTOREQDATA)
};

//////////////////////////////////////////////////////////////////////////
///画线部分

enum INDICATOR_DRAWLINE_TYPE
{
	TVLT_NONE		= 0,	//
	TVLT_DDLINE,			// 两点直线
	TVLT_DOTDOT,			// 两点线段
	TVLT_PLINE,				// 平行线
	TVLT_PERLINE,			// 百分比线
	TVLT_RADIALLINE,		// 两点射线
	TVLT_BARLINE,			// 栅形线
	//UGUNSLINE,			// 上甘氏线
	//DGUNSLINE,			// 下甘氏线
	TVLT_GUNSLINE,			// 甘氏线
	TVLT_GOLDLINE,			// 黄金分割线
	TVLT_BLACKHOLE,			// 神秘黑洞
	TVLT_ELLIPSEARC,		// 圆弧
	TVLT_MULTIARC,			// 多圆弧
	TVLT_GOLDARC,			// 弧度黄金线
	TVLT_CIRCLE,			// 圆
	TVLT_MULTIELLIPSE,		// 多圆
	TVLT_CYCLELINE,			// 周期线
	TVLT_FABCYCLELINE,		// 费波纳契周期线
	TVLT_SUZULINE,			// 速阻线
	TVLT_SINLINE,			// 正弦线
	TVLT_RECTANGLE,			// 矩形
	TVLT_TEXT,				// 文字
	TVLT_UPARROW,			// 上箭头
	TVLT_DOWNARROW,			// 下箭头
	TVLT_STOCKBOX,			// 箱体线
	TVLT_REGRESSLINE,		// 线性回归
	TVLT_REGRESSZONE,		// 线性回归带
	TVLT_REGRESSCHANNEL,	// 回归通道
	TVLT_COUNT=TVLT_REGRESSCHANNEL,	// 线型总数，程序内部控制用
	TVLT_MAX,
};

typedef struct tagTPoint
{
	double dvalue;			//y值
	unsigned long date;		//x日期
	unsigned long time;		//x时间
	//char lable[32];
}TPOINT,*PTPOINT;

//////////////////////////////////////////////////////////////////////////

#pragma pack()

#endif//_H_INDICATORDEF_H_