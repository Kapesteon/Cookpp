#define NOMINMAX //prevents a bug with min()
#include "NutritionalManager.h"
#include <cmath>
#define NBR_ATTR_INFONUTRI 7
#define RECOMMENDED_calories  800
#define RECOMMENDED_fat	65
#define RECOMMENDED_cholesterol 0.3
#define RECOMMENDED_sodium 2.4 
#define RECOMMENDED_carbohydrate 300
#define RECOMMENDED_protein 20
//https://www.canada.ca/en/health-canada/services/understanding-food-labels/percent-daily-value.html
#define UNHEALTHY_PERCENT_STEP_THRESHOLD 5  
#define AMOUNT_STEP_BEFORE_FULLY_UNHEALTHY 3
#define MIN_NUTRISCORE 0
#define MAX_NUTRISCORE 100

NutritionalManager::NutritionalManager() {
	std::vector<double> values{ 
		-1,
		RECOMMENDED_calories,
		RECOMMENDED_fat, 
		RECOMMENDED_cholesterol ,
		RECOMMENDED_sodium, 
		RECOMMENDED_carbohydrate,
		RECOMMENDED_protein };
	this->recommendedPerMealAmount = InfoNutri(values);
	this->percentThresholdUnhealthy = UNHEALTHY_PERCENT_STEP_THRESHOLD;
	//Represents how many +- percent difference in recipe can be tolerated before being unhealthy
	this->amountStepBeforeFullyUnhealty = AMOUNT_STEP_BEFORE_FULLY_UNHEALTHY;
	//Represents how many times it is allowed to exceed the threshold before it is considered fully unhealthy
}

NutritionalManager * NutritionalManager::getSingleton()
{
	if (!singleton)
		singleton = new NutritionalManager;
	return singleton;
}


InfoNutri NutritionalManager::estimateNutriValue(const std::set<Aliment> aliments)
{
	std::map < std::string, double> returnValues;
	//std::vector<double> returnValues(NBR_ATTR_INFONUTRI, 0);
	double perAmount = 0;
	double mass = 0;
	int i = 0;
	auto itr = aliments.begin();
	while (itr != aliments.end()) {
		try {
			auto values = (*itr).getInfoNutri().getNutriValues();
			double perAmount = values.at("perAmount");
			mass = (*itr).getMass();
			double ratio = (mass / perAmount);
			
			i = 0;
			auto itr2 = values.begin();
			while (i < NBR_ATTR_INFONUTRI || itr2 != values.end()) {
				returnValues[(*itr2).first] = ((*itr2).second * ratio) + returnValues[(*itr2).first];
				itr2++;
				i++;
			}


		}
		catch (std::runtime_error) {
			if (perAmount == 0) {
				std::cout << "Math Error : Division by 0 \n NutritionalManager";
				OutputDebugStringA("Math Error : Division by 0 \n NutritionalManager");
			}
		}
		catch(std::exception)
		{
			throw(exception_code);
		}
		
		itr++;
	}
	return InfoNutri(returnValues);
}

float NutritionalManager::estimateNutriScore(InfoNutri infoNutri)
{
	auto values = infoNutri.getNutriValues();
	auto recValues = this->recommendedPerMealAmount.getNutriValues();
	double scale = MAX_NUTRISCORE - MIN_NUTRISCORE;
	double diffPercent = 0;
	double scalingFactor = scale / (NBR_ATTR_INFONUTRI - 1); //-1 to disregard the perAmount
	double stepScoreIncrement = scalingFactor / this->amountStepBeforeFullyUnhealty;
	double nutriScore = MAX_NUTRISCORE;
	double currentNutriScore = 0;
	int i = 0;


	//No try catch : https://cplusplus.com/reference/map/map/erase/
	//maps are Exception safe with .erase()
	values.erase("perAmount");
	recValues.erase("perAmount");

	if (values.size() != recValues.size()) {
		return MIN_NUTRISCORE-1;
	}
	else {
		try {

		
			auto itr = values.begin();
			auto itr2 = recValues.begin();
			for (itr; itr != values.end(); itr++) {
				diffPercent = abs(((*itr).second / (*itr2).second) - 1) * 100;
				currentNutriScore = std::floor(diffPercent / this->percentThresholdUnhealthy) * stepScoreIncrement;
				currentNutriScore = std::min(currentNutriScore, scalingFactor);
				nutriScore -= currentNutriScore;
				itr2++;
			}
		}
		catch (std::exception) {
			std::cout << "Couldn't mark recipe as complete";
			OutputDebugStringA("Couldn't mark recipe as complete");
			return -1.0f;
		}
		
	}
	return nutriScore;
}


//Initialize pointer to zero so that it can be initialized in first call to getInstance
NutritionalManager* NutritionalManager::singleton = 0;


