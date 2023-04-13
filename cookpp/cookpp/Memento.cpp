#include "Memento.h"

Memento Memento::createMemento() {
	std::cout << "Création d'un Memento pour la liste de recettes." << std::endl;
	return Memento(listRecipe_, stockedAliment_);
}

void Memento::restoreMemento(const Memento& memento) {
	listRecipe_ = memento.getListRecipe();
	stockedAliment_ = memento.getStockedAliment();
	std::cout << "Restauration de la liste de recettes précédente." << std::endl;
}