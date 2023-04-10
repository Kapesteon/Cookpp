#pragma once
#include "iostream"
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
		const double getMass() const;

		//Aliment operator< (const Aliment& a) const;
		friend bool operator<(const Aliment& l, const Aliment& r);
		friend bool operator==(const Aliment& l, const Aliment& r);
		friend std::istream& operator >>(std::istream& is, Aliment& in);
		friend std::ostream& operator <<(std::ostream& os, const Aliment& in);

};

