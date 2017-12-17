require("..lua.indicator")

iSet({
		type=INDICATOR_TYPE_SECOND,
		N=9,
		M1=3,
		M2=3
})

function OnInit()
	--index settings
	iSetIndexName(0,"K");
	iSetIndexName(1,"D");
	iSetIndexName(2,"J");
	iSetIndexDigits(0,3);
	iSetIndexDigits(1,3);
	iSetIndexDigits(2,3);
end

function OnCalculate(count,calculated)
    if(count<=0) 
		then
 				return(0);
 		end
 		
 		hStochastic = iStochastic("",0,N,M1,M2);
 		hMACDTrader = iRef("MyMACDTrader","",0); --test ref macdtrader should return null.
 		
 		i=0;
 		j=0;
  	limit=0;
		--last calculated bar will be recounted
  	limit=count-calculated;
  	if(calculated>0) 
  	then
    		limit = limit + 1;
    end
    
  	for i=0,3 do
  		for j=0,limit-1 do
    		iSetIndexValue(i, j, iGetIndexValue(i,j,hStochastic));
    	end
    end
  	
		--return calculated
  	return(count);
end