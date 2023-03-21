#pragma once
#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>

class InfoNutri
{
private:

//May be replace with key-value tab

	static const std::vector<std::string> keys;
	std::map<std::string, double> values;
/*
	UNUSED
	//UNUSED //InfoNutri(double perAmount,double calories,double fat, double cholesterol, double sodium, double carbohydrate, double protein); //May be unused
	double perAmount;
	double calories;
	double fat;
	double cholesterol;
	double sodium;
	double carbohydrate;
	double protein;
*/
public:

	InfoNutri();
	InfoNutri(std::map<std::string, double>& values);
	InfoNutri(double* tab); // Tab of all parameters
	InfoNutri(InfoNutri& c);

	void printInfoNutri();
	std::map<std::string, double> *getInfoNutri();
};

