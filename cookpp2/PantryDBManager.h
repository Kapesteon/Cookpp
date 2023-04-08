#pragma once
#include "GenericDBManager.h"
#include "Pantry.h"
class PantryDBManager :
    public GenericDBManager
{
    private:
        static const std::streamsize classSize = sizeof(Pantry);
    public:

        PantryDBManager();
        PantryDBManager(std::string filepath);
        PantryDBManager(PantryDBManager &c);
        ~PantryDBManager();


        bool write(void * pantry, int pos); //Pointer to Pantry object
        bool read(void * pantry, int pos); //Pointer to Pantry object

};

