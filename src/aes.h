#ifndef AES_H_
#define AES_H_
#include "en675.h"
void aes_init(void);
void aes128_enc(UINT src, UINT dst, UINT len);
void aes128_dec(UINT src, UINT dst, UINT len);
void aes256_enc(UINT src, UINT dst, UINT len);
void aes256_dec(UINT src, UINT dst, UINT len);

#endif /*AES_H_ */
