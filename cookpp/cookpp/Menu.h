#pragma once
#include "Recipe.h"
#include <list>

class Menu
{
	private:
		time_t startDate;
		time_t endDate;
		int numConsumers;
		int nbDays;
		std::list <Recipe> listRecipe;
		bool errorMenu;

		int getNbOccurOfRecipe(Menu* menu, Recipe recipeToCheck) {
			int occurr = 0;
			std::list<Recipe> listRecipe = menu->getListRecipe();
			for (auto it = listRecipe.begin(); it != listRecipe.end(); it++) {
				if (*it == recipeToCheck)
					occurr++;
			}
			return occurr;
		}

		bool recipeAlreadyWritten(std::list<Recipe> listRecipeWritten, Recipe recipeToCheck) {
			for (auto it = listRecipeWritten.begin(); it != listRecipeWritten.end(); it++) {
				if (*it == recipeToCheck)
					return true;
			}
			return false;
		}

	public:
		Menu();
		Menu(time_t startDate, time_t endDate, int numConsumers);

		void addRecipe(Recipe recipe);
		void removeRecipe(Recipe recipe);

		time_t getStartDate();
		void setStartDate(time_t startDate);
		time_t getEndDate();
		void setEndDate(time_t endDate);
		int getNumConsumers();
		void setNumConsumers(int numConsumers);
		int getNbDays();
		void setNbDays(int nbDays);
		std::list <Recipe> getListRecipe();
		bool getErrorMenu();
		void setErrorMenu(bool error);

		//std::string* printMenu();
		void printMenu();
		void writeMenu();
};