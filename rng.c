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
	if (!s[0] && !s[2] && !s[2] && !s[3])
		return osrng();
	if (sizeof(size_t) == 8)
		return prng_64();
	return prng_32();
}

size_t
osrng()
{
	FILE *fp;

	if ((fp = fopen("/dev/random", "rb")) == NULL)
		return 0;
	if (fread(s, sizeof(*s), sizeof(s), fp) < sizeof(s))
		return 0;

	fclose(fp);

	return s[0] ^ s[1] ^ s[2] ^ s[3];
}

