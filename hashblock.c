// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include "sph_groestl.h"

void HashGroestl(void * buf, const void * pbegin, int len)
{
    sph_groestl512_context  ctx_gr[2];
    static unsigned char pblank[1];
    char hash[64];
	char hash2[64];
	
    sph_groestl512_init(&ctx_gr[0]);
    sph_groestl512 (&ctx_gr[0], (len <= 0 ? pblank : (unsigned char*)pbegin), len);
    sph_groestl512_close(&ctx_gr[0], hash);
	
	sph_groestl512_init(&ctx_gr[1]);
	sph_groestl512(&ctx_gr[1],hash,64);
	sph_groestl512_close(&ctx_gr[1],hash2);
	
	for (unsigned int i = 0; i < 32; i++){
        ((char*)buf)[i] = hash2[i];
    }
	
}

