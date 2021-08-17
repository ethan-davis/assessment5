CC=g++
CFLAGS=-g -Wall -std=c++11
HEADERS=main.h game.h collector.h
OBJECTS=assess5.o game.o collector.o

main: $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJECTS) -o assess5
 
%.o: %.cpp 
	$(CC) -c  $(CFLAGS) $< 

clean:
	rm *.o main
