CC=gcc
DEPS = driver.h cache.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cachesimulation: driver.o cache.o
	gcc -lm -o driver driver.o cache.o -I.
