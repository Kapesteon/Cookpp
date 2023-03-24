#pragma once
#include <stdlib.h>
#include <string>
//#include "InfoNutri.cpp"
#include "InfoNutri.h"
class Ingredient

{
private:
	std::string name;
	std::string type;
	std::string season;
	InfoNutri* infoNutri;

public:

	

	Ingredient();		
	Ingredient(std::string name, std::string type, std::string season, InfoNutri *infoNutri);
	Ingredient(const Ingredient &c);

	std::string getName(void);
	void setName(std::string name);
	std::string getType(void);
	void setType(std::string type);
	std::string getSeason(void);
	void setSeason(std::string season);
	InfoNutri * getInfoNutri(void);
	void setInfoNutri(InfoNutri * infoNutri);

};

