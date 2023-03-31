#pragma once
#include "Aliment.h"
#include "InfoNutri.h"
#include "NutritionalManager.h"
#include <set>
#include <vector>

//class NutritionalManager;


class Recipe
{
	private:
		bool isDraft = true;
		std::set <Aliment > aliments;
		std::vector<std::string> steps;
		std::string notes = "";
		float nutriScore;
		InfoNutri infoNutri;
		
		//friend InfoNutri NutritionalManager::setRecipeNutriInfos(Recipe *recipe);
		friend InfoNutri NutritionalManager::estimateNutriValue(const std::set<Aliment> aliments);
		friend float NutritionalManager::estimateNutriScore(InfoNutri infoNutri);

	public:
		Recipe();
		Recipe(std::set<Aliment>  aliments, std::vector<std::string> steps, std::string notes = "");
		Recipe(const Recipe& c);
		~Recipe();

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

		void evaluateNutriInfo();

		void markAsComplete();
		void markAsDraft();

		/*
		float getNutriScore() const;
		void setNutriScore(float nutriScore);

		InfoNutri getInfoNutri() const;
		void setInfoNutri(InfoNutri infoNutri);
		*/
};

