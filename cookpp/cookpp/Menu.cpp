#include "Menu.h"
#include "RecipeDBManager.h"

Menu::Menu() {
	this->startDate = NULL;
	this->endDate = NULL;
	this->numConsumers = 0;
	this->nbDays = 0;
	this->listRecipe = std::list <Recipe>();
	this->errorMenu = false;
}

Menu::Menu(time_t startDate, time_t endDate, int numConsumers) {
	this->startDate = startDate;
	this->endDate = endDate;
	this->numConsumers = numConsumers;
	this->listRecipe = std::list <Recipe>();
	this->errorMenu = false;
	double seconds = difftime(this->endDate, this->startDate);
	this->nbDays = seconds / (24 * 60 * 60);
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

int Menu::getNbDays() {
	return this->nbDays;
}
void Menu::setNbDays(int nbDays) {
	this->nbDays = nbDays;
}

std::list <Recipe > Menu::getListRecipe() {
	return this->listRecipe;
}

bool Menu::getErrorMenu() {
	return this->errorMenu;
}

void Menu::setErrorMenu(bool error) {
	this->errorMenu = error;
}

void Menu::printMenu() {
	std::cout << "Liste des recettes pour " << this->getNumConsumers() << " personnes sur " << this->getNbDays() << " jours :" << std::endl;
	int i = 1;
	std::list<Recipe> listRecipes = this->getListRecipe();
	std::list<Recipe> listRecipeWritten;

	for (Recipe recipe : listRecipes) {
		if (recipeAlreadyWritten(listRecipeWritten, recipe)) {
			break;
		}

		listRecipeWritten.push_back(recipe);
		int occur = getNbOccurOfRecipe(this, recipe);
		std::cout << "Recette " << i << " (x" << occur << ")" << std::endl;

		std::cout << "Ingr�dients :" << std::endl;
		std::vector<Aliment> aliments = recipe.getAliments();
		for (Aliment aliment : aliments) {
			std::cout << " - " << aliment.getName() << " " << aliment.getMass() * this->getNumConsumers() << "g" << std::endl;
		}

		std::cout << "Etapes :" << std::endl;
		std::vector< std::string > steps = recipe.getSteps();
		//int n = 1;
		for (std::string step : steps) {
			std::cout << step << std::endl;
		}

		std::cout << std::endl;
		i++;
	}
}

void Menu::writeMenu() {
	std::ofstream fichier("recettes.txt");

	if (!fichier) {
		std::cerr << "Erreur : impossible d'ouvrir le fichier en �criture" << std::endl;
	}

	fichier << "Liste des recettes pour " << this->getNumConsumers() << " personnes sur " << this->getNbDays() << " jours :" << std::endl;
	int i = 1;
	std::list<Recipe> listRecipes = this->getListRecipe();
	std::list<Recipe> listRecipeWritten;

	for (Recipe recipe : listRecipes) {
		if (recipeAlreadyWritten(listRecipeWritten, recipe)) {
			break;
		}

		listRecipeWritten.push_back(recipe);
		int occur = getNbOccurOfRecipe(this, recipe);
		fichier << "Recette " << i << " (x" << occur << ")" << std::endl;

		fichier << "Ingr�dients :" << std::endl;
		std::vector<Aliment> aliments = recipe.getAliments();
		for (Aliment aliment : aliments) {
			fichier << " - " << aliment.getName() << " " << aliment.getMass() * this->getNumConsumers() << "g" << std::endl;
		}

		fichier << "Etapes :" << std::endl;
		std::vector< std::string > steps = recipe.getSteps();
		//int n = 1;
		for (std::string step : steps) {
			fichier << step << std::endl;
		}

		fichier << std::endl;
		i++;
	}

	fichier.close();
}