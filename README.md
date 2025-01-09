# randpath
Two-dimensional 1024 bit pseudo random number generator

## Synopsis

This project provides two-dimensional 1024 bit pseudo random number generator.
It can start out with a random number pulled from "/dev/urandom", and then progress in two directions (south and east). On each move, a modified random number is generated.
If you use the same seed, you will always get the same (i.e. reproducible) results from moving south/east.

For an example of the quality of the pseudo random number generator, see enclosed PNGs created with the test2 program:

### South test2 example image

1024 calls of rs_south() from common seed.

![south image](test2_randseed_image_s.png)

### East test2 example image

1024 calls of rs_east() from common seed.

![east image](test2_randseed_image_e.png)

## Usage

TBD, see test programs.
