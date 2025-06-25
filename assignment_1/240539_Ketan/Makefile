CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

TARGET = btree_app

all: $(TARGET)

$(TARGET): main.o btree.o myutils.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o btree.o myutils.o

main.o: main.c btree.h myutils.h
	$(CC) $(CFLAGS) -c main.c

btree.o: btree.c btree.h myutils.h
	$(CC) $(CFLAGS) -c btree.c

myutils.o: myutils.c myutils.h
	$(CC) $(CFLAGS) -c myutils.c

clean:
	rm -f *.o $(TARGET)

run: all
	./$(TARGET)
