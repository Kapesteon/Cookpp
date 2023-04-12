#pragma once
#include "Menu.h"
#include "Recipe.h"
#include "Pantry.h"
#include "RecipeDBManager.h"
#include "FacadeUserDB.h"
#include <algorithm>

class MenuGenerator
{
private:
	std::list <Recipe > listRecipe;
	std::forward_list<StockedAliment*> stockedAliment;

public:
	MenuGenerator();
	Menu generateMenu(int numDay, int numConsumers, Pantry pantry, FacadeUserDB facade);
	Menu rerollMenu(Menu menu, Pantry pantry);
	Menu generateOneTimeMeal(Pantry pantry);
	std::forward_list<StockedAliment*> getStockedAliment();
};