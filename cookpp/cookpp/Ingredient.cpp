#include "Ingredient.h"
#define DELIMITER_DB ":@:"

Ingredient::Ingredient()
{
	this->name = "Undefined";
	this->type = "N/A";
	this->season = "N/A";
	this->infoNutri = InfoNutri();
}

Ingredient::Ingredient(std::string name, std::string type, std::string season, InfoNutri *infoNutri)
{
	this->name = name;
	this->type = type;
	this->season = season;
	this->infoNutri = *infoNutri;
}


Ingredient::Ingredient(const Ingredient& c)
{
	this->name = c.name;
	this->type = c.type;
	this->season = c.season;
	this->infoNutri = c.infoNutri;
}

Ingredient::~Ingredient()
{
	/*
	if (this->infoNutri == NULL); {
		OutputDebugStringA("InfoNutri in Ingredient aleady destroyed\n");
	}
	try {
		delete this->infoNutri;
	}
	catch (std::exception e) {
		OutputDebugStringA("Error while destroying Ingredient :");
		OutputDebugStringA(e.what());
	}
	*/
	OutputDebugStringA("Ingredient Destroyed \n");
}

const std::string Ingredient::getName(void) const
{
	return std::string(this->name);
}

void Ingredient::setName(std::string name)
{
	this->name = name;
	return;
}

const std::string Ingredient::getType(void) const
{
	return std::string(this->type);
}

void Ingredient::setType(std::string type)
{
	this->type = type;
	return;
}

const std::string Ingredient::getSeason(void) const 
{
	return std::string(this->season);
}


void Ingredient::setSeason(std::string season)
{
	this->season = season;
	return;
}

InfoNutri Ingredient::getInfoNutri(void) const
{

	return this->infoNutri;
}

void Ingredient::setInfoNutri(InfoNutri  infoNutri)
{
	this->infoNutri = infoNutri;
	return;
}



std::istream& operator>>(std::istream& is, Ingredient& in)
{


	try {
		is >> in.name;
		is >> in.type;
		is >> in.season;
		is >> in.infoNutri;
	}
	catch(std::exception){
		std::cout << "Couldn't recover Ingredient from database";
		OutputDebugStringA("Couldn't recover Ingredient from database");
		return is;
	}


	return is;

}

std::ostream& operator<<(std::ostream& os, const Ingredient& in)
{
	os << in.getName()
	<< std::endl
	<< in.getType()
	<< std::endl
	<< in.getSeason()
	<< std::endl
	<< in.getInfoNutri()
	//<< DELIMITER_DB 
	<< std::endl;
	
	return os;
}







/*
* OLD operator>>
std::string s = "";
is >> s;

size_t pos = 0;
std::string token;
std::string delimiter = DELIMITER_DB;
std::vector<std::string> values;
int i = 0;
try {
	while ((pos = s.find(delimiter)) != std::string::npos) {

		token = s.substr(0, pos);
		values.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
}
catch (std::exception) {
	std::cout << "Couldn't recover Ingredient from database";
	OutputDebugStringA("Couldn't recover Ingredient from database");
	return is;
}
if (values.size() != 4) { //If there is no 4 attributes recovered
	std::cout << "Couldn't recover Ingredient from database";
	OutputDebugStringA("Couldn't recover Ingredient from database");
	return is;
}

in.setName(values[0]);
in.setType(values[1]);
in.setSeason(values[2]);
//in.setInfoNutri(values[3]);

return is;
*/