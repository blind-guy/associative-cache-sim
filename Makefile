CC=gcc
DEPS = driver.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cachesimulation: driver.o
	gcc -lm -o driver driver.o -I.
