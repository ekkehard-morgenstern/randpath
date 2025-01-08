/*
*   RANDPATH - Random path generator
*   Copyright (C) 1998, 2025  Ekkehard Morgenstern
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
*   CONTACT INFO:
*       E-Mail: ekkehard@ekkehardmorgenstern.de
*       Mail: Ekkehard Morgenstern, Mozartstr. 1, D-76744 Woerth am Rhein,
*             Germany, Europe
*/

#include "randseed.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

static FILE* seed_fp = 0;

void rs_init( randseed_t* tgt ) {
    if ( seed_fp == 0 ) {
        seed_fp = fopen( "/dev/urandom", "rb" );
        if ( seed_fp == 0 ) {
            fprintf( stderr, "? failed to open '/dev/urandom': %m\n" );
            exit( EXIT_FAILURE );
        }
    }
    if ( fread( tgt->w, sizeof(uint64_t), RANDSEED_WORDS, seed_fp ) 
        != RANDSEED_WORDS ) {
        fprintf( stderr, "? I/O error on '/dev/urandom'\n" );
        exit( EXIT_FAILURE );
    }
    tgt->sv[0] = UINT64_C(0xbb8dd8182615ddf3);
    tgt->sv[1] = UINT64_C(0x38d35226195ddb49);
    tgt->sv[2] = UINT64_C(0xadeb4f5fc2fe50ee);
    tgt->sv[3] = UINT64_C(0x096ed738a88b61c8);
    tgt->ev[0] = UINT64_C(0xe8497fc974fed9ea);
    tgt->ev[1] = UINT64_C(0x973672f11a2ddd91);
    tgt->ev[2] = UINT64_C(0xc19950208bc3a7cf);
    tgt->ev[3] = UINT64_C(0xd378563e9631242d);
}

void rs_copy( randseed_t* tgt, const randseed_t* src ) {
    memcpy( tgt->w, src->w, sizeof(uint64_t) * RANDSEED_WORDS );
    memcpy( tgt->sv, src->sv, sizeof(uint64_t) * 4 );
    memcpy( tgt->ev, src->ev, sizeof(uint64_t) * 4 );
}

void rs_south( randseed_t* tgt ) {
    uint64_t v1 = tgt->sv[0];
    uint64_t v2 = tgt->sv[1];
    uint64_t v3 = tgt->sv[2];
    uint64_t v4 = tgt->sv[3];
    for ( int i=0; i < RANDSEED_WORDS; ++i ) {
        v1 = ( ( v2 + tgt->w[i] ) ^ v3 );
        v2 = ( ( v3 ^ v4 ) - v2 );
        v3 = ( ( v4 - v3 ) ^ v1 );
        v4 = ( ( v2 ^ v1 ) + v3 );
        tgt->w[i] = v1;
    }
    tgt->sv[0] = v1;
    tgt->sv[1] = v2;
    tgt->sv[2] = v3;
    tgt->sv[3] = v4;
}

void rs_east( randseed_t* tgt ) {
    uint64_t v1 = tgt->ev[0];
    uint64_t v2 = tgt->ev[1];
    uint64_t v3 = tgt->ev[2];
    uint64_t v4 = tgt->ev[3];
    for ( int i=0; i < RANDSEED_WORDS; ++i ) {
        v1 = ( ( v2 ^ tgt->w[i] ) - v3 );
        v2 = ( ( v3 + v4 ) ^ v2 );
        v3 = ( ( v4 + v3 ) - v1 );
        v4 = ( ( v2 ^ v1 ) + v3 );
        tgt->w[i] = v1;
    }
    tgt->ev[0] = v1;
    tgt->ev[1] = v2;
    tgt->ev[2] = v3;
    tgt->ev[3] = v4;
}

void rs_print( const randseed_t* src ) {
    for ( int i=0; i < RANDSEED_WORDS; ++i ) {
        printf( "%08" PRIX64, src->w[i] );
    }
}

