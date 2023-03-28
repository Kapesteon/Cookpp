#pragma once
#include "debug.h"
#include "Windows.h"
#include "debugapi.h"
#include "InfoNutri.h"
#include "Aliment.h"
#include "StockedAliment.h"
#include "Pantry.h"
#include "Recipe.h"
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
	Ingredient testIngredient3 = Ingredient("Potato", "Vegetable", "N/A", &testInfoNutri3);
	Ingredient testIngredient4 = Ingredient(testIngredient3);

	Aliment testAliment;
	Aliment testAliment2 = Aliment(testIngredient2, 500); //Carot
	Aliment testAliment3 = Aliment(testIngredient3, 500); //Potato
	Aliment testAliment4 = Aliment("Apple", "Fruit", "Winter", &testInfoNutri1, 200); //Apple
	Aliment testAliment5 = Aliment(testAliment4);

	StockedAliment testStockedAliment;
	StockedAliment testStockedAliment2 = StockedAliment(testAliment2, 50000, 1000); //Carot
	StockedAliment testStockedAliment3 = StockedAliment(testAliment3, "2022-02-12", 30); //Potato
	StockedAliment testStockedAliment4 = StockedAliment(testIngredient2, 100, time_t(95484845214), time_t(1555000)); //Carot
	StockedAliment testStockedAliment5 = StockedAliment(testIngredient3, 100,"2023-03-13", 15); //Potato
	StockedAliment testStockedAliment6 = StockedAliment(testStockedAliment2); //Carot
	StockedAliment testStockedAliment7 = StockedAliment();

	auto s1 = testStockedAliment3.getObtainedDate();
	auto s2 = testStockedAliment3.getSpoilDate();


	std::forward_list<StockedAliment* > stockedAlimentList;
	stockedAlimentList.assign({&testStockedAliment,&testStockedAliment2,&testStockedAliment3,&testStockedAliment4});
								//""					Carot			, Potato			, Carot

	Pantry pantry = Pantry();
	Pantry pantry2 = Pantry(stockedAlimentList);
	pantry2.addToStock(&testStockedAliment5);
	auto a = pantry2.getStock();
	auto b = pantry2.popStockedAlimentByName("Carot");
	auto c = pantry2.popStockedAlimentByType("Vegetable");
	auto d = pantry2.popStockedAlimentMostDated(4);

	std::string s[] = { "1a","2b","3c","4d","5e"};
	std::vector<std::string> strs(s, s + sizeof(s) / sizeof(std::string));

	Recipe testRecipe1 = Recipe();
	testRecipe1.addAliment(testAliment2);
	testRecipe1.addAliment(testAliment3);
	testRecipe1.setSteps(strs);
	testRecipe1.addStep("6f");
	testRecipe1.addStep("7g");
	testRecipe1.removeLastStep();
	testRecipe1.setNotes("here are some notes");


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
