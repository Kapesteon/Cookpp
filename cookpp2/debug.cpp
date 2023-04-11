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


#include <QtCore/QCoreApplication> 
#include <qfile> 
#include <qcryptographichash.h> 
#include <iostream> 

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

	//Pantry pantry = Pantry();
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
	//testRecipe3.setSteps(strs);
	testRecipe3.addStep("6f");
	testRecipe3.addStep("7g");
	//testRecipe3.removeLastStep();
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

	file.open("stockDB/debug.cdb", std::ios::in | std::ios::out | std::ios::binary);
	file.write((char*)&testInfoNutri5, sizeof(InfoNutri));
	file.write((char*)&testInfoNutri4, sizeof(InfoNutri));
	file.seekp(0, std::ios::beg);
	file.read((char*)&testInfoNutri1, sizeof(InfoNutri));
	file.seekg(1*sizeof(InfoNutri), std::ios::beg);
	file.read((char*)&testInfoNutri2, sizeof(InfoNutri));
	
	file.close();
	*/

	/* 
	//Does not cause issues, even tho seekp is used instead of seekg ! weird
	std::fstream dbIngredients;

	dbIngredients.open("stockDB/debug.cdb", std::ios::in | std::ios::out | std::ios::binary);
	dbIngredients.write((char*)&testIngredient5, sizeof(Ingredient));
	dbIngredients.write((char*)&testIngredient4, sizeof(Ingredient));
	dbIngredients.seekp(0, std::ios::beg);
	dbIngredients.read((char*)&testIngredient1, sizeof(Ingredient));
	dbIngredients.seekp(1*sizeof(Ingredient), std::ios::beg);
	dbIngredients.read((char*)&testIngredient1, sizeof(Ingredient));

	dbIngredients.close();
	*/

	//No issue
	std::fstream file2;
	file2.open("stockDB/debug.cdb", std::ios::in | std::ios::out | std::ios::binary);
	file2.write((char*)&testAliment6, sizeof(Aliment));
	file2.write((char*)&testAliment5, sizeof(Aliment));
	file2.seekp(0, std::ios::beg);
	file2.read((char*)&testAliment1, sizeof(Aliment));
	file2.seekg(1 * sizeof(Aliment), std::ios::beg);
	file2.read((char*)&testAliment1, sizeof(Aliment));
	file2.close();
	

	//No issue
	std::fstream dbRecipe;
	dbRecipe.open("stockDB/recipe.cdb", std::ios::in | std::ios::out | std::ios::binary);
	dbRecipe.write((char*)&testRecipe2, sizeof(Recipe));
	dbRecipe.write((char*)&testRecipe3, sizeof(Recipe));
	dbRecipe.seekp(0, std::ios::beg);
	dbRecipe.read((char*)&testRecipe1, sizeof(Recipe));
	dbRecipe.seekg(1 * sizeof(Recipe), std::ios::beg);
	dbRecipe.read((char*)&testRecipe1, sizeof(Recipe));
	dbRecipe.close();
	
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



	
	RecipeDBManager DBRecipe("stockDB/recipe.cdb");
	//DBRecipe.append(&testRecipe2);
	//DBRecipe.append(&testRecipe3);
	DBRecipe.read(&testRecipe1, 1);
	DBRecipe.read(&testRecipe1, 2);
	std::list<Recipe *> r1;
	r1.push_back(&testRecipe1);
	r1 = DBRecipe.getAllRecipe();
	
	

	FacadeUserDB facade;

	IngredientDBManager DBIngredient("stockDB/ingredient.cdb");
	Ingredient * testIngredient0 = new Ingredient();
	//DBIngredient.write(&testIngredient2,0);
	//DBIngredient.write(&testIngredient3, 1); 
	///DBIngredient.append(&testIngredient4);
	DBIngredient.read(testIngredient0, 0);
	DBIngredient.read(testIngredient0, 1);
	//--------------------------------------
	facade.saveIngredient(&testIngredient2, 0);
	facade.saveIngredient(&testIngredient3, 1);
	DBIngredient.read(&testIngredient1, 0);
	DBIngredient.read(&testIngredient1, 1);
	//std::list<Ingredient*> r;
	//r = DBIngredient.getAllIngredient();




	std::cout << testInfoNutri1;
	std::cout << testIngredient1;


	//FacadeUserDB facade;

	facade.savePantry(&pantry2);
	facade.getPantry(&pantry2);

	facade.addIngredient(&testIngredient1);
	facade.addIngredient(&testIngredient2);
	facade.addIngredient(&testIngredient3);
	facade.saveIngredient(&testIngredient5, 0);
	Ingredient b1 = facade.getIngredient(0);
	Ingredient b2 = facade.getIngredient(0);
	Ingredient b3 = facade.getIngredient(0);
	Ingredient b4 = facade.getIngredient(0);
	auto a1 = facade.getAllIngredient();

	facade.addRecipe(&testRecipe1);
	facade.addRecipe(&testRecipe2);
	facade.saveRecipe(&testRecipe3,0);
	//facade.getRecipe(&testRecipe1,0);
	//auto a2 = facade.getAllRecipe();


	/*
	NOTES :
	Try to use as little heap memory as possible, bug occurs when calling destructors of object sharing multiple instances 
	(2 recipes sharing the same ingredient causes issue)
	*/
	return;
}

