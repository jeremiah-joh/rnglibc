#include "rng.h"
#include <stdio.h>

int
main()
{
	size_t i;

	puts("# prng");
	for (i = 0; i < 10; i++)
		printf("%lu\n", prng());

	puts("# osrng");
	for (i = 0; i < 10; i++)
		printf("%lu\n", osrng());

	return 0;
}
