#include "MenuGenerator.h"

MenuGenerator::MenuGenerator() {};

std::list<Recipe*> MenuGenerator::getListRecipe() {
	return this->_listRecipe;
}

void MenuGenerator::setListRecipe(std::list<Recipe*> listRecipe) {
	this->_listRecipe = listRecipe;
}

std::forward_list<StockedAliment*> MenuGenerator::getStockedAliment() {
	return this->_stockedAliment;
}

void MenuGenerator::setStockedAliment(std::forward_list<StockedAliment*> stockedAliment) {
	this->_stockedAliment = stockedAliment;
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
		std::vector<Aliment> aliments = (*it)->getAliments();
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
	std::vector<Aliment> alimentsRecipe = recipe.getAliments();
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

bool removeAnAlimentFromStockedAliment(Aliment alimentFromRecipe, Pantry* pantry, int numConsumers) {
	std::forward_list<StockedAliment*> stockedAliment = pantry->getStock();

	std::string name = alimentFromRecipe.getName();
	double mass = alimentFromRecipe.getMass() * numConsumers;
	for (auto it = (stockedAliment).begin(); it != (stockedAliment).end(); ++it) {
		std::string nameStocked = (*it)->getName();
		double massStocked = (*it)->getMass();
		if (nameStocked == name) {
			double diffMass = massStocked - mass;
			if (diffMass == 0) {
				pantry->removeFromStock(*it);
			}
			else {
				pantry->editFromStock(*it, diffMass);
			}
			return true;
		}
	}
	return false;
}

bool removeRecipe(std::list<Recipe*>* recipesList, std::list<double>* percentageMassEachRecipe, int indexRecipeToTake) {
	auto it = std::next((*recipesList).begin(), indexRecipeToTake);
	(*recipesList).erase(it);

	auto it2 = std::next((*percentageMassEachRecipe).begin(), indexRecipeToTake);
	(*percentageMassEachRecipe).erase(it2);

	return true;
}

bool removeRecipeWithoutPercentage(std::list<Recipe*>* recipesList, Recipe recipeToRemove) {
	int indexOfTheRecipeToRemove = 0;
	auto it = recipesList->begin();

	while (!(**it == recipeToRemove)) {
		indexOfTheRecipeToRemove++;
		it++;
	}

	it = std::next((*recipesList).begin(), indexOfTheRecipeToRemove);
	(*recipesList).erase(it);

	return true;
}

bool removeAllImpossibleRecipes(std::list<Recipe*>* recipesList, std::list<double>* percentageMassEachRecipe, std::forward_list<StockedAliment*> stockedAliment, int numConsumers) {
	int n = recipesList->size() - 1;
	int nImpossible = 0;
	while (n >= 0) {
		int end = recipesList->size();
		auto it = std::prev((*recipesList).end(), end - n);
		bool isPossible = checkRecipeIsPossible(**it, stockedAliment, numConsumers);
		std::cout << "n,";
		if (recipesList->size() == 1 && n == 0 && isPossible == false) {
			return false;
		}
		if (!isPossible) {
			removeRecipe(recipesList, percentageMassEachRecipe, n);
		}
		n--;
	}
	return true;
}

bool addRecipeToMenu(Menu* menu, Recipe recipeToTakeValue, std::list<Recipe*>* recipesList, std::list<double>* percentageMassEachRecipe,
	std::forward_list<StockedAliment*>* stockedAliment, int indexRecipeToTake, Pantry* p, int numConsumers) {

	bool isRecipeDelete = removeRecipe(recipesList, percentageMassEachRecipe, indexRecipeToTake);

	if (!isRecipeDelete)
		return false;

	std::vector<Aliment> alimentsRecipe = recipeToTakeValue.getAliments();
	for (auto it = alimentsRecipe.begin(); it != alimentsRecipe.end(); ++it) {
		bool isDelete = removeAnAlimentFromStockedAliment(*it, p, numConsumers);
		if (!isDelete) {
			return false;
		}
	}
	menu->addRecipe(recipeToTakeValue);
	return true;
}



Recipe getRandomRecipe(std::list<Recipe*> recipesList) {
	int n = recipesList.size();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, n - 1);
	auto it = recipesList.begin();
	std::advance(it, dis(gen));

	return **it;
}

bool removeStockedAliment(Recipe recipe, Pantry* pantry, int numConsumers) {
	std::vector<Aliment> alimentsRecipe = recipe.getAliments();
	for (auto it = alimentsRecipe.begin(); it != alimentsRecipe.end(); ++it) {
		bool isDelete = removeAnAlimentFromStockedAliment(*it, pantry, numConsumers);
		if (!isDelete) {
			return false;
		}
	}
	return true;
}

int fillTheRecipesWithPantry(Menu* menu, int numRecipesToAdd, int numConsumers, Pantry* pantry, std::list<Recipe*> recipesList) {
	std::forward_list<StockedAliment*> stockedAliment = pantry->getStock();

	//Memento mementoToRestore = gardien.getMemento(numMementoToTake);
	//recipesList = mementoToRestore.getListRecipe();

	int numRecipesAdd = 0;
	while (numRecipesAdd < numRecipesToAdd && recipesList.size() > 0) {
		Recipe recipeToTake = getRandomRecipe(recipesList);
		bool isRecipeGood = checkRecipeIsPossible(recipeToTake, stockedAliment, numConsumers);
		if (!isRecipeGood) {
			removeRecipeWithoutPercentage(&recipesList, recipeToTake);
		}
		else {
			menu->addRecipe(recipeToTake);
			removeStockedAliment(recipeToTake, pantry, numConsumers);
			numRecipesAdd++;
		}
	}
	return numRecipesAdd;
}