void initDb()
{
	//keys = { "perAmount", "calories","fat","cholesterol","sodium","carbohydrate","protein" };
	double tab1[7] = { 100,41,0.2,0,0.070,10,0.9 }; //Carot
	double tab2[7] = { 100,77,0.1,0,0.006,17,2 }; //Potato
	double tab3[7] = { 100,52,0.2,0,0.001,14,0.3 }; //Apple
	double tab4[7] = { 100,360,1,0,0.002,76,10.3 }; //Wheat
	double tab5[7] = { 100,57,0.1,0,0.001,15,0.4 }; //Pear
	double tab6[7] = { 100,60,0.1,0,0.004,15,14 }; //Quince
	double tab7[7] = { 100,0,0,0,0.004,0,0 }; //Water
	double tab8[7] = { 100,884,100,0,0.002,0,0 }; //Olive Oil
	double tab9[7] = { 100,717,81,0.215,0.642,0.1,0.9 }; //Butter
	double tab10[7] = { 100,259,17,0.087,0.050,0,26 }; //Red Meat
	double tab11[7] = { 100,116,0.4,0,0.002,20,9 }; //Lentil
	double tab12[7] = { 100,92,0.6,0,0.004,20,3.4 }; //Buckwheat

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


	Aliment testAliment1 = Aliment(testIngredient1, 50); //Carot
	Aliment testAliment2 = Aliment(testIngredient2, 50); //Potato
	Aliment testAliment3 = Aliment(testIngredient3, 300); //Apple
	Aliment testAliment4 = Aliment(testIngredient4, 400); //Wheat
	Aliment testAliment5 = Aliment(testIngredient5, 100); //Peer
	Aliment testAliment6 = Aliment(testIngredient6, 200); //Quince
	Aliment testAliment7 = Aliment(testIngredient7, 200); //Water
	Aliment testAliment8 = Aliment(testIngredient8, 10); //Olive Oil
	Aliment testAliment9 = Aliment(testIngredient9, 100); //Butter
	Aliment testAliment10 = Aliment(testIngredient10, 200); //Red Meat
	Aliment testAliment11 = Aliment(testIngredient11, 150); //Lentil
	Aliment testAliment12 = Aliment(testIngredient10, 400); //Buckwheat


	StockedAliment testStockedAliment1 = StockedAliment(testIngredient1, 1000, "2021/04/13", 185); //Carot
	StockedAliment testStockedAliment2 = StockedAliment(testIngredient2, 1500, "2021/05/14", 365); //Potato
	StockedAliment testStockedAliment3 = StockedAliment(testIngredient3, 2000, "2021/06/15", 30); //Apple
	StockedAliment testStockedAliment4 = StockedAliment(testIngredient4, 2500, "2021/07/16", 2000); //Wheat


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
	testRecipe1.addAliment(testAliment8);
	testRecipe1.addAliment(testAliment11);
	testRecipe1.addAliment(testAliment7);
	testRecipe1.setName("Lentil Soup");

	testRecipe1.addStep(testSteps1[0]);
	testRecipe1.addStep(testSteps1[1]);
	testRecipe1.addStep(testSteps1[2]);
	testRecipe1.addStep(testSteps1[3]);
	testRecipe1.addStep(testSteps1[4]);

	testRecipe1.setNotes("Notes of Recipe1");
	testRecipe1.markAsComplete();

	Recipe testRecipe2 = Recipe();
	testRecipe2.addAliment(testAliment3);
	testRecipe2.addAliment(testAliment5);
	testRecipe2.addAliment(testAliment6);
	testRecipe2.setName("Fruit Salad");
	testRecipe2.addStep(testSteps2[0]);
	testRecipe2.addStep(testSteps2[1]);
	testRecipe2.addStep(testSteps2[2]);
	testRecipe2.setNotes("Notes of Recipe2");
	testRecipe2.markAsComplete();

	FacadeUserDB facade;
	IngredientDBManager DBIngredient("stockDB/ingredient.cdb");

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

	facade.saveRecipe(&testRecipe1, 0);
	facade.saveRecipe(&testRecipe2, 1);
}






