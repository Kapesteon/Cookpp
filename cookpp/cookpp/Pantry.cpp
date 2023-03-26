#include "Pantry.h"

Pantry::Pantry()
{
	this->stock = std::forward_list<StockedAliment *>();
}

Pantry::Pantry(std::forward_list<StockedAliment *> stockedAliments)
{
	this->stock = stockedAliments;
}

Pantry::~Pantry()
{
	OutputDebugStringA("Pantry Destroyed \n");
}

std::forward_list<StockedAliment *> Pantry::getStock(void) const
{
	return this->stock;
}

void Pantry::setStock(std::forward_list<StockedAliment *> newStock)
{
	this->stock = newStock;
}

void Pantry::addToStock(StockedAliment * stockedAliment)
{
	this->stock.push_front(stockedAliment);
}

void Pantry::removeFromStock(StockedAliment * stockedAliment)
{
	this->stock.remove(stockedAliment);
}

std::forward_list<StockedAliment*> Pantry::popStockedAlimentByName(std::string name)
{
	std::forward_list<StockedAliment*> returnList;

	//auto itr = this->stock.cbegin();
	std::forward_list<StockedAliment*>::iterator itr = this->stock.begin();
	while (itr != this->stock.end())
	{

		if ((*itr)->getName() == name) {
			//itr = this->stock.erase(itr);
			auto next_itr = std::next(itr);
			returnList.push_front(*itr);
			this->stock.remove(*itr);
			itr = next_itr;
		}
		else {
			itr++;
		}
	}

	return returnList;
}

std::forward_list<StockedAliment*> Pantry::popStockedAlimentByType(std::string type)
{
	std::forward_list<StockedAliment*> returnList;

	//auto itr = this->stock.cbegin();
	std::forward_list<StockedAliment*>::iterator itr = this->stock.begin();
	while (itr != this->stock.end())
	{

		if ((*itr)->getType() == type) {
			//itr = this->stock.erase(itr);
			auto next_itr = std::next(itr);
			returnList.push_front(*itr);
			this->stock.remove(*itr);
			itr = next_itr;
		}
		else {
			itr++;
		}
	}

	return returnList;
}

std::forward_list<StockedAliment*> Pantry::popStockedAlimentMostDated(int nbr)
{
	auto todelete = this->stock.max_size();
	nbr = min(nbr, this->stock.max_size());
	std::forward_list<StockedAliment*> returnList;

	this->stock.sort();


	std::forward_list<StockedAliment*>::iterator itr = this->stock.begin();
	int i = 0;
	while (itr != this->stock.end() || i >= nbr)
	{
		auto next_itr = std::next(itr);
		returnList.push_front(*itr);
		this->stock.remove(*itr);
		itr = next_itr;
		i++;
	}

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