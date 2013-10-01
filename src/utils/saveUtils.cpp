#include "../headers/utils/saveUtils.h"

void SaveUtils::save(const Character &character) {
    std::string pathChar = SAVE_PATH+character.getName()+".sav";
    std::ofstream ofile(const_cast<char*>(pathChar.c_str()));
    boost::archive::binary_oarchive oBinaryArchive(ofile);
    oBinaryArchive << character; 
}

void SaveUtils::saveMap(std::string charName, std::string mapName, const Map &map) {
    std::string pathMap = WORLD_PATH+charName+"/"+mapName+".map";
    std::ofstream ofile(const_cast<char*>(pathMap.c_str()));
    boost::archive::binary_oarchive oBinaryArchive(ofile);
    oBinaryArchive << map;
}

Character SaveUtils::load(std::string name, Interface &interface) {
    std::string path = SAVE_PATH+name+"_journal.sav";
    std::ifstream file(const_cast<char*>(path.c_str()), std::ios::in);
    if(file) {
        Character loadedChar;
        std::string pathChar = SAVE_PATH+name+".sav";
        std::ifstream ifile(const_cast<char*>(pathChar.c_str()));
        boost::archive::binary_iarchive iBinaryArchive(ifile);
        iBinaryArchive >> loadedChar;
        loadedChar.loadSprite();
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
    Map loadedMap;
    std::string path = WORLD_PATH+charName+"/"+mapName+".map";
    std::ifstream ifile(const_cast<char*>(path.c_str()));
    boost::archive::binary_iarchive iBinaryArchive(ifile);
    iBinaryArchive >> loadedMap;
    return loadedMap;
}