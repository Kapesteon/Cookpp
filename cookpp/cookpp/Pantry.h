#pragma once
#include "StockedAliment.h"
#include <forward_list>
class Pantry
{
	private:
		std::forward_list<StockedAliment*> stock;

	public:
		Pantry();
		Pantry(std::forward_list<StockedAliment *> stockedAliments);
		~Pantry();

		std::forward_list<StockedAliment *> getStock(void) const;
		void setStock(std::forward_list<StockedAliment *> newStock) ;

		void addToStock(StockedAliment * stockedAliment);
		void removeFromStock(StockedAliment * stockedAliment);

		std::forward_list<StockedAliment*> popStockedAlimentByName(std::string name);
		std::forward_list<StockedAliment*> popStockedAlimentByType(std::string type);
		std::forward_list<StockedAliment*> popStockedAlimentMostDated(int nbr);

		friend std::istream& operator>>(std::istream& is, Pantry& in);
		friend std::ostream& operator<<(std::ostream& os, const Pantry& in);
};

