#pragma once
#include <iostream>
#include <fstream>
#include <ios>

#include "debug.h"
#include "Windows.h"
#include "debugapi.h"
#include <deque>

#include "InfoNutri.h"
#include "Aliment.h"
#include "StockedAliment.h"
#include "Pantry.h"
#include "Recipe.h"
#include "NutritionalManager.h"
#include "PantryDBManager.h"
#include "RecipeDBManager.h"
#include "FacadeUserDB.h"
#include "Menu.h"
#include "Gardien.h"

#include <string>

/*
void debug()
{

	std::ostringstream;
	Menu menu;
	std::time_t currentTime = std::time(nullptr);
	menu.setStartDate(currentTime);
	menu.setNumConsumers(5);
	std::string chaine = std::to_string(menu.getStartDate());
	LPCSTR ma_chaine_lpcstr = chaine.c_str();

	OutputDebugStringA(ma_chaine_lpcstr);

	//std::cout << menu.getStartDate();

	//std::cout << "test fini";
}
*/


void debug()
{
	initDb();

	/*/Menu menu;
	std::time_t currentTime = std::time(nullptr);
	menu.setStartDate(currentTime);
	std::cout << menu.getStartDate();

	FacadeUserDB facade;

	p = facade.getPantry();

	std::list<Recipe*> maListe = facade.getAllRecipe();
	auto it = maListe.begin();
	std::cout << "L'élément 3 de la liste est : " << (*it)->getName() << std::endl;*/


	/*RecipeDBManager DBRecipe("stockDB/recipe.cdb");
	std::list<Recipe*> r;
	r = DBRecipe.getAllRecipe();

	for (auto it = r.begin(); it != r.end(); ++it) {
		std::cout << it->getName() << std::endl;
	}

	auto it = r.begin();
	std::advance(it, 2);

	std::cout << "L'élément 3 de la liste est : " << it->getName() << std::endl;*/

	//Recipe rr = *it;
	
	std::cout << "hujki";
	//std::ostringstream;
	//OutputDebugStringA("test \n ");
	//InfoNutri* testInfoNutri2 = new InfoNutri();
	/*double tab[7] = {52.1,98.5,100,258,48,987,10};
	double tab2[7] = { 1,2,3,4,5,6,7};
	double tab3[7] = { 100,1200,65,0.3,2.4,300,20 };

	InfoNutri testInfoNutri1;
	InfoNutri testInfoNutri2 = InfoNutri(tab,7);
	InfoNutri testInfoNutri3 = InfoNutri(testInfoNutri2);
	InfoNutri testInfoNutri4 = InfoNutri(tab2, 7);
	InfoNutri testInfoNutri5 = InfoNutri(tab3, 7);

	auto e = testInfoNutri3.getNutriValues();
	std::cout << "test";

	std::cout << "test fini";

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
	testRecipe2.setName("Recette2");
	testRecipe2.markAsComplete();

	Recipe testRecipe3 = Recipe();
	testRecipe3.setName("Recette3");
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
	

	menu.addRecipe(testRecipe2);
	menu.addRecipe(testRecipe3);
	menu.removeRecipe(testRecipe3);

	RecipeDBManager DBRecipe("stockDB/recipe.cdb");
	DBRecipe.append(&testRecipe2);
	DBRecipe.append(&testRecipe3);
	DBRecipe.read(&testRecipe1, 1);
	DBRecipe.read(&testRecipe1, 2);
	std::list<Recipe*> r;
	//r.push_back(&testRecipe1);
	r = DBRecipe.getAllRecipe();

	std::cout << "yoo";*/
	/*
	testAliment4.~Aliment();
	OutputDebugStringA("\ns\n ");
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
	/*
	void* h = &pantry;

	std::fstream dbPantry;
	dbPantry.open("stockDB/pantry.cdb", std::ios::in | std::ios::out | std::ios::binary);
	dbPantry.write((char*)&pantry2, sizeof(Pantry));
	dbPantry.seekp(0, std::ios::beg);
	dbPantry.read((char*)h, sizeof(Pantry));
	dbPantry.close();
	*/



	/*
	RecipeDBManager DBRecipe("stockDB/recipe.cdb");
	DBRecipe.append(&testRecipe2);
	DBRecipe.append(&testRecipe3);
	DBRecipe.read(&testRecipe1, 1);
	DBRecipe.read(&testRecipe1, 2);
	std::list<Recipe *> r;
	r.push_back(&testRecipe1);
	r = DBRecipe.getAllRecipe();
	*/
	

/*

	IngredientDBManager DBIngredient("stockDB/ingredient.cdb");
	DBIngredient.write(&testIngredient2,0);
	DBIngredient.append(&testIngredient4);
	DBIngredient.read(&testIngredient1, 0);
	DBIngredient.read(&testIngredient1, 1);
	std::list<Ingredient*> r;
	r = DBIngredient.getAllIngredient();
*/

	/*FacadeUserDB facade;

	facade.savePantry(&pantry2);
	pantry = facade.getPantry();

	facade.addIngredient(&testIngredient1);
	facade.addIngredient(&testIngredient2);
	facade.addIngredient(&testIngredient3);
	facade.saveIngredient(&testIngredient5, 0);
	Ingredient b1 = facade.getIngredient(0);
	auto a1 = facade.getAllIngredient();

	facade.addRecipe(&testRecipe1);
	facade.addRecipe(&testRecipe2);
	facade.saveRecipe(&testRecipe3,0);
	Recipe b2 = facade.getRecipe(0);
	auto a2 = facade.getAllRecipe();

	return;*/
}


