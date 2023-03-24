#pragma once
#include "debug.h"
#include "InfoNutri.h"
#include "Windows.h"
#include "debugapi.h"
#include "Aliment.h"

void debug()
{

	std::ostringstream;
	OutputDebugStringA("test \n ");
	//InfoNutri* testInfoNutri2 = new InfoNutri();
	double tab[7] = { 52.1,98.5,100,258,48,987,10 };
	double tab2[7] = { 1,2,3,4,5,6,7};
	InfoNutri testInfoNutri1;
	InfoNutri testInfoNutri2 = InfoNutri(tab,7);
	InfoNutri testInfoNutri3 = InfoNutri(testInfoNutri2);
	InfoNutri testInfoNutri4 = InfoNutri(tab2, 7);

	auto e = testInfoNutri3.getInfoNutri();
	std::cout << "test";

	Ingredient testIngredient;
	Ingredient testIngredient2 = Ingredient("Carot", "Vegetable", "N/A", &testInfoNutri2);
	Ingredient testIngredient3 = Ingredient("Carot", "Vegetable", "N/A", &testInfoNutri3);
	Ingredient testIngredient4 = Ingredient(testIngredient3);

	Aliment testAliment;
	Aliment testAliment2 = Aliment(testIngredient2, 500);
	Aliment testAliment3 = Aliment(testIngredient3, 500);
	Aliment testAliment4 = Aliment("Apple", "Fruit", "Winter", &testInfoNutri1, 200);
	Aliment testAliment5 = Aliment(testAliment4);


	/*
	testAliment4.~Aliment();
	OutputDebugStringA("\n\n ");
	testIngredient2.~Ingredient();
	OutputDebugStringA("\n\n ");
	testInfoNutri4.~InfoNutri();
	OutputDebugStringA("\n\n ");
	*/
	return;
}
