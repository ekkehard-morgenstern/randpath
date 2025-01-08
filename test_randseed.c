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

#include "randseed.c"
#include <stdlib.h>

int main( int argc, char** argv ) {

    randseed_t rs;
    rs_init( &rs );

    printf( "seed: " ); rs_print( &rs ); printf( "\n" );

    randseed_t path_s, path_e;
    rs_copy( &path_s, &rs );
    rs_copy( &path_e, &rs );

    for (;;) {
        printf( "--------------\n" );
        rs_south( &path_s );
        rs_east( &path_e );
        printf( "south: " ); rs_print( &path_s ); printf( "\n" );
        printf( "east : " ); rs_print( &path_e ); printf( "\n" );
    }

    return EXIT_SUCCESS;
}
