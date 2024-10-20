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

#include "../src/rng.h"
#include <stdio.h>

int
main()
{
	int i;

	for (i = 0; i < 16; i++)
		printf("%ld\n", random_int());
	for (i = 0; i < 16; i++)
		printf("%g\n", random_flt());

	return 0;
}
