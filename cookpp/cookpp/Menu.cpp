#include "Menu.h"
#include "RecipeDBManager.h"

Menu::Menu() {
	this->startDate = NULL;
	this->endDate = NULL;
	this->numConsumers = 0;
	this->listRecipe = std::list <Recipe>();
}

Menu::Menu(time_t startDate, time_t endDate, int numConsumers) {
	this->startDate = startDate;
	this->endDate = endDate;
	this->numConsumers = numConsumers;
	this->listRecipe = std::list <Recipe>();
}


void Menu::addRecipe(Recipe recipe) {
	this->listRecipe.push_back(recipe);
}

void Menu::removeRecipe(Recipe recipe) {
	for (auto it = this->listRecipe.begin(); it != this->listRecipe.end(); ++it) {
		if (*it == recipe) {
			this->listRecipe.erase(it);
			break;
		}
	}
}

time_t Menu::getStartDate() {
	return this->startDate;
}

void Menu::setStartDate(time_t startDate) {
	this->startDate = startDate;
}

time_t Menu::getEndDate() {
	return this->endDate;
}
void Menu::setEndDate(time_t endDate) {
	this->endDate = endDate;
}
int Menu::getNumConsumers() {
	return this->numConsumers;
}
void Menu::setNumConsumers(int numConsumers) {
	this->numConsumers = numConsumers;
}

//std::string* Menu::printMenu() { ; }
void Menu::printMenu() { ; }
