#include "Gardien.h"

void Gardien::addMemento(const Memento& memento) {
        mementos_.push_back(memento);
        std::cout << "Ajout d'un Memento à la liste des Mementos." << std::endl;
}
    
Memento Gardien::getMemento(int index) {
    Memento memento;
    std::cout << "Récupération d'un Memento de la liste." << std::endl;
    try {
        memento = mementos_[index];
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Erreur : index hors limites lors de l'accès à la liste de mementos." << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Erreur : exception non prévue lors de l'accès à la liste de mementos." << std::endl;
    }
    return memento;
}