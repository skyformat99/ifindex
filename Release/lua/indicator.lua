--����ģ��
--[[
module indicator  
--]]
--��ͬ������
--[[
local M = {};
local indicator = ...;
_G[indicator] = M;
package.loaded[indicator] = M    -- ��ģ�����뵽package.loaded�У���ֹ��μ���  
setfenv(1,M)                     -- ��ģ�������Ϊ�����Ļ�������ʹ��ģ���е����в���������ģ����еģ��������庯����ֱ�Ӷ�����ģ�����  
--]]

--[[
--�ű�����ʵ�ִ�ӡһ��table
function print_table(t, n)
    if "table" ~= type(t) then
        return 0;
    end
    n = n or 0;
    local str_space = "";
    for i = 1, n do
        str_space = str_space.."  ";
    end
    print(str_space.."{");
    for k, v in pairs(t) do
        local str_k_v = str_space.."  ["..tostring(k).."] = ";
        if "table" == type(v) then
            print(str_k_v);
            print_table(v, n + 1);
        else
            str_k_v = str_k_v..tostring(v);
            print(str_k_v);
        end
    end
    print(str_space.."}");
end
--]]

--system settings
INDICATOR_TYPE_MAIN = 0;						--��ͼָ��
INDICATOR_TYPE_SECOND = 1;					--��ͼָ��

INDICATOR_STYLE_TRADER = 0X01;			--����ָ��

INDEX_LINE = 0; --ָ����
INDEX_CALC = 1; --��������

PRICE_CLOSE=0;
PRICE_OPEN=1;
PRICE_HIGH=2;
PRICE_LOW=3;
PRICE_MEDIAN=4;
PRICE_TYPICAL=5;
PRICE_WEIGHTED=6;
PRICE_VOLUME=7;
PRICE_AMOUNT=8;
PRICE_TICKVOLUME=9;
PRICE_AVPRICE=10;

MODE_SMA=0;
MODE_EMA=1;
MODE_SMMA=2;
MODE_LWMA=3;
MODE_DMA=4;

DRAW_LINE = 0; --����
	DRAW_SECTION = 1; --����
	DRAW_STICK = 2; --��״��
	DRAW_HISTOGRAM = 3; --��״ͼ
	DRAW_HISTOGRAM2 = 4; --����ָ���������״ͼ

LINE_SOLID = 0; --ʵ��
	LINE_DASH = 1; --����
	LINE_DOT = 2; --����
	LINE_DASHDOT = 3; --�۵���
	LINE_DASHDOTDOT = 4; --˫�۵���
	
	OP_NONE			= 0;
	OP_BUY			= 1;	--Buy operation
	OP_SELL			= 2;	--Sell operation
	OP_BUYLIMIT		= 3;	--Buy limit pending order
	OP_SELLLIMIT	= 4;	--Sell limit pending order
	OP_BUYSTOP		= 5;	--Buy stop pending order
	OP_SELLSTOP		= 6;	--Sell stop pending order

DATE=0
TIME=0
OPEN=0
HIGH=0
LOW=0
CLOSE=0

function OnPreFilter()
	--init filter data
	return 1;
end

function OnPreCalculate(count,calculated)
	if(count<=0) 
		then
 				return(0);
 		end
 		
	--init calculate data
	DATE = iGetPriceDate(0);
	TIME = iGetPriceTime(0);
	OPEN = iGetPriceValue(PRICE_OPEN,0);
	HIGH = iGetPriceValue(PRICE_HIGH,0);
	LOW = iGetPriceValue(PRICE_LOW,0);
	CLOSE = iGetPriceValue(PRICE_CLOSE,0);
	print(DATE,TIME,OPEN,HIGH,LOW,CLOSE);
	
	return 1;
end

--[[
function M.start()
    print("start");
end

function M.stop()
    print("stop");
end

return M;
--]]