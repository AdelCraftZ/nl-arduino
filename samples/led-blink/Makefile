IDIR=include

CC=gcc
CFLAGS=-I$(IDIR)

ODIR=build

build/%.o: src/%.c include/%h
	$(CC) $(CFLAGS) -c $< -o build/$*.o

.PHONY: clean

clean:
	rm -rf build/*