#pragma once
#include "Aliment.h"
#include "InfoNutri.h"
#include "NutritionalManager.h"
#include <set>
#include <vector>
#include <list>

//class NutritionalManager;


class Recipe
{
	private:
		std::string name;
		std::set <Aliment > aliments;
		std::vector<std::string> steps;
		std::string notes = "";
		float nutriScore;
		InfoNutri infoNutri;
		bool isDraft = true;
		
		//friend InfoNutri NutritionalManager::setRecipeNutriInfos(Recipe *recipe);
		friend InfoNutri NutritionalManager::estimateNutriValue(const std::set<Aliment> aliments);
		friend float NutritionalManager::estimateNutriScore(InfoNutri infoNutri);

	public:
		Recipe();
		Recipe(std::string name, std::set<Aliment>  aliments, std::vector<std::string> steps, std::string notes = "");
		Recipe(const Recipe& c);
		~Recipe();

		void setName(std::string name);
		std::string getName() const;

		std::set<Aliment >  getAliments() const;
		void setAliments(std::set< Aliment >  aliments);
		void addAliment(Aliment aliment);
		//void addAliment(std::string name);
		void removeAliment(Aliment aliment);
		//void removeAliment(std::string name);

		std::vector<std::string> getSteps() const;
		void setSteps(std::vector<std::string> steps);
		void addStep(std::string step);
		void removeLastStep();

		std::string getNotes() const;
		void setNotes(std::string notes);
		
		float getNutriScore() const;
		InfoNutri getInfoNutri() const;
		bool getIsDraft() const;

		void evaluateNutriInfo();

		int markAsComplete();
		void markAsDraft();

		friend std::istream& operator>>(std::istream& is, Recipe& in);
		friend std::ostream& operator<<(std::ostream& os, const Recipe& in);

		Recipe operator<(const Recipe& s) const;
		int operator==(const Recipe& s) const;
};

