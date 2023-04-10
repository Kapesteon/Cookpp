#include "Recipe.h"
#define DELIMITER_KEY_VALUE_RECIPE '@' //For serialization //MUST BE ONE CHAR

Recipe::Recipe()
{
	this->name = "unknown";

	this->notes = "";
	this->nutriScore = -1;
	this->infoNutri = InfoNutri();
	this->aliments = std::vector <Aliment>();
	this->steps = std::vector<std::string>();
}

Recipe::Recipe(std::string name,std::vector<Aliment> aliments, std::vector<std::string> steps, std::string notes)
{
	this->name = name;
	this->aliments = aliments;
	this->steps = steps;
	this->notes = notes;
	this->nutriScore = -1;
	this->infoNutri = InfoNutri();
	this->evaluateNutriInfo();
}

Recipe::Recipe(const Recipe& c)
{
	this->name = c.name;
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

void Recipe::setName(std::string name)
{
	this->name = name;
}

std::string Recipe::getName() const
{
	return this->name;
}

std::vector<Aliment> Recipe::getAliments() const
{
	return this->aliments;
}

void Recipe::setAliments(std::vector<Aliment> aliments)
{
	this->aliments = aliments;

}

void Recipe::addAliment(Aliment aliment)
{
	this->aliments.push_back(aliment);

}



void Recipe::removeAliment(Aliment aliment)
{
	auto itr = this->getAliments().begin();

	for (itr; itr != this->getAliments().end(); itr++) {
		if ((*itr) == aliment) {
			this->aliments.erase(itr);
		}
	}


}



std::vector<std::string> Recipe::getSteps() const
{
	return this->steps;
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

float Recipe::getNutriScore() const
{
	return this->nutriScore;
}

InfoNutri Recipe::getInfoNutri() const
{
	return this->infoNutri;
}

bool Recipe::getIsDraft() const
{
	return this->isDraft;
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



std::istream& operator>>(std::istream& is, Recipe& in)
{

	is >> in.name;
	try {

		Aliment bufferA;
		std::string bufferS;
		//As long as the DELIMITER is not reached
		while (is.peek() != DELIMITER_KEY_VALUE_RECIPE) {
			is >> bufferA;
			in.addAliment(bufferA);
		}
		is.ignore(2,'\n'); //Ignore the delimiter

		while ((is.peek()) != DELIMITER_KEY_VALUE_RECIPE) {
			is >> bufferS;
			in.addStep(bufferS);
		}
		is.ignore(2, '\n');

	}
	catch (std::exception) {
		std::cout << "Couldn't recover Ingredient from database";
		OutputDebugStringA("Couldn't recover Ingredient from database");
		return is;
	}
	is >> in.notes;
	is >> in.infoNutri;
	is >> in.nutriScore;
	is >> in.isDraft;

	return is;

}

std::ostream& operator<<(std::ostream& os, const Recipe& in)
{

	os << in.getName()
		<< std::endl;
	try {
		// Serialize Aliments set
		std::vector<Aliment>::iterator itr;
		for (itr = in.getAliments().begin();
			itr != in.getAliments().end(); itr++)
		{
			os << *itr << std::endl;
		}
		os << DELIMITER_KEY_VALUE_RECIPE << std::endl;


		// Serialize Notes vector
		std::vector<std::string>::iterator itr2;
		for (itr2 = in.getSteps().begin();
			itr2 != in.getSteps().end(); itr++)
		{
			os << *itr2 << DELIMITER_KEY_VALUE_RECIPE;
		}
		os << std::endl;

		os << in.getNotes()
			<< std::endl
			<< in.getInfoNutri()
			<< std::endl
			<< in.getNutriScore()
			<< std::endl
			<< in.getIsDraft()
			<< std::endl;
	}
	catch (std::exception) {
		std::cout << "Couldn't save Recipe to database";
		OutputDebugStringA("Couldn't save Recipe to database");
		return os;
	}
	

	return os;


}

Recipe Recipe::operator<(const Recipe& s) const
{
	if (this == &s) return *this;
	if ((this->name) < (s.name)) {
		return s;
	}
	else {
		return *this;
	}
}