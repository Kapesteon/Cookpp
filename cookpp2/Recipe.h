#pragma once
#include "Aliment.h"
#include "InfoNutri.h"
#include "NutritionalManager.h"

#include <set>
#include <vector>
#include <array>
//class NutritionalManager;

//std::array<double, NUMBER_ATRIBUTES>
class Recipe
{
	private:
		std::string name;
		float nutriScore;
		std::string notes = "";
		std::vector<std::string> steps;
		InfoNutri infoNutri;
		std::vector <Aliment > aliments;
		bool isDraft = true;


		
		//friend InfoNutri NutritionalManager::setRecipeNutriInfos(Recipe *recipe);
		friend InfoNutri NutritionalManager::estimateNutriValue(const std::vector<Aliment> aliments);
		friend float NutritionalManager::estimateNutriScore(InfoNutri infoNutri);

	public:
		Recipe();
		Recipe(std::string name, std::vector<Aliment>  aliments, std::vector<std::string> steps, std::string notes = "");
		Recipe(const Recipe& c);
		~Recipe();

		void setName(std::string name);
		std::string getName() const;

		std::vector<Aliment >  getAliments() const;
		void setAliments(std::vector< Aliment >  aliments);
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
};

