CC = gcc
CFLAGS = -Wall

all: $(warning must make to 'proc' or 'thread')

proc: searchtest.c multitest_proc.o
	$(CC) $(CFLAGS) multitest_proc.o searchtest.c -o searchtest -lm

thread: searchtest.c multitest_thread.o
	$(CC) $(CFLAGS) multitest_thread.o searchtest.c -o searchtest -lm -lpthread

multitest_proc.o: multitest_proc.c multitest.h
	$(CC) $(CFLAGS) multitest_proc.c -c

multitest_thread.o: multitest_thread.c multitest.h
	$(CC) $(CFLAGS) multitest_thread.c -c

clean:
	rm -f searchtest multitest_thread.o multitest_proc.o

