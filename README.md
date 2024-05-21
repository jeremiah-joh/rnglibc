Random Number Generator Library for C
=====================================

Useful RNGs written in ANSI C.

Pseudo random number generator
------------------------------

`size_t prng()` and `int prng_buf(void *, const size_t)`.

These functions use xoshiro128++ on 32 bit processor, xoshiro256++ on 64 bit.
They initialize themselves by using `osrng_buf()` when all the numbers in
state are zero.

Operating system's random number generator
------------------------------------------

`size_t osrng()` and `int osrng_buf(void *, const size_t)`.

These functions use '/dev/random' file of operating system.

