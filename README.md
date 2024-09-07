Random Number Generator Library for C
=====================================

Random number generators written in ANSI C.

pseudo_random
-------------

`size_t pseudo_random()`

Returns pseudo-random number from 1 to maximum number of `size_t`. This
function is guaranteed to not return 0 unless the processor is neither 64 nor
32 bit.

note: This function uses the xoshiro128++ algorithm when `size_t` is 4 bytes
long, and the xoshiro256++ algorithm when `size_t` is 8 bytes long.

os_random
---------

`size_t os_random()`

Returns random number from operating system from 1 to maximum number of
`size_t`. This function is guaranteed to not return 0 unless the `/dev/random`
is not available.

note: This function reads random bytes in `/dev/random` file.

License
-------

rnglibc by Woohyun Joh is marked with CC0 1.0
