#include "Recipe.h"

Recipe::Recipe()
{

	this->aliments = std::set <Aliment>();
	this->steps = std::vector<std::string>();
	this->notes = "";
	this->nutriScore = -1;
	this->infoNutri = InfoNutri();
}

Recipe::Recipe(std::set<Aliment> aliments, std::vector<std::string> steps, std::string notes)
{
	this->aliments = aliments;
	this->steps = steps;
	this->notes = notes;
	this->nutriScore = -1;
	this->infoNutri = InfoNutri();
	this->evaluateNutriInfo();
}

Recipe::Recipe(const Recipe& c)
{
	this->aliments = c.aliments;
	this->steps = c.steps;
	this->notes = c.notes;
	this->nutriScore = c.nutriScore;
	this->infoNutri = c.infoNutri;
}

Recipe::~Recipe()
{
	OutputDebugStringA("Recipe Destroyed \n");
}

std::set<Aliment> Recipe::getAliments() const
{
	return this->aliments;
}

void Recipe::setAliments(std::set<Aliment> aliments)
{
	this->aliments = aliments;

}

void Recipe::addAliment(Aliment aliment)
{
	this->aliments.insert(aliment);

}



void Recipe::removeAliment(Aliment aliment)
{
	this->aliments.erase(aliment);

}



std::vector<std::string> Recipe::getSteps() const
{
	return std::vector<std::string>();
}

void Recipe::setSteps(std::vector<std::string> steps)
{
	this->steps = steps;
}

void Recipe::addStep(std::string step)
{
	this->steps.push_back(step);
}

void Recipe::removeLastStep()
{
	this->steps.pop_back();
}


std::string Recipe::getNotes() const
{
	return this->notes;
}

void Recipe::setNotes(std::string notes)
{
	this->notes = notes;
}

void Recipe::evaluateNutriInfo()
{
	NutritionalManager* n = n->getSingleton();
	this->infoNutri = n->estimateNutriValue(this->aliments);
	this->nutriScore = n->estimateNutriScore(this->infoNutri);
}

int Recipe::markAsComplete()
{
	try {
		this->isDraft = false;
		this->evaluateNutriInfo();
		return 0;
	}
	catch(std::exception){
		std::cout << "Couldn't mark recipe as complete";
		OutputDebugStringA("Couldn't mark recipe as complete");
		return -1;
	}
}

void Recipe::markAsDraft()
{
	this->isDraft = true;
}


/*
float Recipe::getNutriScore() const
{
	return this->nutriScore;
}

void Recipe::setNutriScore(float nutriScore)
{
	this->nutriScore = nutriScore;
}

InfoNutri Recipe::getInfoNutri() const
{
	return this->getInfoNutri();
}

void Recipe::setInfoNutri(InfoNutri infoNutri)
{
	this->infoNutri = infoNutri;
}
*/