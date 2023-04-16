#pragma once
//#include "MenuGenerator.h"
//#include "Gardien.h"
#include <list>
#include<forward_list>
#include "Recipe.h"
#include "StockedAliment.h"

class Memento
{
private:
	std::list<Recipe*> listRecipe_;
	std::forward_list<StockedAliment*> stockedAliment_;

public:
	Memento(std::list<Recipe*> listRecipe, std::forward_list<StockedAliment*> stockedAliment) {
		this->listRecipe_ = listRecipe;
		this->stockedAliment_ = stockedAliment;
	}

	Memento(std::list<Recipe*> listRecipe) {
		this->listRecipe_ = listRecipe;
	}

	std::list<Recipe*> getListRecipe() const {
		return listRecipe_;
	}

	std::forward_list<StockedAliment*> getStockedAliment() const {
		return stockedAliment_;
	}
};
