#pragma once
#include "Ingredient.h"
class Aliment : public Ingredient
{
	private:
		double mass;

	public:
		Aliment();
		Aliment(std::string name, std::string type, std::string season, InfoNutri* infoNutri, double mass);
		Aliment(const Ingredient& ingr, double mass);
		Aliment(const Aliment & c);
		~Aliment();

		void setMass(double mass);
		double getMass();
};

