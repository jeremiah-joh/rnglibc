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
 * If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
 */

#include "rng.h"
#include <stdio.h>
#include <limits.h>

#define BUF_LEN 4
#define BITS (sizeof(long) * 8)
#define ROTL(x, k) (((x) << (k)) | ((x) >> (BITS - k)))

#if LONG_MAX == 0x7fffffffffffffff
#define RO1 23
#define SHL 17
#define RO2 45
#elif LONG_MAX == 0x7fffffff
#define RO1 7
#define SHL 9
#define RO2 11
#else
#error "size of type 'long' is too small"
#endif

int
random_buf(void *buf, const size_t len)
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

long
random_int(void)
{
	static unsigned long buf[BUF_LEN] = { 0, 0, 0, 0 };
	long res, tmp;

	if ((buf[0] | buf[1] | buf[2] | buf[3]) == 0)
		if (random_buf(buf, sizeof(buf)))
			return -1;

	res = ROTL(buf[0] + buf[3], RO1) + buf[0];
	tmp = buf[1] << SHL;

	buf[2] ^= buf[0];
	buf[3] ^= buf[1];
	buf[1] ^= buf[2];
	buf[0] ^= buf[3];

	buf[2] ^= tmp;
	buf[3] = ROTL(buf[3], RO2);

	return (res < 0) ? -res : res;
}

double
random_flt(void)
{
	static unsigned long buf[BUF_LEN] = { 0, 0, 0, 0 };
	union { unsigned long i; double f; } res;
	unsigned long tmp;

	if ((buf[0] | buf[1] | buf[2] | buf[3]) == 0)
		if (random_buf(buf, sizeof(buf)))
			return -1.0;

	res.i = buf[0] + buf[3];
	tmp = buf[1] << SHL;

	buf[2] ^= buf[0];
	buf[3] ^= buf[1];
	buf[1] ^= buf[2];
	buf[0] ^= buf[3];

	buf[2] ^= tmp;
	buf[3] = ROTL(buf[3], RO2);

	return (res.f < 0) ? -res.f : res.f;
}
