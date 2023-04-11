#include "Recipe.h"
#define DELIMITER_KEY_VALUE_RECIPE '@' //For serialization //MUST BE ONE CHAR

Recipe::Recipe()
{
	this->name = "N/A";
	this->notes[0] = '\0';
	this->nutriScore = -1;
	this->infoNutri = InfoNutri();
	this->aliments = std::array <Aliment, MAX_ALIMENTS>();
	this->steps = std::array <char[256], MAX_STEPS>();
}

Recipe::Recipe(std::string name, std::array <Aliment, MAX_ALIMENTS> aliments, std::array <char[256], MAX_STEPS> steps, std::string notes)
{
	this->name = name;
	this->aliments = aliments;
	strcpy(this->notes, (notes.c_str()));
	//this->notes = notes;

	int i = 0;
	for (auto itr = steps.begin(); itr != steps.end(); itr++) {
		strcpy(this->steps[i], (*itr));
		i++;
	}

	this->nutriScore = -1;
	this->infoNutri = InfoNutri();
	this->evaluateNutriInfo();
}

Recipe::Recipe(const Recipe& c)
{
	this->name = c.name;
	strcpy(this->notes, (c.notes));
	//this->notes = c.notes;
	this->aliments = c.aliments;

	int i = 0;
	for (auto itr = c.steps.begin(); itr != c.steps.end(); itr++) {
		strcpy(this->steps[i], (*itr));
		i++;
	}
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
	std::vector<Aliment> r;
	auto itr = this->aliments.begin();
	int i = 0;
	for (itr; itr != this->aliments.end(); itr++) {
		if (!(*(itr) != 0)) {
			break;
		}
		r.push_back(this->aliments[i]);
		i++;
	}
	return r;

	//return std::vector<Aliment>(this->aliments.begin(), this->aliments.end());
	//return this->aliments;
}

void Recipe::setAliments(std::vector<Aliment> aliments)
{

	std::copy_n(aliments.begin(), MAX_ALIMENTS, this->aliments.begin());
	//this->aliments = aliments;

}

void Recipe::addAliment(Aliment aliment)
{
	auto itr = this->aliments.begin();
	int i = 0;
	for (itr; itr != this->aliments.end(); itr++) {
		if (!(*(itr) != 0)) {
			this->aliments[i] = aliment;
 			break;
		}
		i++;
	}


}



void Recipe::removeAliment(Aliment aliment)
{


	auto itr = this->aliments.begin();

	int i = 0;
	for (itr; itr != this->aliments.end(); itr++) {
		
		if (!(*(itr) == aliment)) {
			this->aliments[i] = Aliment();
			break;
		}
		i++;
	}



}



std::vector<std::string> Recipe::getSteps() const
{

	std::vector<std::string> a;
	auto itr = this->steps.begin();
	for (itr; itr < this->steps.end() && (*(itr)[0] != '\0'); itr++) {
		a.push_back(std::string(*itr));
	}
	//return std::vector<std::string>(this->steps.begin(), this->steps.end());
	//return this->steps;
	return a;
}

void Recipe::setStep(std::string step, int pos)
{
	strcpy(this->steps[pos], step.c_str());
	//std::copy_n(steps.begin(), steps.size(), this->steps.begin());
	//this->steps = steps;

}

void Recipe::addStep(std::string step)
{
	auto itr = this->steps.begin();
	int i = 0;

	for (itr; itr != this->steps.end(); itr++) {
		if (!(*(itr)[0] != '\0')) {
			int j = 0;
			strcpy(this->steps[i], step.c_str());
			/*
			for (auto itr2 = step.begin(); itr2 != step.end() && j < 255; itr2++) {
				this->steps[i][j] = *(itr2);
				j++;
			}
			*/

			break;
		}
		i++;
	}

	//this->steps.push_back(step);
}




std::string Recipe::getNotes() const
{

	return std::string(this->notes);
}

void Recipe::setNotes(std::string notes)
{
	strcpy(this->notes, (notes.c_str()));
	//this->notes = notes;
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
	this->infoNutri = n->estimateNutriValue(this->getAliments());
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