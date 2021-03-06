#ifndef MAP_H
#define MAP_H

#include "../utils/lib.h"
#include "../utils/const.h"

#include "cell.h"
#include "textures.h"
#include "../GUI/gameWindow.h"

class Map {
	public:
		Map(int x=0, int y=0);
		~Map();
		const int &getLength() const {return length;}
		void setLength(const int &newLength) {length=newLength;}
		const int &getWidth() const {return width;}
		void setWidth(const int &newWidth) {width=newWidth;}
		const std::string &getName() const {return name;}
		void setName(const std::string &newName) {name=newName;}
		const int &getDependencies() const {return dependencies;}
		void setDependencies(const int &newDependencies) {dependencies=newDependencies;}

		//Pass a turn to all cells of the map
		void refreshCells(const int x, const int y);
		void draw(const int x, const int y);

		Cell **cell;
		sf::Sprite fog;

		template<class Archive>
	    void save(Archive& ar, const unsigned int version) const {
	        ar & length & width & name & dependencies;
	        for (int i=0;i<length;i++)
	        	for (int j=0;j<width;j++)
	        		ar & cell[i][j];
	    }
	    template<class Archive>
	    void load(Archive& ar, const unsigned int version){
	        ar & length & width & name & dependencies;
	        cell = new Cell* [length];
   			for (int i=0;i<length;i++)
        		cell[i] = new Cell [width];
	        for (int i=0;i<length;i++)
	        	for (int j=0;j<width;j++)
	        		ar & cell[i][j];
	    }
	    BOOST_SERIALIZATION_SPLIT_MEMBER();

	private:
		int length;
		int width;
		std::string name;
		//How many map must be generate after this one
		int dependencies;
};

BOOST_CLASS_VERSION(Map, 5);

#endif