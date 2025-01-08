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

#include <png.h>

int main( int argc, char** argv ) {

    randseed_t rs;
    rs_init( &rs );

    printf( "seed: " ); rs_print( &rs ); printf( "\n" );

    randseed_t path_s, path_e;
    rs_copy( &path_s, &rs );
    rs_copy( &path_e, &rs );

    png_structp png_ptr_s = 0, png_ptr_e = 0;
    png_infop   info_ptr_s = 0, info_ptr_e = 0;
    png_colorp  palette_s = 0, palette_e = 0;

    FILE        *fp_s = 0, *fp_e = 0;

#define OUTFILE_S   "test2_randseed_image_s.png"
#define OUTFILE_E   "test2_randseed_image_e.png"

    fp_s = fopen( OUTFILE_S, "wb" );
    if ( fp_s == 0 ) {
        fprintf( stderr, "failed to create file '" OUTFILE_S "': %m\n" );
ERR1:   exit( EXIT_FAILURE );
    }

    fp_e = fopen( OUTFILE_E, "wb" );
    if ( fp_e == 0 ) {
        fprintf( stderr, "failed to create file '" OUTFILE_E "': %m\n" );
ERR2:   fclose( fp_s ); 
        remove( OUTFILE_S );
        goto ERR1;
    }

    png_ptr_s = png_create_write_struct( PNG_LIBPNG_VER_STRING, 0, 0, 0 );
    if ( png_ptr_s == 0 ) {
        fprintf( stderr, "failed to create write struct s\n" );
ERR3:   fclose( fp_e );
        remove( OUTFILE_E );
        goto ERR2;
    }

    png_ptr_e = png_create_write_struct( PNG_LIBPNG_VER_STRING, 0, 0, 0 );
    if ( png_ptr_e == 0 ) {
        fprintf( stderr, "failed to create write struct e\n" );
ERR4:   png_destroy_write_struct( &png_ptr_s, info_ptr_s ? &info_ptr_s : 0 );
        goto ERR3;
    }

    info_ptr_s = png_create_info_struct( png_ptr_s );
    if ( info_ptr_s == 0 ) {
        fprintf( stderr, "failed to create info struct s\n" );
ERR5:   png_destroy_write_struct( &png_ptr_e, info_ptr_e ? &info_ptr_e : 0 );
        goto ERR4;
    }

    info_ptr_e = png_create_info_struct( png_ptr_e );
    if ( info_ptr_e == 0 ) {
        fprintf( stderr, "failed to create info struct e\n" );
        goto ERR5;
    }

    if ( setjmp( png_jmpbuf( png_ptr_s ) ) != 0 ) {
        goto ERR5;
    }
    if ( setjmp( png_jmpbuf( png_ptr_e ) ) != 0 ) {
        goto ERR5;
    }

    png_init_io( png_ptr_s, fp_s );
    png_init_io( png_ptr_e, fp_e );

    png_set_IHDR( png_ptr_s, info_ptr_s, 1024, 1024, 1, PNG_COLOR_TYPE_PALETTE,
        PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE );
    png_set_IHDR( png_ptr_e, info_ptr_e, 1024, 1024, 1, PNG_COLOR_TYPE_PALETTE,
        PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE );

    palette_s = (png_colorp) png_malloc( png_ptr_s, 2 * sizeof(png_color) );
    palette_e = (png_colorp) png_malloc( png_ptr_e, 2 * sizeof(png_color) );

    palette_s[0].red = 0; palette_s[0].green = 0; palette_s[0].blue = 0;
    palette_e[0].red = 0; palette_e[0].green = 0; palette_e[0].blue = 0;
    palette_s[1].red = 255; palette_s[1].green = 255; palette_s[1].blue = 255;
    palette_e[1].red = 255; palette_e[1].green = 255; palette_e[1].blue = 255;

    png_set_PLTE( png_ptr_s, info_ptr_s, palette_s, 2 );
    png_set_PLTE( png_ptr_e, info_ptr_e, palette_e, 2 );

    png_write_info( png_ptr_s, info_ptr_s );
    png_write_info( png_ptr_e, info_ptr_e );

    for ( int y=0; y < 1024; ++y ) {

        rs_south( &path_s );
        rs_east( &path_e );

        png_bytep row_s = (png_bytep)(&path_s.w[0]);
        png_bytep row_e = (png_bytep)(&path_e.w[0]);

        png_write_rows( png_ptr_s, &row_s, 1 );
        png_write_rows( png_ptr_e, &row_e, 1 );
    }

    png_write_end( png_ptr_s, info_ptr_s );
    png_write_end( png_ptr_e, info_ptr_e );

    png_free( png_ptr_s, palette_s ); palette_s = 0;
    png_free( png_ptr_e, palette_e ); palette_e = 0;

    png_destroy_write_struct( &png_ptr_s, &info_ptr_s );
    png_destroy_write_struct( &png_ptr_e, &info_ptr_e );

    fclose( fp_s );
    fclose( fp_e );

    return EXIT_SUCCESS;
}
