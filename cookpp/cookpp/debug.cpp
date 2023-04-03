#pragma once
#include <iostream>
#include <fstream>
#include <ios>
#include "debug.h"
#include "Windows.h"
#include "debugapi.h"
#include "InfoNutri.h"
#include "Aliment.h"
#include "StockedAliment.h"
#include "Pantry.h"
#include "Recipe.h"
#include "NutritionalManager.h"

void debug()
{

	std::ostringstream;
	OutputDebugStringA("test \n ");
	//InfoNutri* testInfoNutri2 = new InfoNutri();
	double tab[7] = { 52.1,98.5,100,258,48,987,10 };
	double tab2[7] = { 1,2,3,4,5,6,7};
	double tab3[7] = { 100,1200,65,0.3,2.4,300,20 };

	InfoNutri testInfoNutri1;
	InfoNutri testInfoNutri2 = InfoNutri(tab,7);
	InfoNutri testInfoNutri3 = InfoNutri(testInfoNutri2);
	InfoNutri testInfoNutri4 = InfoNutri(tab2, 7);
	InfoNutri testInfoNutri5 = InfoNutri(tab3, 7);

	auto e = testInfoNutri3.getNutriValues();
	std::cout << "test";

	Ingredient testIngredient1;
	Ingredient testIngredient2 = Ingredient("Carot", "Vegetable", "N/A", &testInfoNutri2);
	Ingredient testIngredient3 = Ingredient("Potato", "Vegetable", "N/A", &testInfoNutri3);
	Ingredient testIngredient4 = Ingredient(testIngredient3);
	Ingredient testIngredient5 = Ingredient("Perfection", "P", "Winter", &testInfoNutri5);

	Aliment testAliment1;
	Aliment testAliment2 = Aliment(testIngredient2, 500); //Carot
	Aliment testAliment3 = Aliment(testIngredient3, 500); //Potato
	Aliment testAliment4 = Aliment("Apple", "Fruit", "Winter", &testInfoNutri1, 200); //Apple
	Aliment testAliment5 = Aliment(testAliment4);
	Aliment testAliment6 = Aliment(testIngredient5, 100); //TEST perfection

	StockedAliment testStockedAliment1;
	StockedAliment testStockedAliment2 = StockedAliment(testAliment2, 50000, 1000); //Carot
	StockedAliment testStockedAliment3 = StockedAliment(testAliment3, "2022-02-12", 30); //Potato
	StockedAliment testStockedAliment4 = StockedAliment(testIngredient2, 100, time_t(95484845214), time_t(1555000)); //Carot
	StockedAliment testStockedAliment5 = StockedAliment(testIngredient3, 100,"2023-03-13", 15); //Potato
	StockedAliment testStockedAliment6 = StockedAliment(testStockedAliment2); //Carot
	StockedAliment testStockedAliment7 = StockedAliment();

	auto s1 = testStockedAliment3.getObtainedDate();
	auto s2 = testStockedAliment3.getSpoilDate();


	std::forward_list<StockedAliment* > stockedAlimentList;
	stockedAlimentList.assign({&testStockedAliment1,&testStockedAliment2,&testStockedAliment3,&testStockedAliment4});
								//""					Carot			, Potato			, Carot

	Pantry pantry = Pantry();
	Pantry pantry2 = Pantry(stockedAlimentList);
	pantry2.addToStock(&testStockedAliment5);
	auto a = pantry2.getStock();
	//auto b = pantry2.popStockedAlimentByName("Carot");
	//auto c = pantry2.popStockedAlimentByType("Vegetable");
	//auto d = pantry2.popStockedAlimentMostDated(4);

	std::string s[] = { "1a","2b","3c","4d","5e"};
	std::vector<std::string> strs(s, s + sizeof(s) / sizeof(std::string));

	
	Recipe testRecipe1 = Recipe();

	Recipe testRecipe2 = Recipe();
	testRecipe2.addAliment(testAliment6);
	testRecipe2.markAsComplete();

	Recipe testRecipe3 = Recipe();
	testRecipe3.addAliment(testAliment2);
	testRecipe3.addAliment(testAliment3);
	testRecipe3.setSteps(strs);
	testRecipe3.addStep("6f");
	testRecipe3.addStep("7g");
	testRecipe3.removeLastStep();
	testRecipe3.setNotes("here are some notes");
	testRecipe3.markAsComplete();

	NutritionalManager* testNManager = testNManager->getSingleton();
	auto w = testRecipe2.getAliments();
	testNManager->estimateNutriValue(w);
	/*
	testAliment4.~Aliment();
	OutputDebugStringA("\n\n ");
	testIngredient2.~Ingredient();
	OutputDebugStringA("\n\n ");
	testInfoNutri4.~InfoNutri();
	OutputDebugStringA("\n\n ");
	*/


	/*
	std::fstream file;

	file.open("stockDB/file.txt", std::ios::in | std::ios::out | std::ios::binary);
	file.write((char*)&testInfoNutri5, sizeof(InfoNutri));
	file.write((char*)&testInfoNutri4, sizeof(InfoNutri));
	file.seekp(0, std::ios::beg);
	file.read((char*)&testInfoNutri1, sizeof(InfoNutri));
	file.seekg(1*sizeof(InfoNutri), std::ios::beg);
	file.read((char*)&testInfoNutri2, sizeof(InfoNutri));
	
	file.close();



	std::fstream dbIngredients;

	dbIngredients.open("stockDB/ingredients.cdb", std::ios::in | std::ios::out | std::ios::binary);
	dbIngredients.write((char*)&testIngredient5, sizeof(Ingredient));
	dbIngredients.seekp(0, std::ios::beg);
	dbIngredients.read((char*)&testIngredient1, sizeof(Ingredient));

	dbIngredients.close();
	*/

	/*
	std::fstream file2;
	file2.open("stockDB/file2.cdb", std::ios::in | std::ios::out | std::ios::binary);
	file2.write((char*)&testAliment6, sizeof(Aliment));
	file2.write((char*)&testAliment5, sizeof(Aliment));
	file2.seekp(0, std::ios::beg);
	file2.read((char*)&testAliment1, sizeof(Aliment));
	file2.seekg(1 * sizeof(Aliment), std::ios::beg);
	file2.read((char*)&testAliment1, sizeof(Aliment));
	file2.close();
	*/

	/*
	std::fstream dbRecipe;
	dbRecipe.open("stockDB/recipe.cdb", std::ios::in | std::ios::out | std::ios::binary);
	dbRecipe.write((char*)&testRecipe2, sizeof(Recipe));
	dbRecipe.write((char*)&testRecipe3, sizeof(Recipe));
	dbRecipe.seekp(0, std::ios::beg);
	dbRecipe.read((char*)&testRecipe1, sizeof(Recipe));
	dbRecipe.seekg(1 * sizeof(Recipe), std::ios::beg);
	dbRecipe.read((char*)&testRecipe1, sizeof(Recipe));
	dbRecipe.close();
	*/
	/*
	std::fstream file3;
	file3.open("stockDB/file3.cdb", std::ios::in | std::ios::out | std::ios::binary);
	file3.write((char*)&testStockedAliment5, sizeof(StockedAliment));
	file3.write((char*)&testStockedAliment4, sizeof(StockedAliment));
	file3.seekp(0, std::ios::beg);
	file3.read((char*)&testStockedAliment1, sizeof(StockedAliment));
	file3.seekg(1 * sizeof(StockedAliment), std::ios::beg);
	file3.read((char*)&testStockedAliment1, sizeof(StockedAliment));
	file3.close();
	*/

	std::fstream dbPantry;
	dbPantry.open("stockDB/pantry.cdb", std::ios::in | std::ios::out | std::ios::binary);
	dbPantry.write((char*)&pantry2, sizeof(Pantry));
	dbPantry.seekp(0, std::ios::beg);
	dbPantry.read((char*)&pantry, sizeof(Pantry));
	dbPantry.close();

	return;
}
