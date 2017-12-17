require("..lua.indicator")

iSet({
		type=INDICATOR_TYPE_MAIN,
		N=20,
		M=2
})

function OnInit()
	--index settings
	iSetIndexName(0,"BOLL");
	iSetIndexName(1,"UPPER");
	iSetIndexName(2,"LOWER");
end

function OnCalculate(count,calculated)
		if(count<=0) 
		then
 				return(0);
 		end
 	
		--ref indicator
		--hMA = iMA("",0,N,0,MODE_SMA,PRICE_CLOSE);
		hBands = iBands("",0,N,0,M,PRICE_CLOSE);
	
  	i=0;
  	limit=0;
		--last calculated bar will be recounted
  	limit=count-calculated;
  	if(calculated>0) 
  	then
    		limit = limit + 1;
    end
    		
  	for i=0,limit-1 do
  			--boll = iGetIndexValue(0,i,hMA);
  			upper = iGetIndexValue(0,i,hBands);
  			lower = iGetIndexValue(1,i,hBands);
  			boll = iGetIndexValue(2,i,hBands);
    		iSetIndexValue(0, i, boll);
    		iSetIndexValue(1, i, upper);
    		iSetIndexValue(2, i, lower);
    end
  	
		--return calculated
  	return(count);
end
