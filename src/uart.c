#include "en675.h"
#include "reg.h"

void Uart0_Init(unsigned int BaudRate){UART0_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart0_Tx(char data){while(UART0_TX_FULL);UART0_TX_DAT = data;}
int Uart0_Rx(void){if(UART0_RX_EMPTY) return -1; else return (int)(UART0_RX_DAT & 0xff);}
void Uart0_Irq(void){}

void Uart1_Init(unsigned int BaudRate){UART1_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart1_Tx(char data){while(UART1_TX_FULL);UART1_TX_DAT = data;}
int Uart1_Rx(void){if(UART1_RX_EMPTY) return -1; else return (int)(UART1_RX_DAT & 0xff);}
void Uart1_Irq(void){}

void Uart2_Init(unsigned int BaudRate){UART2_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart2_Tx(char data){while(UART2_TX_FULL);UART2_TX_DAT = data;}
int Uart2_Rx(void){if(UART2_RX_EMPTY) return -1; else return (int)(UART2_RX_DAT & 0xff);}
void Uart2_Irq(void){}

void Uart3_Init(unsigned int BaudRate){UART3_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart3_Tx(char data){while(UART3_TX_FULL);UART3_TX_DAT = data;}
int Uart3_Rx(void){if(UART3_RX_EMPTY) return -1; else return (int)(UART3_RX_DAT & 0xff);}
void Uart3_Irq(void){}

void Uart4_Init(unsigned int BaudRate){UART4_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart4_Tx(char data){while(UART4_TX_FULL);UART4_TX_DAT = data;}
int Uart4_Rx(void){if(UART4_RX_EMPTY) return -1; else return (int)(UART4_RX_DAT & 0xff);}
void Uart4_Irq(void){}

void Uart5_Init(unsigned int BaudRate){UART5_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart5_Tx(char data){while(UART5_TX_FULL);UART5_TX_DAT = data;}
int Uart5_Rx(void){if(UART5_RX_EMPTY) return -1; else return (int)(UART5_RX_DAT & 0xff);}
void Uart5_Irq(void){}

void Uart6_Init(unsigned int BaudRate){UART6_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart6_Tx(char data){while(UART6_TX_FULL);UART6_TX_DAT = data;}
int Uart6_Rx(void){if(UART6_RX_EMPTY) return -1; else return (int)(UART6_RX_DAT & 0xff);}
void Uart6_Irq(void){}

void Uart7_Init(unsigned int BaudRate)
{
	SYS_GPIO56_MUX = 3;	//	UART7
	SYS_GPIO57_MUX = 3;	//	UART7
	UART7_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;
}
void Uart7_Tx(char data){while(UART7_TX_FULL);UART7_TX_DAT = data;}
int Uart7_Rx(void){if(UART7_RX_EMPTY) return -1; else return (int)(UART7_RX_DAT & 0xff);}
void Uart7_Irq(void){}

void Uart8_Init(unsigned int BaudRate){UART8_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart8_Tx(char data){while(UART8_TX_FULL);UART8_TX_DAT = data;}
int Uart8_Rx(void){if(UART8_RX_EMPTY) return -1; else return (int)(UART8_RX_DAT & 0xff);}
void Uart8_Irq(void){}
