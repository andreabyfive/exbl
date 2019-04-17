#include "en675.h"
#include "reg.h"
#include "ddr.h"
#include "rv_utils.h" // dmwrite32, dmread32

#define TEST_DDR_SIZE DDR_SIZE
//#define TEST_DDR_SIZE 1*1024

char DdrMapTest(void)
{
	volatile ULONG *pDDR = (volatile ULONG *)DDR_BASE;
	//printf("DDR MAP Test - Write\n");
	for(pDDR = (volatile ULONG *)DDR_BASE; pDDR < (volatile ULONG *)(DDR_BASE+TEST_DDR_SIZE); pDDR++)
	{
	  if ((ULONG)pDDR % 64 == 0) hwflush_dcache_range((ULONG)pDDR, 0x40);
	*pDDR = (ULONG)pDDR;
	}
	ULONG ok = 0, fail = 0;
	for(pDDR = (volatile ULONG *)DDR_BASE; pDDR < (volatile ULONG *)(DDR_BASE+TEST_DDR_SIZE); pDDR++)
	{
		if ((ULONG)pDDR % 64 == 0) hwflush_dcache_range((ULONG)pDDR, 0x40);
		ULONG getdata = *pDDR;
		if (getdata != (ULONG)pDDR)
		{
			_printf("DDR Test - X: %08lx 0x%08lx\n", pDDR, getdata);
                fail++;
		}
		else
		{
			ok++;
		}
     }
	_printf("DDR Test - Done(O:%lu X:%lu)\n", ok, fail);
	return ((fail)? 1 : 0);
}

void DqG0OutDly(UINT var)
{
	DDR_DLY_DQ7OUT  = var;
	DDR_DLY_DQ6OUT  = var;
	DDR_DLY_DQ5OUT  = var;
	DDR_DLY_DQ4OUT  = var;
	DDR_DLY_DQ3OUT  = var;
	DDR_DLY_DQ2OUT  = var;
	DDR_DLY_DQ1OUT  = var;
	DDR_DLY_DQ0OUT  = var;
}
void DqG1OutDly(UINT var)
{
	DDR_DLY_DQ15OUT = var;
	DDR_DLY_DQ14OUT = var;
	DDR_DLY_DQ13OUT = var;
	DDR_DLY_DQ12OUT = var;
	DDR_DLY_DQ11OUT = var;
	DDR_DLY_DQ10OUT = var;
	DDR_DLY_DQ9OUT  = var;
	DDR_DLY_DQ8OUT  = var;
}
void DqG2OutDly(UINT var)
{
	DDR_DLY_DQ23OUT = var;
	DDR_DLY_DQ22OUT = var;
	DDR_DLY_DQ21OUT = var;
	DDR_DLY_DQ20OUT = var;
	DDR_DLY_DQ19OUT = var;
	DDR_DLY_DQ18OUT = var;
	DDR_DLY_DQ17OUT = var;
	DDR_DLY_DQ16OUT = var;
}
void DqG3OutDly(UINT var)
{
	DDR_DLY_DQ31OUT = var;
	DDR_DLY_DQ30OUT = var;
	DDR_DLY_DQ29OUT = var;
	DDR_DLY_DQ28OUT = var;
	DDR_DLY_DQ27OUT = var;
	DDR_DLY_DQ26OUT = var;
	DDR_DLY_DQ25OUT = var;
	DDR_DLY_DQ24OUT = var;
}
void DqOutDly(UINT var)
{
	DqG0OutDly(var);
	DqG1OutDly(var);
	DqG2OutDly(var);
	DqG3OutDly(var);
}
void DmOutDly(UINT var)
{
	DDR_DLY_DM0OUT  = var;
	DDR_DLY_DM1OUT  = var;
	DDR_DLY_DM2OUT  = var;
	DDR_DLY_DM3OUT  = var;
}
void CaOutDly(int var)
{
	DDR_DLY_CA9OUT  = var;
	DDR_DLY_CA8OUT  = var;
	DDR_DLY_CA7OUT  = var;
	DDR_DLY_CA6OUT  = var;
	DDR_DLY_CA5OUT  = var;
	DDR_DLY_CA4OUT  = var;
	DDR_DLY_CA3OUT  = var;
	DDR_DLY_CA2OUT  = var;
	DDR_DLY_CA1OUT  = var;
	DDR_DLY_CA0OUT  = var;
}

