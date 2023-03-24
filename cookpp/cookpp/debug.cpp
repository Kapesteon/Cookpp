#include "debug.h"
#include "InfoNutri.h"
#include "Windows.h"
#include "debugapi.h"

void debug()
{

	std::ostringstream;
	OutputDebugStringA("test");
	//InfoNutri* testInfoNutri2 = new InfoNutri();
	double tab[7] = { 52.1,98.5,100,258,48,987,10 };

	InfoNutri testInfoNutri1;
	InfoNutri testInfoNutri2 = InfoNutri(tab,7);
	InfoNutri testInfoNutri3 = InfoNutri(testInfoNutri2);

	auto e = testInfoNutri3.getInfoNutri();
	std::cout << "test";

	Ingredient testIngredient;
	Ingredient testIngredient2 = Ingredient("Carot", "Vegetable", "N/A", &testInfoNutri3);
	Ingredient testIngredient3 = Ingredient(testIngredient2);
	return;
}