void initDb()
{

	double tab1[7] = { 1,2,3,4,5,6,7 };
	double tab2[7] = { 11,12,13,14,15,16,17 };
	double tab3[7] = { 21,22,23,24,25,26,27 };
	double tab4[7] = { 31,32,33,34,35,36,37 };
	double tab5[7] = { 1,2,3,4,5,6,7 };
	double tab6[7] = { 11,12,13,14,15,16,17 };
	double tab7[7] = { 21,22,23,24,25,26,27 };
	double tab8[7] = { 31,32,33,34,35,36,37 };
	double tab9[7] = { 1,2,3,4,5,6,7 };
	double tab10[7] = { 11,12,13,14,15,16,17 };
	double tab11[7] = { 21,22,23,24,25,26,27 };
	double tab12[7] = { 31,32,33,34,35,36,37 };

	InfoNutri testInfoNutri1 = InfoNutri(tab1, 7);
	InfoNutri testInfoNutri2 = InfoNutri(tab2, 7);
	InfoNutri testInfoNutri3 = InfoNutri(tab3, 7);
	InfoNutri testInfoNutri4 = InfoNutri(tab4, 7);
	InfoNutri testInfoNutri5 = InfoNutri(tab5, 7);
	InfoNutri testInfoNutri6 = InfoNutri(tab6, 7);
	InfoNutri testInfoNutri7 = InfoNutri(tab7, 7);
	InfoNutri testInfoNutri8 = InfoNutri(tab8, 7);
	InfoNutri testInfoNutri9 = InfoNutri(tab9, 7);
	InfoNutri testInfoNutri10 = InfoNutri(tab10, 7);
	InfoNutri testInfoNutri11 = InfoNutri(tab11, 7);
	InfoNutri testInfoNutri12 = InfoNutri(tab12, 7);


	Ingredient testIngredient1 = Ingredient("Carot", "Vegetable", "N/A", &testInfoNutri1);
	Ingredient testIngredient2 = Ingredient("Potato", "Vegetable", "N/A", &testInfoNutri2);
	Ingredient testIngredient3 = Ingredient("Apple", "Fruit", "N/A", &testInfoNutri3);
	Ingredient testIngredient4 = Ingredient("Wheat", "Grain", "N/A", &testInfoNutri4);
	Ingredient testIngredient5 = Ingredient("Pear", "Fruit", "N/A", &testInfoNutri5);
	Ingredient testIngredient6 = Ingredient("Quince", "Fruit", "N/A", &testInfoNutri6);
	Ingredient testIngredient7 = Ingredient("Water", "N/A", "N/A", &testInfoNutri7);
	Ingredient testIngredient8 = Ingredient("Olive Oil", "Oil", "N/A", &testInfoNutri8);
	Ingredient testIngredient9 = Ingredient("Butter", "Dairy", "N/A", &testInfoNutri9);
	Ingredient testIngredient10 = Ingredient("Red Meat", "Protein", "N/A", &testInfoNutri10);
	Ingredient testIngredient11 = Ingredient("Lentil", "Protein", "N/A", &testInfoNutri11);
	Ingredient testIngredient12 = Ingredient("Buckwheat", "Grain", "N/A", &testInfoNutri12);


	Aliment testAliment1 = Aliment(testIngredient1, 100); //Carot
	Aliment testAliment2 = Aliment(testIngredient2, 200); //Potato
	Aliment testAliment3 = Aliment(testIngredient3, 300); //Apple
	Aliment testAliment4 = Aliment(testIngredient4, 400); //Wheat
	Aliment testAliment5 = Aliment(testIngredient5, 100); //Pear


	StockedAliment testStockedAliment1 = StockedAliment(testIngredient1, 300, "2021-21-01", 185); //Carot
	StockedAliment testStockedAliment2 = StockedAliment(testIngredient2, 1500, "2021-22-01", 365); //Potato
	StockedAliment testStockedAliment3 = StockedAliment(testIngredient3, 3000, "2021-23-01", 30); //Apple
	StockedAliment testStockedAliment4 = StockedAliment(testIngredient4, 3500, "2021-24-01", 2000); //Wheat
	StockedAliment testStockedAliment5 = StockedAliment(testIngredient5, 1400, "2021-24-01", 57); //Pear


	std::forward_list<StockedAliment* > stockedAlimentList;
	stockedAlimentList.assign({ &testStockedAliment1,&testStockedAliment2,&testStockedAliment3,&testStockedAliment4 });


	Pantry testpantry1 = Pantry(stockedAlimentList);

	std::string testSteps1[] =
	{ "1 - Dice carots and potatoes",
		"2 - Boil them for ~20 minutes",
		"3 - After 20min, add the lentils and the meat to the soup",
		"4 - Let it cook for another 20min",
		"5 - Serve"
	};
	std::vector<std::string> strs(testSteps1, testSteps1 + sizeof(testSteps1) / sizeof(std::string));

	std::string testSteps2[] =
	{ "1 - Lorem ipsum dolor sit amet",
	  "2 - consectetur adipiscing elit ",
	  "3 - sed do eiusmod tempor incididunt"
	};
	std::vector<std::string> strs2(testSteps2, testSteps2 + sizeof(testSteps2) / sizeof(std::string));

	Recipe testRecipe1 = Recipe();
	testRecipe1.addAliment(testAliment1);
	testRecipe1.addAliment(testAliment2);
	//testRecipe1.addAliment(testAliment5);
	testRecipe1.setName("Recipe 1");
	testRecipe1.setNotes("Notes of Recipe1");
	testRecipe1.addStep(testSteps1[0]);
	testRecipe1.addStep(testSteps1[1]);
	testRecipe1.addStep(testSteps1[2]);
	testRecipe1.addStep(testSteps1[3]);
	testRecipe1.addStep(testSteps1[4]);
	testRecipe1.markAsComplete();

	Recipe testRecipe2 = Recipe();
	testRecipe2.addAliment(testAliment3);
	testRecipe2.addAliment(testAliment4);
	//testRecipe2.addAliment(testAliment5);
	testRecipe2.setName("Recipe 2");
	testRecipe2.setNotes("Notes of Recipe2");
	testRecipe2.markAsComplete();

	FacadeUserDB facade;

	facade.savePantry(&testpantry1);

	facade.saveIngredient(&testIngredient1, 0);
	facade.saveIngredient(&testIngredient2, 1);
	facade.saveIngredient(&testIngredient3, 2);
	facade.saveIngredient(&testIngredient4, 3);
	facade.saveIngredient(&testIngredient5, 4);
	facade.saveIngredient(&testIngredient6, 5);
	facade.saveIngredient(&testIngredient7, 6);
	facade.saveIngredient(&testIngredient8, 7);
	facade.saveIngredient(&testIngredient9, 8);
	facade.saveIngredient(&testIngredient10, 9);
	facade.saveIngredient(&testIngredient11, 10);
	facade.saveIngredient(&testIngredient12, 11);

	facade.resetRecipe();

	facade.saveRecipe(&testRecipe1, 0);
	facade.saveRecipe(&testRecipe2, 1);

	RecipeDBManager DBRecipe("stockDB/recipe.cdb");
	std::list<Recipe*> r;
	r = DBRecipe.getAllRecipe();

	Menu menu;
	std::time_t currentTime = std::time(nullptr);
	menu.setStartDate(currentTime);


	std::cout << menu.getStartDate();

	Pantry pantry;
	facade.getPantry(&pantry);
	pantry.setStock(stockedAlimentList);
	facade.savePantry(&pantry);
	std::forward_list<StockedAliment*> stockedAliment = pantry.getStock();

	std::list<Recipe*> recipesList;
	recipesList = facade.getAllRecipe();

	MenuGenerator menuGenerator;
	menuGenerator.setListRecipe(recipesList);
	menuGenerator.setStockedAliment(stockedAlimentList);

	struct tm date1 = { 0 };
	date1.tm_year = 2023 - 1900;
	date1.tm_mon = 3;
	date1.tm_mday = 10;
	date1.tm_hour = 12;
	date1.tm_min = 0;
	date1.tm_sec = 0;
	time_t t1 = mktime(&date1);

	struct tm date2 = { 0 };
	date2.tm_year = 2023 - 1900;
	date2.tm_mon = 3;
	date2.tm_mday = 20;
	date2.tm_hour = 12;
	date2.tm_min = 0;
	date2.tm_sec = 0;
	time_t t2 = mktime(&date2);

	double seconds = difftime(t2, t1);
	int days = seconds / (24 * 60 * 60);

	Menu newMenu = menuGenerator.generateMenu(1, 2, &pantry, facade);
	newMenu.writeMenu();
	//Menu newMenuBis = menuGenerator.generateOneTimeMeal(2, &pantry, facade);
	std::cout << "Fin.";
}