void debugA(IngredientDBManager* DBIngredient, Ingredient* testIngredient0)
{

	//BUG : READING OUTSIDE OF SCOPE OF WHEN IT WAS WRITTEN RETURN INVALID DATA (especially InfoNutri)
	// Exact : https://cplusplus.com/forum/general/44719/

	double tab1[7] = { 1,2,3,4,5,6,7 };
	double tab2[7] = { 11,12,13,14,15,16,17 };
	double tab3[7] = { 21,22,23,24,25,26,27 };
	InfoNutri testInfoNutri1 = InfoNutri(tab1, 7);
	InfoNutri testInfoNutri2 = InfoNutri(tab2, 7);
	InfoNutri testInfoNutri3 = InfoNutri(tab3, 7);
	Ingredient testIngredient1 = Ingredient("Carot", "Vegetable", "N/A", &testInfoNutri1);
	Ingredient testIngredient2 = Ingredient("Potato", "Vegetable", "N/A", &testInfoNutri2);
	Ingredient testIngredient3 = Ingredient("Apple", "Fruit", "N/A", &testInfoNutri3);

	FacadeUserDB facade;
	//IngredientDBManager DBIngredient("stockDB/ingredient.cdb");
	//Ingredient* testIngredient0 = new Ingredient();
	InfoNutri * testInfoNutri0 = new InfoNutri();


	DBIngredient->write(&testIngredient1,0);
	DBIngredient->write(&testIngredient2, 1); 


		
	std::fstream file;



	file.open("stockDB/debug.cdb", std::ios::in | std::ios::out | std::ios::binary);
	file.write((char*)&testInfoNutri1, sizeof(InfoNutri));

	file.close();

	file.open("stockDB/debug.cdb", std::ios::in | std::ios::out | std::ios::binary);
	file.seekg(0, std::ios::beg);
	file.read((char*)testInfoNutri0, sizeof(InfoNutri));

	file.close();
	
	std::cout << *testInfoNutri0;



	//facade.saveIngredient(&testIngredient1, 0);
    //facade.saveIngredient(&testIngredient2, 1);
	//Ingredient a = facade.getIngredient(0);
	//Ingredient b = facade.getIngredient(1);
}






void debugB(IngredientDBManager* DBIngredient, Ingredient* testIngredient0)
{

	FacadeUserDB facade;
	//IngredientDBManager * DBIngredient = new IngredientDBManager("stockDB/ingredient.cdb");


	InfoNutri* testInfoNutri0 = new InfoNutri();






	/*
	std::ifstream in("stockDB/debug.cdb");
	std::streambuf* cinbuf = std::cin.rdbuf(); //save old buf
	std::cin.rdbuf(in.rdbuf()); //redirect std::cin to stockDB/debug.cdb
	*/

	//std::ifstream cin("stockDB/debug.cdb");
	//std::ofstream cout("stockDB/debug.cdb");

	//std::cout << *testInfoNutri0;
	//std::cin >> *testInfoNutri0;


	std::fstream file;
	file.open("stockDB/debug.cdb", std::ios::in | std::ios::out | std::ios::binary);
	file.seekg(0, std::ios::beg);
	file.read((char*)testInfoNutri0, sizeof(InfoNutri));
	//file.seekg(1 * sizeof(InfoNutri), std::ios::beg);
	//file.read((char*)testInfoNutri0, sizeof(InfoNutri));

	file.close();

	/*
	DBIngredient->read(testIngredient0, 0);
	std::cout << testIngredient0->getName();
	std::cout << std::endl;
	std::cout << testIngredient0->getType();
	std::cout << std::endl;
	std::cout << testIngredient0->getSeason();
	std::cout << std::endl;
	std::cout << testIngredient0->getInfoNutri();
	std::cout << std::endl;

	DBIngredient->read(testIngredient0, 1);

	std::cout << testIngredient0->getName();
	std::cout << std::endl;
	std::cout << testIngredient0->getType();
	std::cout << std::endl;
	std::cout << testIngredient0->getSeason();
	std::cout << std::endl;
	std::cout << testIngredient0->getInfoNutri();
	std::cout << std::endl;
	*/


	Ingredient a = facade.getIngredient(0);
	Ingredient b = facade.getIngredient(1);
}




/* get hash  	//https://www.quora.com/How-can-I-get-the-MD5-or-SHA-hash-of-a-file-in-C


	QFile myFile("C:/ISEN/M2/ProgObj/projFinal/Cookpp2/cookpp2/cookpp2/stockDB/ingredient.cdb");
	myFile.open(QIODevice::ReadOnly);

	QByteArray fileData = myFile.readAll(); //207E9B56724944A171CC273E49B77D46
	myFile.close();
	QString hash = QString(QCryptographicHash::hash((fileData),
		QCryptographicHash::Md5).toHex()).toUpper();
	std::cout << "The Md5 hash of your file is: " << hash.toStdString()
		<< std::endl;


*/