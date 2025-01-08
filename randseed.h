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

#ifndef RANDSEED_H
#define RANDSEED_H  1

#include <stdint.h>

#define RANDSEED_WORDS  16  /* 1024 bit */

typedef struct _randseed_t {
    uint64_t    w[RANDSEED_WORDS], sv[4], ev[4];
} randseed_t;

void rs_init( randseed_t* tgt );
void rs_copy( randseed_t* tgt, const randseed_t* src );
void rs_south( randseed_t* tgt );
void rs_east( randseed_t* tgt );
void rs_print( const randseed_t* src );

#endif

