CC=gcc
DEPS = driver.h cache.h set.h block.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cachesimulation: driver.o cache.o set.o
	gcc -lm -o driver driver.o cache.o set.o -I.
