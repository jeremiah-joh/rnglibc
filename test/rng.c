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
#include "../src/rng.h"
#include <stdio.h>

int
main()
{
	int i;

	for (i = 1; i <= 8; i++)
		printf("%d. os_random():     %#.16lx\n", i, os_random());
	for (i = 1; i <= 8; i++)
		printf("%d. pseudo_random(): %#.16lx\n", i, pseudo_random());

	return 0;
}
