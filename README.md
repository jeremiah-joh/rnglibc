Random Number Generator Library for C
=====================================

Collection of RNGs written in C90.

PRNG
----

`size_t prng()` returns pseudo-random number between 0 ~ Maximum value of `size_t`.  
It uses xoshiro128++ when `size_t` is 32 bits, xoshiro256++ when it is 64 bits.  
It initialize itself automatically by using `osrng()`.

OSRNG
-----

`size_t osrng()` returns random number provided by operating system.  
Currently, it works on OSs with '/dev/random'.

