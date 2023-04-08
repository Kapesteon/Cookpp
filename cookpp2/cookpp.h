#pragma once
#include <QtWidgets>
#include <QtWidgets/QWidget>
#include "ui_cookpp.h"
#include <cmath>

#include "InfoNutri.h"
#include "Aliment.h"
#include "StockedAliment.h"
#include "Pantry.h"
#include "Recipe.h"
#include "NutritionalManager.h"
#include "PantryDBManager.h"
#include "RecipeDBManager.h"
#include "FacadeUserDB.h"

class cookpp : public QWidget
{
    Q_OBJECT

public:
    cookpp(QWidget *parent = nullptr);
    ~cookpp();

    void displayMainMenu();

    void displayAllIngredients();
    void getPageIngredient(int page, std::list<Ingredient*>* listIngredient,std::vector< QToolButton*>* ingredientsButton);

    void deleteCurrentView();

private:
    int currentpage = 0;
    QMenuBar* menuBar;
    QGridLayout* currentLayout;


    QGroupBox *createDebugOutput();
    QGroupBox *createMainMenuBox();

    QGroupBox *createFirstExclusiveGroup();
    QGroupBox *createSecondExclusiveGroup();
    QGroupBox *createNonExclusiveGroup();
    QGroupBox *createPushButtonGroup();
    //Ui::cookppClass ui;

private slots:
    void ingredientListPreviousclicked();
    void ingredientListNextclicked();
};