CC=g++
CFLAGS=-Wall
LDFLAGS=
EXEC=analyze
OBJ=main.o

%.o : %.cpp %.h
	$(CC) -c $*.cpp $(CFLAGS)

main.o :
	$(CC) -c main.cpp $(CFLAGS)  

analyze : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) 
	rm -rf *.o

clean:
	rm -rf *.o
