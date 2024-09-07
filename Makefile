CC = cc
CFLAGS = -ansi -Wall -Wextra -Wpedantic -Werror

all: rng

rng:
	$(CC) $(CFLAGS) -o rng test/rng.c src/rng.c -g

clean:
	rm -f rng
