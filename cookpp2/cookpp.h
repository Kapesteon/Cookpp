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
    void displayPantry();
    void getPageIngredient(int page, std::list<Ingredient*>* listIngredient,std::vector< QToolButton*>* ingredientsButton);
    void getPageRecipe(int page, std::list<Recipe*>* listRecipe, std::vector< QToolButton*>* recipesButton);
    void getPagePantry(int page, std::list<StockedAliment*>* listStockedAliment, std::vector< QToolButton*>* pantryButton);

    void ingredientEditor();
    void saveIngredientEdit();

    /* RECIPE */
    void recipeEditor();
    void saveRecipeEdit();
    void setupRecipeAlimentsTable(QTableWidget* aliments, std::vector<Aliment>* alimList);
    void setupRecipeStepsTable(QTableWidget* steps,std::vector<std::string> *stepsList);
    void updateCurrentRecipeSelected();

    void deleteCurrentView();
    void deleteSpecificLayout(QLayout* item);
    void setDetailBoxToMainLayout(int row, int col, int rowSpan, int colSpan);

private:
    int currentPage = 0;
    std::unique_ptr<std::vector<Ingredient*>> activeIngredientBuffer; //Used to store Ingredients
    std::unique_ptr<std::vector<Recipe*>> activeRecipeBuffer; //Used to store Recipes
    std::unique_ptr<std::vector<StockedAliment*>> activeStockedAlimentBuffer; //Used to store StockedAliment
    Ingredient* currentIngredientSelected;
    Recipe* currentRecipeSelected;


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
    void mnViewPantry();
    void mnAddIngredient();
    void mnAddRecipe();
    /*------------------------------------*/

    /*------------Button Slots-----------*/
    void showIngredientDetailclicked();
    void showRecipeDetailclicked();
    void showStockedAlimentDetailclicked();

    void editIngredientclicked();
    void saveIngredientEditclicked();

    void editRecipeclicked();
    void saveRecipeEditclicked();
    void addNewAlimentInRecipeclicked();
    void removeAlimentFromRecipeclicked();
    void addNewStepInRecipeclicked();
    void removeStepFromRecipeclicked();

    void gotoMainMenuclicked();
    /*------------------------------------*/

};