#include "../headers/utils/saveUtils.h"

void SaveUtils::save(const Character character) {
    std::string path = SAVE_PATH+character.getName()+".sav";
	std::ofstream f(const_cast<char*>(path.c_str()));
    if (!f.is_open())
        std::cerr << "Error: Can't write in the save file." << std::endl;
    else {
        f << character.getX() << " " << character.getY() << " " << SaveUtils::serialize(&character.getRace());
        f << " " << character.getMap();
        f.close();
    }
}

Character SaveUtils::load(std::string name, Interface &interface) {
    std::string path = SAVE_PATH+name+".sav";
    std::ifstream file(const_cast<char*>(path.c_str()), std::ios::in);
    if(file) {
        int x;
        int y;
        file >> x >> y;
        int raceChoice;
        std::string map;
        file >> raceChoice >> map;
        Character loadedChar = Character(name, raceChoice, map);
        loadedChar.setX(x);
        loadedChar.setY(y);
        std::string line;
        while (getline(file, line))
            interface.write(line);
        file.close();
        return loadedChar;
    }
    else
        std::cerr << "Error: Can't read save file." << std::endl;
    Character charNull = Character();
    return charNull;
}

Map SaveUtils::loadMap(std::string charName, std::string mapName) {
    Map loadedMap = Map();
    std::string path = WORLD_PATH+charName+"/"+mapName+".map";
    std::ifstream file(const_cast<char*>(path.c_str()), std::ios::in);
    if(file) {
        int length;
        int width;
        file >> length >> width;
        loadedMap.setLength(length);
        loadedMap.setWidth(width);
        loadedMap.cell = new Cell* [length];
        for (int i=0;i<length;i++)
            loadedMap.cell[i] = new Cell [width];
        for (int j=0;j<width;j++) {
            for (int i=0;i<length;i++) {
                int cellType;
                file >> cellType;
                switch (cellType) {
                    case NOTHING_CODE: {loadedMap.cell[i][j] = Cell();break;}
                    case DUNGEON_FLOOR_A: {loadedMap.cell[i][j] = DungeonFloorA();break;}
                    case DUNGEON_WALL_A: {loadedMap.cell[i][j] = DungeonWallA();break;}
                }
            }
        }
        std::string end;
        file >> end;
        while ((end == ":") && !file.eof()) {
            int itemType, itemX, itemY;
            file >> itemType >> itemX >> itemY;
            switch (itemType) {
                case DEFAULT_ITEM: {loadedMap.cell[itemX][itemY].drops.push_front(Item());break;}
                case SWORD_1H_A: {loadedMap.cell[itemX][itemY].drops.push_front(Sword1HA());break;}
                case GREAVES_L_A: {loadedMap.cell[itemX][itemY].drops.push_front(GreavesLA());break;}
          }
          file >> end;
        }
        file.close();
    }
    else
        std::cerr << "Error: Can't read save file." << std::endl;
    return loadedMap;
}

std::string SaveUtils::serialize(const Race *race) {
    std::ostringstream oss;
    oss << (*race).getRaceCode();
	return oss.str();
}