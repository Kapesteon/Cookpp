#pragma once
#include "Memento.h"

class Gardien 
{
private:
    std::vector<Memento> mementos_;

public:
    void addMemento(const Memento& memento);
    Memento getMemento(int index);
};