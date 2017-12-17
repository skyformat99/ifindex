require("..lua.indicator")

iSet({
		type=INDICATOR_TYPE_MAIN,
		InpTenkan=9,
		InpKijun=26,
		InpSenkou=52
})

local Tenkan=0
local Kijun=1
local SpanA=2
local SpanB=3
local Chikou=4
local SpanA2=5
local SpanB2=6

local ExtBegin=0

function OnInit()

		--index settings
		iSetIndexName(Tenkan,"Tenkan");
		iSetIndexName(Kijun,"Kijun");
		iSetIndexName(SpanA,"SpanA");
		iSetIndexName(SpanB,"SpanB");
		iSetIndexName(Chikou,"Chikou");
		iSetIndexName(SpanA2,"SpanA2");
		iSetIndexName(SpanB2,"SpanB2");
		
		iSetIndexType(Tenkan,INDEX_LINE);
		iSetIndexType(Kijun,INDEX_LINE);
		iSetIndexType(SpanA,INDEX_LINE);
		iSetIndexType(SpanB,INDEX_CALC);
		iSetIndexType(Chikou,INDEX_LINE);
		iSetIndexType(SpanA2,INDEX_LINE);
		iSetIndexType(SpanB2,INDEX_LINE);

		iSetIndexBegin(Tenkan,InpTenkan);
		
		iSetIndexBegin(Kijun,InpKijun);
		
		ExtBegin=InpKijun;
		if(ExtBegin<InpTenkan)
		then
		   ExtBegin=InpTenkan;
		end
		   
		iSetIndexDraw(SpanA,DRAW_HISTOGRAM2);
		iSetIndexLine(SpanA,LINE_DOT);
		iSetIndexBegin(SpanA,InpKijun+ExtBegin);
		iSetIndexShift(SpanA,InpKijun);
		iSetIndexNext(SpanA,SpanB);
		
		iSetIndexDraw(SpanB,DRAW_HISTOGRAM2);
		iSetIndexLine(SpanB,LINE_DOT);
		iSetIndexBegin(SpanB,InpKijun+InpSenkou);
		iSetIndexShift(SpanB,InpKijun);
		
		iSetIndexDraw(Chikou,DRAW_LINE);
		iSetIndexShift(Chikou,-InpKijun);
		
		iSetIndexDraw(SpanA2,DRAW_LINE);
		iSetIndexLine(SpanA2,LINE_DOT);
		iSetIndexBegin(SpanA2,InpKijun+ExtBegin);
		iSetIndexShift(SpanA2,InpKijun);
		   
		iSetIndexDraw(SpanB2,DRAW_LINE);
		iSetIndexLine(SpanB2,LINE_DOT);
		iSetIndexBegin(SpanB2,InpKijun+InpSenkou);
		iSetIndexShift(SpanB2,InpKijun);
		
end
  
function OnCalculate(count,calculated)
		if(count<=0) 
		then
 				return(0);
 		end
		
		--begin calculated
		i = 0;
 		k = 0;
 		pos = 0;
    high_value = 0;
    low_value = 0;
    limit=0;
		--last calculated bar will be recounted
  	limit=count-calculated;
  	if(calculated>0) 
  	then
    		limit = limit + 1;
    end
   
    --Close = iGetPriceValue(PRICE_CLOSE,0);

   if(count<InpTenkan or count<InpKijun or count<InpSenkou)
   then
   		--[[
   		for i=0,limit do
   		 		iSetIndexValue(Tenkan, i, 0.00);
   		 		iSetIndexValue(Kijun, i, 0.00);
   		 		iSetIndexValue(SpanA, i, 0.00);
         	iSetIndexValue(SpanA2, i, 0.00);
         	iSetIndexValue(Chikou, i, 0.00);
         	iSetIndexValue(SpanB, i, 0.00);
         	iSetIndexValue(SpanB2, i, 0.00);
      end
      --]]
      return(0);
   end
