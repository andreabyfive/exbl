#include "en675.h"
#include "reg.h"

void sfls_init()
{
	while(!SFLS_SFLS_ID_VAL);
	SFLS_USR_CMD = 0x38;
	SFLS_BUS_CMD_RD		= 0xEB;
	SFLS_BUS_CMD_WR		= 0x02;
	SFLS_BUS_CMD_WREN	= 0x06;
	SFLS_BUS_CMD_RDREG	= 0x05;
	SFLS_BUS_RD_CMD_MODE = 2;
	SFLS_BUS_RD_ADR_MODE = 2;
	SFLS_BUS_RD_DAT_MODE = 2;
	SFLS_BUS_WR_CMD_MODE = 2;
	SFLS_BUS_WR_ADR_MODE = 2;
	SFLS_BUS_WR_DAT_MODE = 2;
	SFLS_BUS_WREN_CMD_MODE = 2;
	SFLS_BUS_RDREG_CMD_MODE = 2;
	SFLS_BUS_RDREG_DAT_MODE = 2;
	SFLS_BUS_GAP_EN = 1;
	SFLS_BUS_GAP = 6;
	SFLS_IO_CLKDIV = 0;
	SFLS_IO_RDLTC = 1;
	SFLS_USRBUS_REQ = 1;
	while(SFLS_BUS_REQ);
}