char ddr_cal_test()
{
	char result = 0;
	DDR_MR_ADR = 32;
	DDR_MR_WE  = 0;
	DDR_MR_REQ = 1;
	while(DDR_MR_REQ);
	if(DDR_MR_RDDAT0!=0x00000000) result++;
	if(DDR_MR_RDDAT1!=0x00000000) result++;
	if(DDR_MR_RDDAT2!=0xffffffff) result++;
	if(DDR_MR_RDDAT3!=0xffffffff) result++;
	//if(result>0) printf("%08x %08x %08x %08x ", DDR_MR_RDDAT0,DDR_MR_RDDAT1,DDR_MR_RDDAT2,DDR_MR_RDDAT3);
	DDR_MR_ADR = 40;
	DDR_MR_WE  = 0;
	DDR_MR_REQ = 1;
	while(DDR_MR_REQ);
	if(DDR_MR_RDDAT0!=0xffffffff) result++;
	if(DDR_MR_RDDAT1!=0x00000000) result++;
	if(DDR_MR_RDDAT2!=0xffffffff) result++;
	if(DDR_MR_RDDAT3!=0x00000000) result++;
	//if(result>0) printf("%08x %08x %08x %08x\n", DDR_MR_RDDAT0,DDR_MR_RDDAT1,DDR_MR_RDDAT2,DDR_MR_RDDAT3);
	DDR_MR_ADR = 32;
	DDR_MR_WE  = 0;
	DDR_MR_REQ = 1;
	while(DDR_MR_REQ);
	if(DDR_MR_RDDAT0!=0x00000000) result++;
	if(DDR_MR_RDDAT1!=0x00000000) result++;
	if(DDR_MR_RDDAT2!=0xffffffff) result++;
	if(DDR_MR_RDDAT3!=0xffffffff) result++;
	//if(result>0) printf("%08x %08x %08x %08x ", DDR_MR_RDDAT0,DDR_MR_RDDAT1,DDR_MR_RDDAT2,DDR_MR_RDDAT3);
	DDR_MR_ADR = 40;
	DDR_MR_WE  = 0;
	DDR_MR_REQ = 1;
	while(DDR_MR_REQ);
	if(DDR_MR_RDDAT0!=0xffffffff) result++;
	if(DDR_MR_RDDAT1!=0x00000000) result++;
	if(DDR_MR_RDDAT2!=0xffffffff) result++;
	if(DDR_MR_RDDAT3!=0x00000000) result++;
	//if(result>0) printf("%08x %08x %08x %08x\n", DDR_MR_RDDAT0,DDR_MR_RDDAT1,DDR_MR_RDDAT2,DDR_MR_RDDAT3);
	return result;
}
char ddr_rw_test()
{
	char result = 0;
	UINT *ADDR_BASE = 0x80000000;
	hwflush_dcache_range(0x80000000, 0x40);
	ADDR_BASE[0] = 0xffffffff;
	ADDR_BASE[1] = 0;
	ADDR_BASE[2] = 0xffffffff;
	ADDR_BASE[3] = 0;
	ADDR_BASE[4] = 0xffffffff;
	ADDR_BASE[5] = 0xffffffff;
	ADDR_BASE[6] = 0;
	ADDR_BASE[7] = 0;
	ADDR_BASE[8] = 0xaaaaaaaa;
	ADDR_BASE[9] = 0x55555555;
	ADDR_BASE[10] = 0xaaaaaaaa;
	ADDR_BASE[11] = 0x55555555;
	ADDR_BASE[12] = 0x55555555;
	ADDR_BASE[13] = 0xaaaaaaaa;
	ADDR_BASE[14] = 0x55555555;
	ADDR_BASE[15] = 0xaaaaaaaa;
	hwflush_dcache_range(0x80000000, 0x40);
	if(ADDR_BASE[0]!=0xffffffff) result++;
	if(ADDR_BASE[1]!=0x00000000) result++;
	if(ADDR_BASE[2]!=0xffffffff) result++;
	if(ADDR_BASE[3]!=0x00000000) result++;
	if(ADDR_BASE[4]!=0xffffffff) result++;
	if(ADDR_BASE[5]!=0xffffffff) result++;
	if(ADDR_BASE[6]!=0x00000000) result++;
	if(ADDR_BASE[7]!=0x00000000) result++;
	if(ADDR_BASE[8]!=0xaaaaaaaa) result++;
	if(ADDR_BASE[9]!=0x55555555) result++;
	if(ADDR_BASE[10]!=0xaaaaaaaa) result++;
	if(ADDR_BASE[11]!=0x55555555) result++;
	if(ADDR_BASE[12]!=0x55555555) result++;
	if(ADDR_BASE[13]!=0xaaaaaaaa) result++;
	if(ADDR_BASE[14]!=0x55555555) result++;
	if(ADDR_BASE[15]!=0xaaaaaaaa) result++;
	//printf("%08x %08x %08x %08x %08x %08x %08x %08x\n", ADDR_BASE[0], ADDR_BASE[1], ADDR_BASE[2], ADDR_BASE[3], ADDR_BASE[4], ADDR_BASE[5], ADDR_BASE[6], ADDR_BASE[7]);
	return result;
}

