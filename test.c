#include "src/rng.h"
#include <stdio.h>

int
main()
{
	size_t i, r;

	puts("# prng()");
	for (i = 0; i < 8; i++)
		printf("%lu\n", prng());

	puts("# osrng()");
	for (i = 0; i < 8; i++)
		printf("%lu\n", osrng());

	puts("# prng_buf()");
	for (i = 0; i < 8; i++) {
		prng_buf(&r, sizeof(r));
		printf("%lu\n", r);
	}

	puts("# osrng_buf()");
	for (i = 0; i < 8; i++) {
		osrng_buf(&r, sizeof(r));
		printf("%lu\n", r);
	}

	return 0;
}
