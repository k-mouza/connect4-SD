CC = gcc
CFLAGS = -O3

SOURCEDIR = ../src/
INCDIR = ../include
OBJDIR = $(SOURCEDIR)

TESTBIN = test-all

TESTOBJ = test-all.o
OBJS = $(TESTOBJ) $(OBJDIR)ai_player.o $(OBJDIR)output.o $(OBJDIR)gameplay.o

LIBS = -lcunit -lm

testbin: $(OBJS) Makefile
	$(CC) $(CFLAGS) -o $(TESTBIN) $(OBJS) $(LIBS)

$(SOURCEDIR)%.c: $(INCDIR)%.h

%.o: $(SOURCEDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $< 

clean:
	rm -rf $(TESTOBJ) $(TESTBIN)