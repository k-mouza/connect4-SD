CC = gcc
CFLAGS = -O3

TESTDIR = testing/
INCDIR = include/
SOURCEDIR = src/

OBJ = $(SOURCEDIR)connect4.o $(SOURCEDIR)ai_player.o $(SOURCEDIR)output.o $(SOURCEDIR)gameplay.o $(SOURCEDIR)input.o
EXEC = connect4

MFLAGS = -w

all: exec tests

exec: $(OBJ) Makefile
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)
	
%.c: %.h
	
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
tests:
	cd $(TESTDIR) && $(MAKE) $(MFLAGS)
	
clean:
	rm -rf $(OBJ) $(EXEC)
	cd $(TESTDIR) && $(MAKE) $(MFLAGS) clean