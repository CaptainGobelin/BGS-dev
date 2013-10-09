#ifndef EXIT_H
#define EXIT_H

#include "../utils/lib.h"
#include "../utils/const.h"

#include "textures.h"

class MapExit {
	public :
		MapExit(std::string code = "");

		const std::string &getDestCode() const {return destCode;}
		void setDestCode(const std::string &newDestCode) {destCode=newDestCode;}
		const std::string &getDestName() const {return destName;}
		void setDestName(const std::string &newDestName) {destName=newDestName;}

		template<class Archive>
	    void serialize(Archive& ar, const unsigned int version){
	        ar & destCode & destName;
	    }

	private :
		std::string destCode;
		std::string destName;
};

BOOST_CLASS_VERSION(MapExit, 9);

#endif