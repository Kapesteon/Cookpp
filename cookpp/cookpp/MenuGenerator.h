#pragma once
#include "Menu.h"
#include "Recipe.h"
#include "Pantry.h"
#include "RecipeDBManager.h"
#include "FacadeUserDB.h"
#include <algorithm>
#include <random>
#include "Memento.h"
#include "Gardien.h"

class MenuGenerator
{
private:
	std::list <Recipe*> _listRecipe;
	std::forward_list<StockedAliment*> _stockedAliment;

public:
	MenuGenerator();

	std::list<Recipe*> getListRecipe();
	void setListRecipe(std::list<Recipe*> listRecipe);
	std::forward_list<StockedAliment*> getStockedAliment();
	void setStockedAliment(std::forward_list<StockedAliment*> stockedAliment);


	Menu generateMenu(int numDay, int numConsumers, Pantry* pantry, FacadeUserDB facade);
	Menu rerollMenu(Menu menu, Pantry pantry);
	Menu generateOneTimeMeal(Pantry pantry);
};