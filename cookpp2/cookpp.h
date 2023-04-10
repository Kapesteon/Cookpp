#pragma once
#include <QtWidgets>
#include <QtWidgets/QWidget>
#include "ui_cookpp.h"
#include "debug.h"
#include <cmath>
#include <memory>

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
    void displayAllRecipes();
    void getPageIngredient(int page, std::list<Ingredient*>* listIngredient,std::vector< QToolButton*>* ingredientsButton);
    void getPageRecipe(int page, std::list<Recipe*>* listRecipe, std::vector< QToolButton*>* recipesButton);



    void deleteCurrentView();
    void deleteSpecificLayout(QLayout* item);

private:
    int currentPage = 0;
    std::unique_ptr<std::vector<Ingredient*>> activeIngredientBuffer; //Used to store Ingredients
    std::unique_ptr<std::vector<Recipe*>> activeRecipeBuffer; //Used to store Ingredients
    FacadeUserDB* facade;


    QGroupBox* detailBox;

    QMenuBar* menuBar;
    QGridLayout* currentLayout;
    QMenu* mnfileMenu;
    QMenu* mneditMenu;
    QMenu* mnformatMenu;
    QMenu* mnhelpMenu;


    QGroupBox *createDebugOutput();
    QGroupBox *createMainMenuBox();

    QGroupBox *createFirstExclusiveGroup();
    QGroupBox *createSecondExclusiveGroup();
    QGroupBox *createNonExclusiveGroup();
    QGroupBox *createPushButtonGroup();
    //Ui::cookppClass ui;

    void createActions();
    void createMenus();


    /*------------Menu Actions-----------*/
    QAction* mnMainMenuAct;
    QAction* mnExitAct;
    QAction* mnAddRecipeAct;
    QAction* mnEditRecipeAct;
    QAction* mnAddIngredientAct;
    QAction* mnEditIngredientAct;
    QAction* mnAddToPantryAct;
    QAction* mnRemoveFromPantryAct;
    QAction* mnViewIngredientsAct;
    QAction* mnViewRecipesAct;
    QAction* mnViewPantryAct;
    QAction* mnaboutAct;
    /*------------------------------------*/
    
private slots:

    /*--------Display all* Slot ----*/
    void ingredientListPreviousclicked();
    void ingredientListNextclicked();
    void recipeListNextclicked();
    void recipeListPreviousclicked();

    /*------------Menu Slots-----------*/
    void mnMainMenu();
    void mnViewIngredients();
    void mnViewRecipes();
    /*------------------------------------*/

    /*------------Menu Slots-----------*/
    void showIngredientDetailclicked();
    void showRecipeDetailclicked();
    /*------------------------------------*/

};