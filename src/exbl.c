
#include "uart.h"
#include "print.h"
#include "boot.h"
#include "sfls.h"
#include "ddr.h"
#include "en675.h"
#include "reg.h"
#include <stdint.h>
#include "uart_regcontrol.h"

#define SIZE_OF_DATA 1024*16
//int g_test_data = 0;

//char g_key=0x0f;


#define SLEEP_CNT 100000

#define BASE_ADDR 0x80003000

void sleep_(int cnt)
{

	for(int i=0;i<cnt;i++){
		__asm("C.NOP");
	}

}
void sleep_s(void){
	__asm("C.NOP");
}

void main_(void)
{
  _printf("exception\n");
  while(1);
}

#define SRAM_EMPTY  0xa0010000
#define SRAM_SIZE  1024


#define CLINT_BASE         0x02000000
volatile uint64_t* mtime =      (uint64_t*)(CLINT_BASE + 0xbff8);


void main_0(void)
{



//	SYS_CPU_EN = 0x0;
//	_init_data_section();
//	_init_bss_section();

//	chksum16(RAM_BASE+0x10000, 0x10);

//	sha224(RAM_BASE+0x10000, 0x10);
//	sha256(RAM_BASE+0x10000, 0x10);
	Uart7_Init(115200);
	//	GPIO_PIN55_OEN = 0;
	//	SYS_GPIO56_MUX = 3;
	//	SYS_GPIO57_MUX = 3;
/*
	 union {
			UINT m;
	        struct {
	            unsigned int a : 2;
	            unsigned int b : 1;
	            unsigned int c : 7;
	            unsigned int d : 6;
	            unsigned int e : 16;

	        };
	    } u;


    u.a=1;
    u.b=2;
    u.c=3;
    u.d=4;
    u.e=5;

*/
 //   Uart1_Hex(u.m);



//   Uart1_Hex(v.m);

	UINT j;



//	test_calib();

	DdrInit(2);
//	DDR_PWR_REQ = 1;

	

#define EMPT_SRAM 0x80010388
#define DST_SRAM  0x81000388
#define SIZEOFCACHE 1225
	volatile uint* psrc = EMPT_SRAM;
	volatile uint* pdst = DST_SRAM;
	uint* src = psrc;
	uint* dst = pdst;
	uint size = SIZEOFCACHE;
uint i=0;
uint ret;
uint r=0;

#if 1
for(r=0;r<10000;r++){

	src = psrc;
	dst = pdst;

	_printf("############[Round:%d](src:%08x)(dst:%08x)(size:%d)###########\r\n",r,src,dst ,size);

	for(i=0;i<size/4;i++){
		dmwrite32(src++, i);DdrOffOn();
	}
	src = psrc;
	for(i=0;i<size/4;i++){
			if((ret=dmread32(src)) != i){
				_printf("[%d](%x)\r\n",i,psrc);
			}
			src++;
	}

	cdma_copy(dst,psrc,size);

	for(i=0;i<size/4;i++){
			if((ret=dmread32(dst)) != i){
				_printf("[%d](src:%08x)(dmadst:%08x)(Daddr:%08x)(Data:%08x)\r\n",i,psrc,pdst,dst,ret);
			}
		dst++;
	}

	size +=1 ;
//	psrc +=1 ;
//	pdst +=1 ;
	if(psrc > EMPT_SRAM + 0x1000) psrc = EMPT_SRAM;


	}
#else
//	 SYS_CPU_EN = 0xf;
	 volatile int a,b,c=0;
	 *mtime = 0; // timer init

//	 for(i=0;i<size/4;i++){
//	 		dmwrite32(src++, i);
//	 }
     src = 0x80000000;
     dst = 0x81000000;
	 size = 1024;
	 uint round=1;
	 uint total_size = 10*1024*1024;
	 uint size_shift=1;
	 uint idx=0;
	 while(size < 1024*1024){
		 idx++;
		 size = 1<<(size_shift++);
		 round=total_size/size;

		 *mtime = 0; // timer init
		 for(i=0;i<round;i++){
			 dma_copy(dst,psrc,size);
		 }

		 _printf("idx[%d]round %d size %d time %16lu\r\n",idx,round,size,*mtime);
	 }
#endif

	 while(1){
		 Comm();
		 sleep_(100000);
		 _printf("%16lu\n",*mtime);
	//	 a =  SYS_CPU_EN;

//		 a =  SYS_CPU_EN;
//		 SYS_CPU_EN = c;

	 }


//

}

void main_1(void)
{

	//	while(1);
//	while((SYS_CPU_EN & 0x2)!=0x2){
//		sleep_(1);
//	}
//	Uart1_Strn("CPU1");
	 volatile int a,b,c=0;
	 while(1){
		 _printf("b");
	//	 sleep_(1);
		 a =  SYS_CPU_EN;
		 SYS_CPU_EN = c;
	 }
}

void main_2(void)
{

//	while(1);
//	while((SYS_CPU_EN & 0x4)!=0x4){
//		sleep_(1);
//	}
//	Uart1_Strn("CPU2");
	 volatile int a,b,c=0;
	 while(1){
		 _printf("c");
	//	 sleep_(1);
		 a =  SYS_CPU_EN;

	//	 UART7_TX_DAT = c;
		 SYS_CPU_EN = c;

	 }
}

void main_3(void)
{

//	while(1);
//	while((SYS_CPU_EN & 0x8)!=0x8){
//		sleep_(1);
//	}
//	Uart1_Strn("CPU3");
 volatile int a,b,c=0;
	 while(1){
		 _printf("d");
		 //sleep_(1);
		 //__asm("C.NOP");

//

		 a =  SYS_CPU_EN;

//		 UART7_TX_DAT = c;

		 //sleep_(1);
		 //b =  UART7_TX_FULL;
	  SYS_CPU_EN = c;
	 }
}


