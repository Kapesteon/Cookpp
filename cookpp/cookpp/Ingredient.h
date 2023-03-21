#pragma once
#include <stdlib.h>
#include <string>
#include "InfoNutri.cpp"

class Ingredient
{
private:
	std::string name;
	std::string type;
	std::string season;


public:

	InfoNutri infoNutri;

	Ingredient();		
	Ingredient(std::string name, std::string type, std::string season, InfoNutri &infoNutri);
	Ingredient(Ingredient &c);

	std::string getName(void);
	void setName(std::string name);
	std::string getType(void);
	void setType(std::string type);
	std::string getSeason(void);
	void setSeason(std::string season);
	

};

