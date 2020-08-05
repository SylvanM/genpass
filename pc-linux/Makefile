# the compiler: gcc for C program. define as g++ for C++
CC = gcc

CFLAGS = -Wall

all: genpass

# To create the executable file we need the object files
genpass: clean
	$(CC) $(CFLAGS) -o genpass main.c genpass.c utility.c ../drng/drng.c

clean:
	$(RM) genpass *.o *~
