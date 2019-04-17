/*
 * boot.c
 *
 *  Created on: 2018. 11. 29.
 *      Author: BYOH
 */
#include <stdint.h>
#include <string.h>
#include "en675.h"
#include "boot.h"
#include "dma.h"

const unsigned int _bss_s;
const unsigned int _bss_e;

void _init_bss_section(void)
{
	UINT pDst = (UINT)(intptr_t)(_bss_s);
	if( pDst == 0) return;
	UINT n = _bss_e - _bss_s;
	dma_set(pDst, n, 0);
	return;
}

const unsigned int _data_s;
const unsigned int _data_e;
const unsigned int _data_lma_s;

void _init_data_section(void)
{
	dma_copy((UINT)_data_s, (UINT)_data_lma_s, (UINT)(_data_e - _data_s));
}
