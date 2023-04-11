#pragma once
#include "Recipe.h"

class Menu
{
	private:
		time_t startDate;
		time_t endDate;
		int numConsumers;
		std::list <Recipe > listRecipe;

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

		//std::string* printMenu();
		void printMenu();
};