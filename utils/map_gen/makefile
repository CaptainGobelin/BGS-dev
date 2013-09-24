CC=g++
CFLAGS=-Wall
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -Wall
EXEC=generate
OBJ=main.o mapGenerator.o map.o pattern.o

%.o : %.cpp %.h
	$(CC) -c $*.cpp $(CFLAGS)

main.o :
	$(CC) -c main.cpp $(CFLAGS)  

generate : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) 
	rm -rf *.o

clean:
	rm -rf *.o
