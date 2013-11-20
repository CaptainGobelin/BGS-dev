CC=g++
CFLAGS=-Wall
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -Wall
EXEC=room
OBJ=main.o

%.o : %.cpp %.h
	$(CC) -c $*.cpp $(CFLAGS)

main.o :
	$(CC) -c main.cpp $(CFLAGS)  

room : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) 
	rm -rf *.o

clean:
	rm -rf *.o
