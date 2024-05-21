CC = cc
CFLAGS = -ansi -Wall

test:
	$(CC) $(CFLAGS) src/rng.c test.c -g
	./a.out
clean:
	rm -f ./a.out
