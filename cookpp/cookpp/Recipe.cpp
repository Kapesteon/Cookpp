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
	return std::set< Aliment>();
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

std::string Recipe::getNotes() const
{
	return this->notes;
}

void Recipe::setNotes(std::string notes)
{
	this->notes = notes;
}
