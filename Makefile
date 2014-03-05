CC = gcc
CFLAGS = -O3

OBJ = connect4.o ai_player.o output.o gameplay.o
EXEC = connect4

all: exec

exec: $(OBJ) Makefile
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)
	
%.c: %.h
	
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
clean:
	rm -rf $(OBJ) $(EXEC)