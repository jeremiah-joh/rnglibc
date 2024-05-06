/*
 * Copyright (C) 2024 Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 * 
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "rng.h"
#include <stdio.h>

static size_t s[4] = { 0, 0, 0, 0 };

static size_t
rotl_64(const size_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

static size_t
prng_64()
{
	const size_t result = rotl_64(s[0] + s[3], 23) + s[0];

	const size_t t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;

	s[3] = rotl_64(s[3], 45);

	return result;
}

static size_t 
rotl_32(const size_t x, int k)
{
	return (x << k) | (x >> (32 - k));
}

size_t
prng_32()
{
	const size_t result = rotl_32(s[0] + s[3], 7) + s[0];

	const size_t t = s[1] << 9;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;

	s[3] = rotl_32(s[3], 11);

	return result;
}

size_t
prng()
{
	size_t i;
	if (!(s[0] | s[1] | s[2] | s[3]))
		for (i = 0; i < 4; i++)
			s[i] = osrng();

	if (sizeof(size_t) == 8)
		return prng_64();

	return prng_32();
}

size_t
osrng()
{
	FILE *fp;
	size_t r;

	if ((fp = fopen("/dev/random", "rb")) == NULL)
		return 0;
	if (fread(&r, 1, sizeof(r), fp) < sizeof(r))
		return 0;

	fclose(fp);

	return r;
}

