#pragma once
#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>

class InfoNutri
{
private:
	
	static std::vector<std::string> keys;
	std::map<std::string, double> values;
	

	//UNUSED //InfoNutri(double perAmount,double calories,double fat, double cholesterol, double sodium, double carbohydrate, double protein); //May be unused
	/*
	double perAmount;
	double calories;
	double fat;
	double cholesterol;
	double sodium;
	double carbohydrate;
	double protein;
	*/

public:

	//define the static vector Keys
	//static void instanciateKeys();
	

	//Overloading cout
	friend std::ostream& operator<<(std:: ostream& os, const InfoNutri& dt);

	InfoNutri();
	InfoNutri(std::vector<double>& param);
	InfoNutri(double* tab, size_t len); // Tab of all parameters
	InfoNutri(const InfoNutri& c);

	void printInfoNutri();
	const std::map<std::string, double> getInfoNutri() const;
};

