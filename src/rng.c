/*
 * rnglibc - random number generators written in ANSI C
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

#define BUF_LEN 4
#define BITS (sizeof(size_t) * 8)
#define ROTL(x, k) (((x) << (k)) | ((x) >> (BITS - k)))

static int
os_random_buf(void *buf, size_t len)
{
	FILE *fp;

	if ((fp = fopen("/dev/random", "r")) == NULL)
		return -1;
	if (fread(buf, len, 1, fp) != 1)
		return -1;
	if (fclose(fp))
		return -1;

	return 0;
}

static size_t
prng_64(size_t buf[BUF_LEN])
{
	size_t res, tmp;

	res = ROTL(buf[0] + buf[3], 23) + buf[0];
	tmp = buf[1] << 17;

	buf[2] ^= buf[0];
	buf[3] ^= buf[1];
	buf[1] ^= buf[2];
	buf[0] ^= buf[3];

	buf[2] ^= tmp;

	buf[3] = ROTL(buf[3], 45);

	return res;
}

static size_t
prng_32(size_t buf[BUF_LEN])
{
	size_t res, tmp;

	res = ROTL(buf[0] + buf[3], 7) + buf[0];
	tmp = buf[1] << 9;

	buf[2] ^= buf[0];
	buf[3] ^= buf[1];
	buf[1] ^= buf[2];
	buf[0] ^= buf[3];

	buf[2] ^= tmp;

	buf[3] = ROTL(buf[3], 11);

	return res;
}

size_t
pseudo_random(void)
{
	static size_t buf[BUF_LEN] = { 0, 0, 0, 0 };

	if ((buf[0] | buf[1] | buf[2] | buf[3]) == 0)
		if (os_random_buf(buf, sizeof(buf)))
			return 0;

	/* compiler will optimize this code */
	if (sizeof(size_t) == 8)
		return prng_64(buf);
	if (sizeof(size_t) == 4)
		return prng_32(buf);

	/* unreachable unless the CPU is neither 32 nor 64 bit */
	return 0;
}

size_t
os_random(void)
{
	size_t r;

	if (os_random_buf(&r, sizeof(r)))
		return 0;

	return r;
}
