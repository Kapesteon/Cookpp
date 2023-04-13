#include "Gardien.h"

void Gardien::addMemento(const Memento& memento) {
        mementos_.push_back(memento);
        std::cout << "Ajout d'un Memento à la liste des Mementos." << std::endl;
}
    
Memento Gardien::getMemento(int index) {
        std::cout << "Récupération d'un Memento de la liste." << std::endl;
        return mementos_[index];
}