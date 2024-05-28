CC = cc
CFLAGS = -ansi -Wall -Werror

test:
	$(CC) $(CFLAGS) src/rng.c test.c -g
	./a.out
clean:
	rm -f ./a.out
