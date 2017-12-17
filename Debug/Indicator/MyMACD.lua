require("..lua.indicator")

iSet({
		type=INDICATOR_TYPE_POOL,
		InpFastEMA=12,
		InpSlowEMA=26,
		InpSignalSMA=9,
		index_name1="DIF",
		index_name2="DEA",
		index_name3="MACD",
		index0 = {
			digits=3
		},
		index1 = {
			draw=DRAW_STICK,
			digits=3
		},
		index2 = {
			digits=3
		}
})

function OnFilter()
	iAddPool("600000.SH");
	iAddPool("600004.SH");
	iAddPool("000001.SZ");
end

function OnCalculate(count,calculated)
		if(count<=0) 
		then
 				return(0);
 		end
		
		--ref indicator
		hFastMA = iMA("",0,InpFastEMA,0,MODE_EMA,PRICE_CLOSE);
		hSlowMA = iMA("",0,InpSlowEMA,0,MODE_EMA,PRICE_CLOSE);
		
		--
  	
		--return calculated
  	return(count);
end