void DdrGetId()
{
	DDR_MR_ADR = 5;
	DDR_MR_WE  = 0;
	DDR_MR_REQ = 1;
	while(DDR_MR_REQ);
	_printf("MR5:%08x\n", DDR_MR_RDDAT0);
	DDR_MR_ADR = 8;
	DDR_MR_WE  = 0;
	DDR_MR_REQ = 1;
	while(DDR_MR_REQ);
	_printf("MR8:%08x\n", DDR_MR_RDDAT0);
}

void DdrOn()
{
	if(!DDR_PWR_CUR)
	{
		DDR_PWR_REQ = 1;
		while(DDR_PWR_REQ);
	}
}
void DdrOff()
{
	if(DDR_PWR_CUR)
	{
		DDR_PWR_REQ = 1;
		while(DDR_PWR_REQ);
	}
}
void DdrOffOn()
{
	DdrOff();
	DdrOn();
}

void DdrInit(BYTE Sel)
{
	int i;
	char min=15, max=0;

	DdrOff();

	DDR_MEM_SEL = Sel;// (0:128Mb S2/S4, 1:256Mb S2/S4, 2:512Mb S2/S4, 3:1Gb S2, 4:1Gb S4, 5: 2Gb S2, 6:2Gb S4, 7:4Gb S2/S4)
	DDR_RD_EN_MASK  = 0x08;
	DDR_RD_VAL_EDGE = 1;
	DDR_RD_VAL_LTC	= 6;
	DDR_MRR_VAL_LTC	= 6;
	DDR_WR_LTC 		= 1;

	DdrOn();

	for(i=0;i<16;i++)
	{
		DDR_DLY_CSOUT = i;
		CaOutDly(i);
		char temp = ddr_cal_test();
		if(temp!=0) _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
		DdrOffOn();
	}
	if(min==15){ _printf("CA FAIL\n"); while(1);}
	CaOutDly((max+min+1)>>1);
	DDR_DLY_CSOUT = (max+min+1)>>1;
	_printf("DDR_DLY_CA*OUT : %d  ",DDR_DLY_CA9OUT);
	_printf("DDR_DLY_CSOUT : %d\n",DDR_DLY_CSOUT);
        DdrOffOn();
	min=15, max=0;
	for(i=0;i<16;i++)
	{
		DDR_DLY_DQS0IN = i;
		char temp = ddr_cal_test();
		if(temp!=0)  _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
	}
	if(min==15){ _printf("DDR_DLY_DQS0IN FAIL\n"); while(1);}
	DDR_DLY_DQS0IN = min+2;
	_printf("DDR_DLY_DQS0IN : %d\n",DDR_DLY_DQS0IN);

	min=15, max=0;
	for(i=0;i<16;i++)
	{
		DDR_DLY_DQS1IN = i;
		char temp = ddr_cal_test();
		if(temp!=0)  _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
	}
	if(min==15){ _printf("DDR_DLY_DQS1IN FAIL\n"); while(1);}
	DDR_DLY_DQS1IN = min+2;
	_printf("DDR_DLY_DQS1IN : %d\n",DDR_DLY_DQS1IN);

	min=15, max=0;
	for(i=0;i<16;i++)
	{
		DDR_DLY_DQS2IN = i;
		char temp = ddr_cal_test();
		if(temp!=0)  _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
	}
	if(min==15){ _printf("DDR_DLY_DQS2IN FAIL\n"); while(1);}
	DDR_DLY_DQS2IN = min+2;
	_printf("DDR_DLY_DQS2IN : %d\n",DDR_DLY_DQS2IN);

	min=15, max=0;
	for(i=0;i<16;i++)
	{
		DDR_DLY_DQS3IN = i;
		char temp = ddr_cal_test();
		if(temp!=0)  _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
	}
	if(min==15){ _printf("DDR_DLY_DQS3IN FAIL\n"); while(1);}
	DDR_DLY_DQS3IN = min+2;
	DDR_RD_VAL_LTC	= 7;

	_printf("DDR_DLY_DQS3IN : %d\n",DDR_DLY_DQS3IN);

	min=15, max=0;
	for(i=0;i<16;i++)
	{
		DmOutDly(i);
		DqOutDly(i);
		char temp = ddr_rw_test();
		if(temp!=0)  _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
	}
	if(min==15){ _printf("DDR_DMDQ_OUT FAIL\n"); while(1);}
	DmOutDly(min+2);
	DqOutDly(min+2);
	_printf("DDR_DMDQ_OUT : %d\n",min+2);

	min=15, max=0;
	for(i=0;i<16;i++)
	{
		DDR_DLY_DM0OUT = i;
		char temp = ddr_rw_test();
		if(temp!=0)  _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
	}
	DDR_DLY_DM0OUT = min+2;
	_printf("DDR_DLY_DM0OUT : %d\n",DDR_DLY_DM0OUT);

	min=15, max=0;
	for(i=0;i<16;i++)
	{
		DDR_DLY_DM1OUT = i;
		char temp = ddr_rw_test();
		if(temp!=0)  _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
	}
	DDR_DLY_DM1OUT = min+2;
	_printf("DDR_DLY_DM1OUT : %d\n",DDR_DLY_DM1OUT);
	min=15, max=0;
	for(i=0;i<16;i++)
	{
		DDR_DLY_DM2OUT = i;
		char temp = ddr_rw_test();
		if(temp!=0)  _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
	}
	DDR_DLY_DM2OUT = min+2;
	_printf("DDR_DLY_DM2OUT : %d\n",DDR_DLY_DM2OUT);
	min=15, max=0;
	for(i=0;i<16;i++)
	{
		DDR_DLY_DM3OUT = i;
		char temp = ddr_rw_test();
		if(temp!=0)  _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
	}
	DDR_DLY_DM3OUT = min+2;
	_printf("DDR_DLY_DM3OUT : %d\n",DDR_DLY_DM3OUT);

	min=15, max=0;
	for(i=0;i<16;i++)
	{
		DqG0OutDly(i);
		char temp = ddr_rw_test();
		if(temp!=0)  _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
	}
	DqG0OutDly(min+2);
	_printf("DDR_DQG0_OUT : %d\n",min+2);
	min=15, max=0;
	for(i=0;i<16;i++)
	{
		DqG1OutDly(i);
		char temp = ddr_rw_test();
		if(temp!=0)  _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
	}
	DqG1OutDly(min+2);
	_printf("DDR_DQG1_OUT : %d\n",min+2);
	min=15, max=0;
	for(i=0;i<16;i++)
	{
		DqG2OutDly(i);
		char temp = ddr_rw_test();
		if(temp!=0)  _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
	}
	DqG2OutDly(min+2);
	_printf("DDR_DQG2_OUT : %d\n",min+2);



	min=15, max=0;
	for(i=0;i<16;i++)
	{
		DqG3OutDly(i);
		char temp = ddr_rw_test();
		if(temp!=0)  _printf("_");
		else
		{
			_printf("*");
			if(min>i) min = i;
			if(max<i) max = i;
		}
	}
	DqG3OutDly(min+2);
	_printf("DDR_DQG3_OUT : %d\n",min+2);

//	DdrMapTest();
}