--[[ 
--counting from 0 to count
--ArraySetAsSeries(ExtTenkanBuffer,false);
--ArraySetAsSeries(ExtKijunBuffer,false);
--ArraySetAsSeries(ExtSpanA_Buffer,false);
--ArraySetAsSeries(ExtSpanB_Buffer,false);
--ArraySetAsSeries(ExtChikouBuffer,false);
--ArraySetAsSeries(ExtSpanA2_Buffer,false);
--ArraySetAsSeries(ExtSpanB2_Buffer,false);
--ArraySetAsSeries(open,false);
--ArraySetAsSeries(high,false);
--ArraySetAsSeries(low,false);
--ArraySetAsSeries(close,false);
--Tenkan Sen
--]]
--initial zero
   if(calculated<1)
   then
   		for i=0,InpTenkan do
         iSetIndexValue(Tenkan, iReversePos(i), 0);
      end
      for i=0,InpKijun do
         iSetIndexValue(Kijun, iReversePos(i), 0);
      end
      for i=0,ExtBegin do
         iSetIndexValue(SpanA, iReversePos(i), 0);
         iSetIndexValue(SpanA2, iReversePos(i), 0);
      end
      for i=0,InpSenkou do
         iSetIndexValue(SpanB, iReversePos(i), 0);
         iSetIndexValue(SpanB2, iReversePos(i), 0);
      end
    end

   pos=InpTenkan-1;
   if(calculated>InpTenkan)
   then
      pos=calculated-1;
   end
   for i=pos,count-1 do
      high_value=iGetPriceValue(PRICE_HIGH,iReversePos(i));
      low_value=iGetPriceValue(PRICE_LOW,iReversePos(i));
      k=i+1-InpTenkan;
      while(k<=i) do
         if(high_value<iGetPriceValue(PRICE_HIGH,iReversePos(k))) then
            high_value=iGetPriceValue(PRICE_HIGH,iReversePos(k));
         end
         if(low_value>iGetPriceValue(PRICE_LOW,iReversePos(k))) then
            low_value=iGetPriceValue(PRICE_LOW,iReversePos(k));
         end
         k = k + 1;
      end
      iSetIndexValue(Tenkan, iReversePos(i), (high_value+low_value)/2);
   end
--Kijun Sen
   pos=InpKijun-1;
   if(calculated>InpKijun)
   then
      pos=calculated-1;
   end
   for i=pos,count-1 do
      high_value=iGetPriceValue(PRICE_HIGH,iReversePos(i));
      low_value=iGetPriceValue(PRICE_LOW,iReversePos(i));
      k=i+1-InpKijun;
      while(k<=i) do
         if(high_value<iGetPriceValue(PRICE_HIGH,iReversePos(k))) then
            high_value=iGetPriceValue(PRICE_HIGH,iReversePos(k));
         end
         if(low_value>iGetPriceValue(PRICE_LOW,iReversePos(k))) then
            low_value=iGetPriceValue(PRICE_LOW,iReversePos(k));
         end
         k = k + 1;
      end
      iSetIndexValue(Kijun, iReversePos(i), (high_value+low_value)/2);
   end
--Senkou Span A
   pos=ExtBegin-1;
   if(calculated>ExtBegin)
   then
      pos=calculated-1;
   end
   for i=pos,count-1 do
      iSetIndexValue(SpanA, iReversePos(i), (iGetIndexValue(Kijun,iReversePos(i))+iGetIndexValue(Tenkan,iReversePos(i)))/2);
      iSetIndexValue(SpanA2, iReversePos(i), iGetIndexValue(SpanA,iReversePos(i)));
   end
--Senkou Span B
   pos=InpSenkou-1;
   if(calculated>InpSenkou)
   then
      pos=calculated-1;
   end
   for i=pos,count-1 do
      high_value=iGetPriceValue(PRICE_HIGH,iReversePos(i));
      low_value=iGetPriceValue(PRICE_LOW,iReversePos(i));
      k=i+1-InpSenkou;
      while(k<=i) do
         if(high_value<iGetPriceValue(PRICE_HIGH,iReversePos(k))) then
            high_value=iGetPriceValue(PRICE_HIGH,iReversePos(k));
         end
         if(low_value>iGetPriceValue(PRICE_LOW,iReversePos(k))) then
            low_value=iGetPriceValue(PRICE_LOW,iReversePos(k));
         end
         k = k + 1;
      end
      iSetIndexValue(SpanB, iReversePos(i), (high_value+low_value)/2);
      iSetIndexValue(SpanB2, iReversePos(i), iGetIndexValue(SpanB,iReversePos(i)));
   end
--Chikou Span
   pos=0;
   if(calculated>1)
   then
      pos=calculated-1;
   end
   for i=pos,count-1 do
      iSetIndexValue(Chikou, iReversePos(i), iGetPriceValue(PRICE_CLOSE,iReversePos(i)));
   end

   return(count);
end
