
CC = g++

INCLUDE = .

CFLAGS = 

main : main.o elevator.o
	$(CC) -o main main.o elevator.o
main.o : main.cpp elevator.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c main.cpp
elevator.o : elevator.cpp elevator.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c elevator.cpp 



