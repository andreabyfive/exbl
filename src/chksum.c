#include "en675.h"
#include "reg.h"
#include "chksum.h"

WORD chksum16(UINT src, UINT len)
{
	CHKSUM_ADR = src;
	CHKSUM_LEN = len;
	CHKSUM_GO = 1;
	while(CHKSUM_GO);
	return (WORD) CHKSUM_DAT;
}
