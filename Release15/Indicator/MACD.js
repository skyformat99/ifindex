//system settings
var INDICATOR_TYPE_MAIN = 0, //主图指标
INDICATOR_TYPE_SECOND = 1; //幅图指标

var PRICE_CLOSE=0,
PRICE_OPEN=1,
PRICE_HIGH=2,
PRICE_LOW=3,
PRICE_MEDIAN=4,
PRICE_TYPICAL=5,
PRICE_WEIGHTED=6,
PRICE_VOLUME=7,
PRICE_AMOUNT=8;
var MODE_SMA=0,
MODE_EMA=1,
MODE_SMMA=2,
MODE_LWMA=3,
MODE_DMA=4;
var LINE_STYLE_SOLID = 0, //实线
	LINE_STYLE_DASH = 1, //折线
	LINE_STYLE_DOT = 2, //虚线
	LINE_STYLE_DASHDOT = 3, //折点线
	LINE_STYLE_DASHDOTDOT = 4, //双折点线
	LINE_STYLE_STICK = 5,
	LINE_STYLE_STICK3D = 6;
	
function Input(name,value)
{
		this.name = name;
		this.value = value;
		this.init = init;
		function init()
    {
        iSetInput(this.name,this.value);
    }
    this.update = update;
    function update()
    {
        value = iGetInput(name);
    }
}

//indicator settings
iSetType(INDICATOR_TYPE_MAIN);
//input settings
iSetInput("InpFastEMA",12);   // Fast EMA Period
iSetInput("InpSlowEMA",26);   // Slow EMA Period
iSetInput("InpSignalSMA",9);  // Signal SMA Period
//index settings
iSetIndexCount(3);
iSetIndexName(0,"DIF");
iSetIndexName(1,"DEA");
iSetIndexName(1,"MACD");
iSetIndexStyle(2,LINE_STYLE_STICK);

function oncalculate(count,calculated)
{
		//get input settings
 		var InpFastEMA = Number(iGetInput("InpFastEMA"));   // Fast EMA Period
		var InpSlowEMA = Number(iGetInput("InpSlowEMA"));   // Slow EMA Period
		var InpSignalSMA = Number(iGetInput("InpSignalSMA"));  // Signal SMA Period
		
		if(count<=InpSignalSMA)
 				return(0);
 
		//ref indicator
		var hFastMA = iMA("",0,InpFastEMA,0,MODE_EMA,PRICE_CLOSE);
		var hSlowMA = iMA("",0,InpSlowEMA,0,MODE_EMA,PRICE_CLOSE);
		
  	var i,limit;
		//last calculated bar will be recounted
  	limit=count-calculated;
  	if(calculated>0)
    		limit++;
    		
		//DIF
  	for(i=0; i<limit; i++) {
  			var dif = iGetIndexValue(0,i,hFastMA)-iGetIndexValue(0,i,hSlowMA);
    		iSetIndexValue(0, i, dif);
    }
    
    //DEA
    iMAIndexOnLine(1, InpSignalSMA, MODE_EMA, 0);
    
		//MACD
  	for(i=0; i<limit; i++) {
  			var macd = (iGetIndexValue(0,i)-iGetIndexValue(1,i))*2;
    		iSetIndexValue(2, i, macd);
    }
  	
		//return calculated
  	return(count);
}
