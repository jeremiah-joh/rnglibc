Random Number Generator Library for C
=====================================

Random number generators written in ANSI C.

pseudo_random
-------------

`long pseudo_random(void)`

Returns a pseudo-random long integer in the range LONG_MIN to LONG_MAX.

This function uses xoshiro256++ or xorshiro128++ depends on size of `long`.

os_random
---------

`long os_random(void)`

Returns a OS-generated random long integer in the range LONG_MIN to LONG_MAX.

This function reads bytes from `/dev/random`.

License
-------

rnglibc by Woohyun Joh is marked with CC0 1.0
