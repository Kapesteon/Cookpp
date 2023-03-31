#pragma once
#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include "Windows.h"
#include "debugapi.h"

class InfoNutri
{
private:
	
	static std::vector<std::string> keys;
	std::map<std::string, double> values;


public:


	InfoNutri();
	InfoNutri(std::vector<double>& param);
	InfoNutri(double* tab, size_t len); // Tab of all parameters
	InfoNutri(std::map<std::string, double> values);
	InfoNutri(const InfoNutri& c);
	~InfoNutri();

	void printInfoNutri();
	const std::map<std::string, double> getNutriValues() const;


	//Overloading cout
	friend std::ostream& operator<<(std::ostream& os, const InfoNutri& dt);
};

