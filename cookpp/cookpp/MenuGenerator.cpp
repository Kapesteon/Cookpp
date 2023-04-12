#include "MenuGenerator.h"

MenuGenerator::MenuGenerator() {};

std::forward_list<StockedAliment*> MenuGenerator::getStockedAliment() {
	return this->stockedAliment;
}

int getLessPercentageMassRecipe(std::list<double> percentageMassEachRecipe, std::list<Recipe*> recipesList) {
	double getLessPercentageMassRecipe = 1.00;
	int indexRecipeToTake = 0;
	int i = 0;
	for (auto it = percentageMassEachRecipe.begin(); it != percentageMassEachRecipe.end(); ++it) {
		if (getLessPercentageMassRecipe > *it) {
			getLessPercentageMassRecipe = *it;
			indexRecipeToTake = i;
		}
		i++;
	}
	return indexRecipeToTake;
}

std::list<double> getPercentageMassEachRecipe(std::list<Recipe*> recipesList, double totalMassPantry) {
	std::list<double> percentageMassEachRecipe;

	for (auto it = recipesList.begin(); it != recipesList.end(); ++it) {
		std::set<Aliment > aliments = (*it)->getAliments();
		double massAliments = 0;
		for (auto aliment = aliments.begin(); aliment != aliments.end(); ++aliment) {
			massAliments = massAliments + aliment->getMass();
		}
		double percentageMass = massAliments / totalMassPantry;
		percentageMassEachRecipe.push_back(percentageMass);
	}

	return percentageMassEachRecipe;
}

Recipe getRecipeToTake(std::list<Recipe*> recipesList, int indexRecipeToTake) {
	auto itRecipeToTake = recipesList.begin();
	if (indexRecipeToTake > 0) {
		std::advance(itRecipeToTake, indexRecipeToTake - 1);
	}
	Recipe* recipeToTake = *itRecipeToTake;
	Recipe recipeToTakeValue = *recipeToTake;

	return recipeToTakeValue;
}

bool checkRecipeIsPossible(Recipe recipe, std::forward_list<StockedAliment*> stockedAliment, int numConsumers) {
	std::set<Aliment > alimentsRecipe = recipe.getAliments();
	for (auto it = alimentsRecipe.begin(); it != alimentsRecipe.end(); ++it) {
		std::string name = it->getName();
		double mass = it->getMass() * numConsumers;
		
		bool found = false;
		for (auto itStocked = stockedAliment.begin(); itStocked != stockedAliment.end(); ++itStocked) {
			std::string nameStocked = (*itStocked)->getName();
			double massStocked = (*itStocked)->getMass();
			if (nameStocked == name) {
				if (massStocked >= mass) {
					found = true;
				}
				else {
					found = false;
				}
				break;
			}
		}

		if (found == false)
			return false;
	}
	return true;
}

bool removeAnAlimentFromStockedAliment(Aliment alimentFromRecipe, std::forward_list<StockedAliment*>* stockedAliment, Pantry p, int numConsumers) {
	std::string name = alimentFromRecipe.getName();
	double mass = alimentFromRecipe.getMass() * numConsumers;
	for (auto it = (*stockedAliment).begin(); it != (*stockedAliment).end(); ++it) {
		std::string nameStocked = (*it)->getName();
		double massStocked = (*it)->getMass();
		if (nameStocked == name) {
			double diffMass = massStocked - mass;
			p.removeFromStock(*it);
			(*it)->setMass(diffMass);
			p.addToStock(*it);
			return true;
		}
	}
	return false;
}

bool removeRecipe(Recipe recipeToTakeValue, std::list<Recipe*>* recipesList, std::list<double>* percentageMassEachRecipe, int indexRecipeToTake) {
	auto it = std::next((*recipesList).begin(), indexRecipeToTake);
	(*recipesList).erase(it);

	auto it2 = std::next((*percentageMassEachRecipe).begin(), indexRecipeToTake);
	(*percentageMassEachRecipe).erase(it2);

	return true;
}

bool addRecipeToMenu(Menu* menu, Recipe recipeToTakeValue, std::list<Recipe*>* recipesList, std::list<double>* percentageMassEachRecipe,
	std::forward_list<StockedAliment*>* stockedAliment, int indexRecipeToTake, Pantry p, int numConsumers) {

	bool isRecipeDelete = removeRecipe(recipeToTakeValue, recipesList, percentageMassEachRecipe, indexRecipeToTake);

	if (!isRecipeDelete)
		return false;

	std::set<Aliment > alimentsRecipe = recipeToTakeValue.getAliments();
	for (auto it = alimentsRecipe.begin(); it != alimentsRecipe.end(); ++it) {
		bool isDelete = removeAnAlimentFromStockedAliment(*it, stockedAliment, p, numConsumers);
		if (!isDelete) {
			return false;
		}
	}
	menu->addRecipe(recipeToTakeValue);
	return true;
}

Menu MenuGenerator::generateMenu(int numDay, int numConsumers, Pantry pantry, FacadeUserDB facade) {
	Menu menu;
	menu.setNumConsumers(numConsumers);

	//Pantry pantry2 = facade.getPantry();

	std::forward_list<StockedAliment*> stockedAliment = pantry.getStock();

	//RecipeDBManager DBRecipe("stockDB/recipe.cdb");
	std::list<Recipe*> recipesList;
	//recipesList = DBRecipe.getAllRecipe();

	recipesList = facade.getAllRecipe();

	double totalMassPantry = 0;
	for (auto it = stockedAliment.begin(); it != stockedAliment.end(); ++it) {
		totalMassPantry = totalMassPantry + (*it)->getMass();
	}
	std::list<double> percentageMassEachRecipe = getPercentageMassEachRecipe(recipesList, totalMassPantry);

	for (int i = 0; i < numDay; i++) {
		int indexRecipeToTake = getLessPercentageMassRecipe(percentageMassEachRecipe, recipesList);
		Recipe recipeToTakeValue = getRecipeToTake(recipesList, indexRecipeToTake);
		bool isRecipeGood = checkRecipeIsPossible(recipeToTakeValue, stockedAliment, numConsumers);
		
		if (!isRecipeGood) {
			removeRecipe(recipeToTakeValue, &recipesList, &percentageMassEachRecipe, indexRecipeToTake);
		}
		else {
			addRecipeToMenu(&menu, recipeToTakeValue, &recipesList, &percentageMassEachRecipe, &stockedAliment, indexRecipeToTake, pantry, numConsumers);
		}
	}

	facade.removePantry();
	facade.putPantry();

	this->stockedAliment = stockedAliment;
	/*FacadeUserDB newFacade;

	Pantry newPantry = newFacade.getPantry();
	newPantry.setStock(stockedAliment);
	newFacade.savePantry(&newPantry);*/

	std::cout << "L'élément 3 de la liste est : " << std::endl;

	return menu;
}