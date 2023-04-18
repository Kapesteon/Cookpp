#include "Gardien.h"

void Gardien::addMemento(const Memento& memento) {
        mementos_.push_back(memento);
        std::cout << "Ajout d'un Memento � la liste des Mementos." << std::endl;
}
    
Memento Gardien::getMemento(int index) {
    Memento memento;
    std::cout << "R�cup�ration d'un Memento de la liste." << std::endl;
    try {
        memento = mementos_[index];
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Erreur : index hors limites lors de l'acc�s � la liste de mementos." << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Erreur : exception non pr�vue lors de l'acc�s � la liste de mementos." << std::endl;
    }
    return memento;
}