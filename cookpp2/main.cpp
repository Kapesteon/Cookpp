#include "cookpp.h"
#include <QtWidgets/QApplication>
#include "debug.h"

int main(int argc, char *argv[])
{

    initDb(); //empty File must be create beforehand

    
    //IngredientDBManager* DBIngredient = new IngredientDBManager("stockDB/ingredient.cdb");
    //Ingredient* testIngredient0 = new Ingredient();
    //debugA(DBIngredient, testIngredient0);
    //debugB(DBIngredient, testIngredient0);
    //debug();

    QApplication a(argc, argv);
    cookpp w;
    w.show();
    return a.exec();
}