bool completeShoppingList(Menu* menu, Recipe recipeToAdd, std::forward_list<StockedAliment*>* stockedAliment, int numConsumers) {
	std::vector<Aliment> alimentForRecipe = recipeToAdd.getAliments();
	for (Aliment aliment : alimentForRecipe) {
		double newMass = aliment.getMass() * numConsumers;
		bool alimentInStockedAliment = false;
		for (auto it = stockedAliment->begin(); it != stockedAliment->end(); it++) {
			double massStocked = (*it)->getMass();
			if (aliment.getName() == (*it)->getName()) {
				if (massStocked >= aliment.getMass() * numConsumers) {
					newMass = massStocked - newMass;
					(*it)->setMass(newMass);
				}
				else {
					newMass = newMass - massStocked;
					(*it)->setMass(0);
					menu->putInShoppingList(aliment, newMass);
				}
				alimentInStockedAliment = true;
			}
		}
		if (alimentInStockedAliment == false) {
			menu->putInShoppingList(aliment, newMass);
		}
	}
	return true;
}

int fillTheRecipesWithShoppingList(Menu* menu, int numRecipesToAdd, int numConsumers, Pantry* pantry, std::list<Recipe*> recipesList) {
	//Memento mementoToRestore = gardien.getMemento(0);
	//std::list<Recipe*> recipesList = mementoToRestore.getListRecipe();

	std::forward_list<StockedAliment*> stockedAliment = pantry->getStock();

	int numRecipesAdd = 0;
	while (numRecipesToAdd > numRecipesAdd) {
		Recipe recipeToAdd = getRandomRecipe(recipesList);
		completeShoppingList(menu, recipeToAdd, &stockedAliment, numConsumers);
		menu->addRecipe(recipeToAdd);
		numRecipesAdd++;
	}

	return numRecipesAdd;
}

Menu MenuGenerator::generateMenu(int numDay, int numConsumers, Pantry* pantry, FacadeUserDB* facade) {
	Menu menu;
	menu.setNumConsumers(numConsumers);
	menu.setNbDays(numDay);

	std::forward_list<StockedAliment*> stockedAliment = pantry->getStock();
	std::list<Recipe*> recipesList;
	recipesList = facade->getAllRecipe();

	Gardien gardien;
	Memento firstMemento = this->createMemento();
	gardien.addMemento(firstMemento);

	double totalMassPantry = 0;
	for (auto it = stockedAliment.begin(); it != stockedAliment.end(); ++it) {
		totalMassPantry = totalMassPantry + (*it)->getMass();
	}
	std::list<double> percentageMassEachRecipe = getPercentageMassEachRecipe(recipesList, totalMassPantry);
	
	bool stillSomeRecipe = removeAllImpossibleRecipes(&recipesList, &percentageMassEachRecipe, stockedAliment, numConsumers);

	Memento memento = this->createMemento();
	gardien.addMemento(memento);

	int numRecipesOk = 0;
	while (recipesList.size() > 0 && numRecipesOk < numDay) {
		int indexRecipeToTake = getLessPercentageMassRecipe(percentageMassEachRecipe, recipesList);
		Recipe recipeToTakeValue = getRecipeToTake(recipesList, indexRecipeToTake);
		bool isRecipeGood = checkRecipeIsPossible(recipeToTakeValue, stockedAliment, numConsumers);

		if (!isRecipeGood) {
			removeRecipe(&recipesList, &percentageMassEachRecipe, indexRecipeToTake);
		}
		else {
			Memento memento = this->createMemento();
			gardien.addMemento(memento);
			addRecipeToMenu(&menu, recipeToTakeValue, &recipesList, &percentageMassEachRecipe, &stockedAliment, indexRecipeToTake, pantry, numConsumers);
			numRecipesOk++;
		}
	}

	int numRecipesToAdd = numDay - numRecipesOk;
	int recipesAdd = 0;

	if (numRecipesToAdd != 0) {
		Memento mementoToRestore = gardien.getMemento(1);
		this->restoreMemento(mementoToRestore);
		recipesList = this->getListRecipe();
		recipesAdd = fillTheRecipesWithPantry(&menu, numRecipesToAdd, numConsumers, pantry, recipesList);
	}

	if (recipesAdd != numRecipesToAdd) {
		std::cerr << "Nombre de repas ajout�s incoh�rents" << std::endl;
		//menu.setErrorMenu(true);
		numRecipesToAdd = numRecipesToAdd - recipesAdd;
		Memento mementoToRestore = gardien.getMemento(0);
		this->restoreMemento(mementoToRestore);
		recipesList = this->getListRecipe();
		fillTheRecipesWithShoppingList(&menu, numRecipesToAdd, numConsumers, pantry, recipesList);
	}

	std::cout << "L'�l�ment 3 de la liste est : " << std::endl;

	return menu;
}

Menu MenuGenerator::generateOneTimeMeal(int numConsumers, Pantry* pantry, FacadeUserDB* facade) {
	Menu menu = generateMenu(1, numConsumers, pantry, facade);
	return menu;
}

Memento MenuGenerator::createMemento() {
	std::cout << "Cr�ation d'un Memento pour la liste de recettes." << std::endl;
	return Memento(_listRecipe, _stockedAliment);
}

void MenuGenerator::restoreMemento(const Memento& memento) {
	_listRecipe = memento.getListRecipe();
	_stockedAliment = memento.getStockedAliment();
	std::cout << "Restauration de la liste de recettes pr�c�dente." << std::endl;
}