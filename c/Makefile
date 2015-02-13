# Makefile for C version of `storm`.
# Mark Piper (mark.piper@colorado.edu)

CC = gcc
CFLAGS = -c
LFLAGS =

PROG = storm
CLEAN = *.o *~
CLEANER = $(PROG) *.data *.in

all: $(PROG)

storm: storm.o

%: %.o
	$(CC) $(LFLAGS) $^ -o $@ -lm
	@date

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(CLEAN)

cleaner:
	rm -f $(CLEAN) $(CLEANER)
