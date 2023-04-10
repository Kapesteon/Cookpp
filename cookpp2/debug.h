#pragma once
#include "Ingredient.h"
#include "InfoNutri.h"
#include <iostream>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <ios>

#include "debug.h"
#include "Windows.h"
#include "debugapi.h"
#include <deque>

#include "InfoNutri.h"
#include "Aliment.h"
#include "StockedAliment.h"
#include "Pantry.h"
#include "Recipe.h"
#include "NutritionalManager.h"
#include "PantryDBManager.h"
#include "RecipeDBManager.h"
#include "FacadeUserDB.h"


void debug();
void initDb();
void debugA(IngredientDBManager* DBIngredient, Ingredient* testIngredient0);
void debugB(IngredientDBManager* DBIngredient, Ingredient* testIngredient0);