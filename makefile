CC=g++
CFLAGS=-Wall
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -Wall
EXEC=bgs
OBJ=main.o gameController.o optionsFile.o gameWindow.o startController.o \
startController.o gameInput.o startScreen.o menuController.o textures.o character.o race.o \
saveUtils.o map.o cell.o loadGameMenuController.o sessionController.o sessionScreen.o \
interface.o mapController.o mapScreen.o item.o

%.o : src/utils/%.cpp src/headers/utils/%.h
	$(CC) -c src/utils/$*.cpp $(CFLAGS)

%.o : src/Model/%.cpp src/headers/Model/%.h
	$(CC) -c src/Model/$*.cpp $(CFLAGS)

%.o : src/GUI/%.cpp src/headers/GUI/%.h
	$(CC) -c src/GUI/$*.cpp $(CFLAGS)
	
%.o : src/%.cpp src/headers/%.h
	$(CC) -c src/$*.cpp $(CFLAGS)

main.o :
	$(CC) -c src/main.cpp $(CFLAGS)  

bgs : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) 
	rm -rf *.o

clean:
	rm -rf *.o
