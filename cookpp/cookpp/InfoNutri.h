#pragma once
#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include <array>
#include "Windows.h"
#include "debugapi.h"
#define NUMBER_ATRIBUTES 7

class InfoNutri
{
private:
	
	static std::vector<std::string> keys;
	//std::map<std::string, double> values;
	std::array<double, NUMBER_ATRIBUTES> nutriValues = std::array<double, NUMBER_ATRIBUTES>();

public:


	InfoNutri();
	InfoNutri(std::vector<double>& param);
	InfoNutri(double* tab, size_t len); // Tab of all parameters
	InfoNutri(std::map<std::string, double> values); //Unused
	InfoNutri(const InfoNutri& c);
	~InfoNutri();

	void setValueByKey(std::string key, double value);
	const std::array<double, NUMBER_ATRIBUTES> getNutriValues() const;

	static const std::vector<std::string> getNutriKeys();


	//Overloading streams
	//friend std::ostream& operator<<(std::ostream& os, const InfoNutri& dt);


	friend std::istream& operator>>(std::istream& is, InfoNutri& in);
	friend std::ostream& operator<<(std::ostream& os, const InfoNutri& in);
};

