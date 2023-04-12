#pragma once
#include "StockedAliment.h"
#include <forward_list>
#include <list>
#include <vector>
#define MAX_STOCKEDALIMENTS 25
class Pantry
{
	private:
		//std::forward_list<StockedAliment*> stock;
		std::array<StockedAliment, MAX_STOCKEDALIMENTS> stock;

		static std::forward_list<StockedAliment*> convertStockToForwardList(std::array<StockedAliment, MAX_STOCKEDALIMENTS>* stock);
		static std::array<StockedAliment, MAX_STOCKEDALIMENTS> convertForwardListToStock(std::forward_list<StockedAliment*> flist);


	public:
		Pantry();
		Pantry(std::forward_list<StockedAliment *> stockedAliments);
		Pantry(std::array<StockedAliment, MAX_STOCKEDALIMENTS> stockedAliments);
		~Pantry();



		std::forward_list<StockedAliment *> getStock(void);
		std::list<StockedAliment*> getStockAsList(void);
		void setStock(std::forward_list<StockedAliment *> newStock) ;

		void addToStock(StockedAliment * stockedAliment);
		void removeFromStock(StockedAliment * stockedAliment);

		std::forward_list<StockedAliment*> popStockedAlimentByName(std::string name);
		std::forward_list<StockedAliment*> popStockedAlimentByType(std::string type);
		std::forward_list<StockedAliment*> popStockedAlimentMostDated(int nbr);

		friend std::istream& operator>>(std::istream& is, Pantry& in);
		//friend std::ostream& operator<<(std::ostream& os, const Pantry& in);
};

