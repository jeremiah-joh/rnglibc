Random Number Generator Library for C
=====================================

Random number generators written in ANSI C.

`int random_buf(void *buf, const size_t len)`
---------------------------------------------

Fills `buf` of size `len` with `/dev/random`.
Returns 0 on success, -1 on failure.

`long random_int(void)`
-----------------------

Returns random integer between 0 and LONG_MAX on success, -1 on failure.

`double random_int(void)`
-------------------------

Returns random floating point number greater than 0.0 on success,
-1.0 on failure.

License
-------

rnglibc by Woohyun Joh is marked with CC0 1.0
