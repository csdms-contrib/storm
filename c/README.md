# storm.c

This is a "faithful" C translation
of the original Fortran 77 version of **storm**.
Some variable names have been changed,
but the flow of the original program
is preserved.

To make the outputs from this version
match those of the Fortran version:

1. the location indices of the storm center have been decremented by
   one;
1. the write order of the `wdir`, `windx` and `windy` variables have
   been transposed.

Compile and run this program with a sample input file:

	$ make
	$ cp ../testing/data/wind.in .
	$ ./storm
