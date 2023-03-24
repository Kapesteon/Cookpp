#pragma once
#include <stdlib.h>
#include <string>
#include <memory>
#include "InfoNutri.h"
#include "Windows.h"
#include "debugapi.h"

class Ingredient

{
private:
	std::string name;
	std::string type;
	std::string season;
	InfoNutri infoNutri;

public:

	

	Ingredient();		
	Ingredient(std::string name, std::string type, std::string season, InfoNutri *infoNutri);
	Ingredient(const Ingredient &c);
	~Ingredient();

	const std::string getName(void) const;
	void setName(std::string name);
	const std::string getType(void) const ;
	void setType(std::string type);
	const std::string getSeason(void) const;
	void setSeason(std::string season);
	InfoNutri getInfoNutri(void) const;
	void setInfoNutri(InfoNutri infoNutri);

};

