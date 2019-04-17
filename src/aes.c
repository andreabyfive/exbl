#include "en675.h"
#include "reg.h"
#include "aes.h"

void aes_init()
{
	AES_KEY_255_224 =0x12345678;
	AES_KEY_223_192 =0x12345678;
	AES_KEY_191_160 =0x12345678;
	AES_KEY_159_128 =0x12345678;
	AES_KEY_127_96  =0x12345678;
	AES_KEY_95_64   =0x12345678;
	AES_KEY_63_32   =0x12345678;
	AES_KEY_31_0    =0x12345678;
	AES_CBC_EN		=1;
}


void aes128_enc(unsigned int src, unsigned int dst, unsigned int len)
{
	AES_SRC = src;
	AES_DST = dst;
	AES_LEN = len;
	AES_IRQ_EN = 1;
	AES_KEY_LEN = 0;
	AES_MODE = 1;
	AES_REQ = 1;
	while(AES_REQ);
}
void aes128_dec(unsigned int src, unsigned int dst, unsigned int len)
{
	AES_SRC = src;
	AES_DST = dst;
	AES_LEN = len;
	AES_IRQ_EN = 1;
	AES_KEY_LEN = 0;
	AES_MODE = 0;
	AES_REQ = 1;
	while(AES_REQ);
}
void aes256_enc(unsigned int src, unsigned int dst, unsigned int len)
{
	AES_SRC = src;
	AES_DST = dst;
	AES_LEN = len;
	AES_IRQ_EN = 1;
	AES_KEY_LEN = 1;
	AES_MODE = 1;
	AES_REQ = 1;
	while(AES_REQ);
}
void aes256_dec(unsigned int src, unsigned int dst, unsigned int len)
{
	AES_SRC = src;
	AES_DST = dst;
	AES_LEN = len;
	AES_IRQ_EN = 1;
	AES_KEY_LEN = 1;
	AES_MODE = 0;
	AES_REQ = 1;
	while(AES_REQ);
}
