#include "en675.h"
#include "reg.h"

void sha224(UINT * src, UINT * len)
{
	SHA_SRC = src;
	SHA_LEN = len;
	SHA_IRQ_EN = 1;
	SHA_MODE = 0;
	SHA_REQ = 1;
	while(SHA_REQ);
}
void sha256(UINT * src, UINT * len)
{
	SHA_SRC = src;
	SHA_LEN = len;
	SHA_IRQ_EN = 1;
	SHA_MODE = 1;
	SHA_REQ = 1;
	while(SHA_REQ);
}