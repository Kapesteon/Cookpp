#pragma once
#include "InfoNutri.h"
#include "Aliment.h"
#include <set>

/*
class InfoNutri;
class Aliment;
*/

class NutritionalManager
{


	private:
		static NutritionalManager* singleton;
		InfoNutri recommendedPerMealAmount;

		double percentThresholdUnhealthy;
		double amountStepBeforeFullyUnhealty;
		NutritionalManager();

	public:
		static NutritionalManager* getSingleton();
		InfoNutri estimateNutriValue(const std::vector<Aliment> aliments);
		float estimateNutriScore(InfoNutri infoNutri);
		
		

};