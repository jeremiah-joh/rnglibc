/*
 * rnglibc - useful random number generators written in ANSI C
 *
 * Written in 2024 by Woohyun Joh <jeremiahjoh@sungkyul.ac.kr>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software.
 */

#include "rng.h"
#include <stdio.h>
#include <string.h>

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

static size_t
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
	/* initialize buffer if numbers in s are all zero */
	if ((s[0] | s[1] | s[2] | s[3]) == 0)
		if (osrng_buf(s, sizeof(s)))
			return 0;

	/* compiler will optimize this code */
	if (sizeof(size_t) == 8)
		return prng_64();
	if (sizeof(size_t) == 4)
		return prng_32();

	/* unreachable unless the CPU is neither 32 nor 64 bit */
	return 0;
}

size_t
osrng()
{
	size_t r;
	return osrng_buf(&r, sizeof(r)) ? 0 : r;
}

int
prng_buf(void *buf, const size_t len)
{
	size_t i, r;

	for (i = 0, r = prng(); i < len / sizeof(r); i++, r = prng())
		memcpy((size_t *)buf + i, &r, sizeof(r));

	memcpy((size_t *)buf + i, &r, len % sizeof(r));

	return 0;
}

int
osrng_buf(void *buf, const size_t len)
{
	FILE *fp;

	if ((fp = fopen("/dev/random", "rb")) == NULL)
		return -1;
	if (fread(buf, 1, len, fp) < len)
		return -1;

	fclose(fp);

	return 0;
}

#ifdef _TEST

int
main()
{
	size_t arr[2];

	printf("osrng     %lu\n", osrng());
	printf("prng      %lu\n", prng());

	osrng_buf(&arr, sizeof(arr));
	printf("osrng_buf %lu, %lu\n", arr[0], arr[1]);

	arr[0] = arr[1] = 0;

	prng_buf(&arr, sizeof(arr));
	printf("prng_buf  %lu, %lu\n", arr[0], arr[1]);

	return 0;
}

#endif
