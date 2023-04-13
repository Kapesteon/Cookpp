#include "Pantry.h"
#define DELIMITER_KEY_VALUE_RECIPE '@' //For serialization //MUST BE ONE CHAR

std::forward_list<StockedAliment*> Pantry::convertStockToForwardList(std::array<StockedAliment, MAX_STOCKEDALIMENTS>* stock)
{


	std::forward_list<StockedAliment*> returnList = std::forward_list<StockedAliment*>();
	int i = 0;
	for (auto itr = stock->begin(); itr != stock->end() && i < MAX_STOCKEDALIMENTS; itr++) {
		if (!(*itr == StockedAliment())) {
			returnList.push_front(&*itr);
			i++;
		}
		else {
			break;
		}
	}
	return returnList;


	//std::forward_list<StockedAliment*> returnList{ stock.cbegin(), stock.cend() };
	//returnList.remove_if([](StockedAliment* s) {return *s == (StockedAliment()); });
	//return returnList;
}

std::array<StockedAliment, MAX_STOCKEDALIMENTS> Pantry::convertForwardListToStock(std::forward_list<StockedAliment*> flist)
{
	std::array<StockedAliment, MAX_STOCKEDALIMENTS> toReturn = std::array<StockedAliment, MAX_STOCKEDALIMENTS>();
	int i = 0;
	for (auto itr = flist.begin(); itr != flist.end() && i < MAX_STOCKEDALIMENTS; itr++) {
		toReturn.at(i) = (**itr);
		i++;
	}
	return toReturn;
}

Pantry::Pantry()
{
	this->stock = std::array<StockedAliment, MAX_STOCKEDALIMENTS>();
}

Pantry::Pantry(std::forward_list<StockedAliment*> stockedAliments)
{

	this->stock = convertForwardListToStock(stockedAliments);
}

Pantry::Pantry(std::array<StockedAliment, MAX_STOCKEDALIMENTS> stockedAliments)
{
	this->stock = stockedAliments;
}



Pantry::~Pantry()
{
	OutputDebugStringA("Pantry Destroyed \n");
}

std::forward_list<StockedAliment*> Pantry::getStock(void)
{
	return this->convertStockToForwardList(&this->stock);

}

std::list<StockedAliment*> Pantry::getStockAsList(void)
{
	std::list<StockedAliment*> returnList = std::list<StockedAliment*>();


	int i = 0;
	for (auto itr = this->stock.begin(); itr != this->stock.end() && i < MAX_STOCKEDALIMENTS; itr++) {
		if (!(*itr == StockedAliment())) {

			returnList.push_back(&(*itr));

			i++;
		}
		else {
			break;
		}
	}


	return returnList;

	//std::list<StockedAliment*> list(this->stock.begin(), this->stock.end());
	//list.remove_if([](StockedAliment* s) {return *s == (StockedAliment()); });
	//return list;
}



void Pantry::setStock(std::forward_list<StockedAliment*> newStock)
{

	this->stock = this->convertForwardListToStock(newStock);
}

void Pantry::addToStock(StockedAliment* stockedAliment)
{
	int i = 0;
	for (auto itr = this->stock.begin(); itr != this->stock.end(); itr++) {
		if (*(itr) == StockedAliment()) {
			this->stock.at(i) = *stockedAliment;
			break;
		}
		i++;
	}

}

void Pantry::removeFromStock(StockedAliment* stockedAliment)
{

	auto list = this->convertStockToForwardList(&this->stock);
	//list.remove(*stockedAliment);

	auto before = list.before_begin();
	for (auto it = list.begin(); it != list.end(); ) {
		if (**it == *stockedAliment) {
			it = list.erase_after(before);

		}
		else
		{
			before = it;
			++it;
		}
	}
	this->stock = this->convertForwardListToStock(list);
}

void Pantry::editFromStock(StockedAliment* stockedAliment, double mass)
{
	auto list = this->convertStockToForwardList(&this->stock);

	for (auto it = list.begin(); it != list.end(); ++it) {
		if (**it == *stockedAliment) {
			(*it)->setMass(mass);
			break;
		}
	}
	this->stock = this->convertForwardListToStock(list);
}

std::forward_list<StockedAliment*> Pantry::popStockedAlimentByName(std::string name)
{
	std::forward_list<StockedAliment*> returnList;
	std::forward_list<StockedAliment*> list = this->convertStockToForwardList(&this->stock);

	std::forward_list<StockedAliment*>::iterator itr = list.begin();


	while (itr != list.end())
	{

		if ((*itr)->getName() == name) {

			auto next_itr = std::next(itr);
			returnList.push_front(*itr);
			list.remove(*itr);
			itr = next_itr;
		}
		else {
			itr++;
		}
	}

	this->stock = this->convertForwardListToStock(list);

	return returnList;
}

std::forward_list<StockedAliment*> Pantry::popStockedAlimentByType(std::string type)
{
	std::forward_list<StockedAliment*> returnList;
	std::forward_list<StockedAliment*> list = this->convertStockToForwardList(&this->stock);

	std::forward_list<StockedAliment*>::iterator itr = list.begin();


	while (itr != list.end())
	{

		if ((*itr)->getType() == type) {

			auto next_itr = std::next(itr);
			returnList.push_front(*itr);
			list.remove(*itr);
			itr = next_itr;
		}
		else {
			itr++;
		}
	}

	this->stock = this->convertForwardListToStock(list);

	return returnList;
}

std::forward_list<StockedAliment*> Pantry::popStockedAlimentMostDated(int nbr)
{
	auto todelete = this->stock.max_size();
	nbr = min(nbr, this->stock.max_size());
	std::forward_list<StockedAliment*> returnList;
	std::forward_list<StockedAliment*> list = this->convertStockToForwardList(&this->stock);

	list.sort();


	std::forward_list<StockedAliment*>::iterator itr = list.begin();
	int i = 0;
	while (itr != list.end() || i >= nbr)
	{
		auto next_itr = std::next(itr);
		returnList.push_front(*itr);
		list.remove(*itr);
		itr = next_itr;
		i++;
	}

	this->stock = this->convertForwardListToStock(list);
	return returnList;
}

/*
std::forward_list<StockedAliment*> Pantry::popStockedAlimentByType(std::string type)
{
	return ;
}

std::forward_list<StockedAliment*> Pantry::popStockedAlimentMostDated(int nbr)
{
	return ;
}
*/

std::istream& operator>>(std::istream& is, Pantry& in)
{


	try {
		StockedAliment buffer;
		while (is.peek() != DELIMITER_KEY_VALUE_RECIPE) {
			is >> buffer;
			in.addToStock(&buffer);
		}
		is.ignore(2, '\n'); //Ignore the delimiter
	}
	catch (std::exception) {
		std::cout << "Couldn't recover Pantry from database";
		OutputDebugStringA("Couldn't recover Pantry from database");
		return is;
	}


	return is;

}


/*
std::ostream& operator<<(std::ostream& os, const Pantry& in)
{


	try {
		auto itr = in.getStock()->begin();
		StockedAliment buffer;
		while (itr != in.getStock()end()) {
			os << *itr;
			os << std::endl;
		}
		os << DELIMITER_KEY_VALUE_RECIPE;
		os << std::endl;
	}
	catch (std::exception) {
		std::cout << "Couldn't save Pantry to database";
		OutputDebugStringA("Couldn't save Pantry to database");
		return os;
	}


	return os;


}*/