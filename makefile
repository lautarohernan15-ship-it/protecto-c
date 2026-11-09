CC     = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic

artemis4: main.c artemis.c artemis.h
	$(CC) $(CFLAGS) main.c artemis.c -o artemis4

clean:
	rm -f artemis4 artemis4.exe
