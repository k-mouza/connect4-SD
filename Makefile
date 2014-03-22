CC = gcc
CFLAGS = -O3

TESTDIR = testing/

OBJ = connect4.o ai_player.o output.o gameplay.o input.o
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