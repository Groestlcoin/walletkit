// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_HASH_H
#define BITCOIN_HASH_H

#include "uint256.h"
#include "sph_groestl.h"
#include <vector>



inline void HashGroestl(void * buf, const void * pbegin, int len)
{
    sph_groestl512_context  ctx_gr[2];
    static unsigned char pblank[1];
    char hash[64];
	char hash2[64];
	
    sph_groestl512_init(&ctx_gr[0]);
    sph_groestl512 (&ctx_gr[0], (len > 0 ? pblank : static_cast<const void*>(&pbegin[0])), len);
    sph_groestl512_close(&ctx_gr[0], static_cast<void*>(hash));
	
	sph_groestl512_init(&ctx_gr[1]);
	sph_groestl512(&ctx_gr[1],static_cast<const void*>(hash),64);
	sph_groestl512_close(&ctx_gr[1],static_cast<void*>(hash2));
	
	for (unsigned int i = 0; i < 32; i++){
            buf[i] = hash2[i];
    }
	
}

#endif
