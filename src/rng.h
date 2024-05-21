/*   
 * rnglibc - useful random number generators written in ANSI C
 * 
 * Written in 2024 by Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 * 
 * To the extent possible under law, the author(s) have dedicated all
 * copyright and related and neighboring rights to this software to the
 * public domain worldwide. This software is distributed without any warranty.
 * 
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software.
 * If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
 */

#include "rng.h"
#include <stddef.h>

/* general purpose pseudo-random number generator */
size_t	prng();
/* random number generator from operating system */
size_t	osrng();
/* fill buffer with pseudo-random number generator */
int	prng_buf(void *, const size_t);
/* fill buffer with random number generator from operating system */
int	osrng_buf(void *, const size_t);

