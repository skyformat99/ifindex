require("..lua.indicator")

iSet({
		type=INDICATOR_TYPE_SECOND,
		trade=true,
		InpFastEMA=12,
		InpSlowEMA=26,
		InpSignalSMA=9,
		index0 = {
			name="DIF",
			digits=3
		},
		index1 = {
			name="DEA",
			draw=DRAW_STICK,
			digits=3
		},
		index2 = {
			name="MACD",
			digits=3
		}
})

function OnCalculate(count,calculated)
		if(count<=0) 
		then
 				return(0);
 		end
 
		--ref indicator
		hFastMA = iMA("",0,InpFastEMA,0,MODE_EMA,PRICE_CLOSE);
		hSlowMA = iMA("",0,InpSlowEMA,0,MODE_EMA,PRICE_CLOSE);
		
  	i=0;
  	limit=0;
		--last calculated bar will be recounted
  	limit=count-calculated;
  	if(calculated>0) 
  	then
    		limit = limit + 1;
    end
    		
		--DIF
  	for i=0,limit-1 do
  			dif = iGetIndexValue(0,i,hFastMA)-iGetIndexValue(0,i,hSlowMA);
    		iSetIndexValue(0, i, dif);
    end
    
    --DEA
    iMAIndexOnLine(1, InpSignalSMA, MODE_EMA, 0);
    
		--MACD
  	for i=0,limit-1 do
  			macd = (iGetIndexValue(0,i)-iGetIndexValue(1,i))*2;
    		iSetIndexValue(2, i, macd);
    end
    
    --if Cross do Buy or Sell 
    cross = iCross(0,1);
    if(cross>=0) 
  	then
    		iOrderSend("",OP_BUY,100);
    end
    if(cross<0) 
  	then
    		iOrderSend("",OP_SELL,100);
    end
    
		iOrderClose();
		iOrdersSelect();
		iOrdersTotal();
		iOrderSelectByIndex();
		iOrderSelectByTicket();
		iOrderSelectByMagic();
		iOrderType();
		iOrderTicket();
		iOrderSymbol();
		iOrderOpenPrice();
		iOrderClosePrice();
		iOrderOpenTime();
		iOrderCloseTime();
		iOrderExpiration();
		iOrderLots();
		iOrderProfit();
		iOrderTakeProfit();
		iOrderStopLoss();
		iOrderCommission();
		iOrderMagicNumber();
		iOrderComment();
		iOrderExtra();
  	
		--return calculated
  	return(count);
end
