CC = cc
CFLAGS = -ansi -Wall -Wextra -Wpedantic -Werror

all: test

test:
	$(CC) $(CFLAGS) -o rng src/rng.c -D_TEST -g

clean:
	rm -f rng
