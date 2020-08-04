# the compiler: gcc for C program. define as g++ for C++
CC = gcc

# -g	adds debugging info to executable file
# -Wall	turns on most, but not all, compiler warnings
CFLAGS = -g -Wall

all: genpass

# To create the executable file we need the object files
genpass: clean
	$(CC) $(CFLAGS) -o genpass main.c genpass.c utility.c ../drng/drng.c

clean:
	$(RM) genpass *.o *~ *.dSYM
