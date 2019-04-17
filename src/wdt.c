
#include "en675.h"
#include "reg.h"


void wdt_init(UINT milsec)
{
	SYS_WDT_LMT = (milsec*OSC_FREQ/1000);
	SYS_WDT_EN = 1;
}

void wdt_continue()
{
	SYS_WDT_CLR = 1;

	//	(SYS_WDT_LMT - SYS_WDT_CNT)*1000/(OSC_FREQ) = remain time (ms)
}
