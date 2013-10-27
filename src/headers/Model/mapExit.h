#ifndef EXIT_H
#define EXIT_H

#include "../utils/lib.h"
#include "../utils/const.h"

#include "textures.h"

//A map exit is a link between to map (a way to a map to an anoter one)

class MapExit {
	public:
		MapExit(std::string code = "", int dep = 0);

		const std::string &getDestCode() const {return destCode;}
		void setDestCode(const std::string &newDestCode) {destCode=newDestCode;}
		const std::string &getDestName() const {return destName;}
		void setDestName(const std::string &newDestName) {destName=newDestName;}
		const int &getDependencies() const {return dependencies;}
		void setDependencies(const int &newDependencies) {dependencies=newDependencies;}

		template<class Archive>
	    void serialize(Archive& ar, const unsigned int version){
	        ar & destCode & destName & dependencies;
	    }

	private:
		std::string destCode;
		std::string destName;
		int dependencies;
};

BOOST_CLASS_VERSION(MapExit, 9);

#endif