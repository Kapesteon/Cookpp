#include "Aliment.h"

Aliment::Aliment()
	: Ingredient()
{

	this->mass = 0;
}

Aliment::Aliment(std::string name, std::string type, std::string season, InfoNutri* infoNutri, double mass)
	: Ingredient(name, type, season, infoNutri) 
{

	this->mass = mass;
}

Aliment::Aliment(const Ingredient& ingr, double mass)
	: Ingredient(ingr)
{

	this->mass = mass;
}

Aliment::Aliment(const Aliment& c)
{
	this->setName(c.getName());
	this->setType(c.getType());
	this->setSeason(c.getSeason());
	this->setInfoNutri(c.getInfoNutri());
	this->mass = c.mass;
}

Aliment::~Aliment()
{
	OutputDebugStringA("Aliment Destroyed \n");
}

void Aliment::setMass(double mass)
{
	this->mass = mass;
	return;
}

const double Aliment::getMass() const
{
	return this->mass;
}



bool operator<(const Aliment& l, const Aliment& r)
{
	return std::tie(l.getName())
		< std::tie(r.getName()); // keep the same order
}

bool operator==(const Aliment& l, const Aliment& r)
{
	if (l.getName() == r.getName() && l.getMass() == r.getMass()) {
		return true;
	}
	else {
		return false;
	}
}

bool operator!=(const Aliment& l, int a)
{
	if (a != 0) {
		return true;
	}
	else {
		if ( ( int(l.getMass()) != 0) || (l.getName() != "Undefined") || (l.getType()) != "N/A") {
			return true;
		}
	}
	return false;
}

std::istream& operator>>(std::istream& is, Aliment& in)
{

	try {
		is >> static_cast<Ingredient&>(in); //static cast to call Parent istream operator>>
		std::string newMass = "";
		is >> newMass;
		in.setMass(std::stod(newMass));
		return is;
	}
	catch (std::exception) {
		std::cout << "Couldn't recover Aliment from database";
		OutputDebugStringA("Couldn't recover Aliment from database");
		return is;
	}


	return is;

}

std::ostream& operator<<(std::ostream& os, const Aliment& in)
{

	try {
		os << static_cast<const Ingredient&>(in)
			<< std::endl
			<< in.getMass()
			<< std::endl;
		return os;
	}
	catch (std::exception) {
		std::cout << "Couldn't add Aliment to database";
		OutputDebugStringA("Couldn't add Aliment to database");
		return os;
	}
	return os;
}


