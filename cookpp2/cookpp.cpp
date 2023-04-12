#pragma once
#include "cookpp.h"

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

#define NUMBER_OBJET_PER_PAGE 9
#define BTN_FIXED_WIDTH 80
#define BTN_FIXED_HEIGHT 40

cookpp::cookpp(QWidget *parent)
    : QWidget(parent)
{
    initDb();

    QVBoxLayout* mainLayout = new QVBoxLayout(this); // Main layout of widget
    this->facade = new FacadeUserDB();
    this->detailBox = new QGroupBox(tr("Details"));

    createActions();
    createMenus();

    displayMainMenu();

    setMinimumSize(1280, 600);
    setMaximumSize(1280, 600);
    resize(1280, 600);
    QPalette pal = QPalette();

    // set black background
    // Qt::black / "#000000" / "black"
    pal.setColor(QPalette::Window, Qt::white);

    this->setAutoFillBackground(true);
    this->setPalette(pal);
    //this->setStyleSheet("background-color:white;");
}

cookpp::~cookpp()
{}

void cookpp::displayMainMenu() {

    deleteCurrentView();

    QGridLayout* mainGrid = new QGridLayout;

    setLayout(mainGrid);
 
    setWindowTitle(tr("Cook++ - Main Menu"));

}

void cookpp::getPageIngredient(int page, std::list<Ingredient*>* listIngredient,std::vector< QToolButton*>* ingredientsButton)
{
    std::string n = "";
    //std::unique_ptr<std::vector<Ingredient>> bufferIngredients(new std::vector<Ingredient>());
    std::unique_ptr<std::vector<Ingredient*>> bufferIngredients = std::make_unique<std::vector<Ingredient*>>();
    auto itr = listIngredient->begin();



    //Set the iterator to the right emplacement
    for (int i = 0; i < NUMBER_OBJET_PER_PAGE * page; i++) {
        itr++;
        if (itr == listIngredient->end()) {
            break;   
        }
    }
    
    //Build all buttons containing the right name
    for (int i = 0; i < NUMBER_OBJET_PER_PAGE; ++i) {
        try {
            if (itr == listIngredient->end()){
                ingredientsButton->push_back(new QToolButton());
                ingredientsButton->back()->setText(tr(""));
                ingredientsButton->back()->setFixedSize(0, 0);
                Ingredient * a = new Ingredient();
                bufferIngredients->push_back(a);
            }
            else {
                std::string n = (*itr)->getName();
                ingredientsButton->push_back(new QToolButton());
                ingredientsButton->back()->setText(tr(n.c_str()));
                ingredientsButton->back()->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
                connect(ingredientsButton->back(), SIGNAL(clicked()), this, SLOT(showIngredientDetailclicked()));
                bufferIngredients->push_back(*itr);
                itr++;
            }


        }
        catch (std::exception) {
            return;
        }
    }

    this->activeIngredientBuffer = std::move(bufferIngredients);
    //delete listIngredient; //Causes crash
    return;

        
}

void cookpp::getPageRecipe(int page, std::list<Recipe*>* listRecipe, std::vector< QToolButton*>* recipesButton)
{
    std::string n = "";
    //std::unique_ptr<std::vector<Ingredient>> bufferIngredients(new std::vector<Ingredient>());
    std::unique_ptr<std::vector<Recipe*>> bufferRecipes = std::make_unique<std::vector<Recipe*>>();
    auto itr = listRecipe->begin();



    //Set the iterator to the right emplacement
    for (int i = 0; i < NUMBER_OBJET_PER_PAGE * page; i++) {
        itr++;
        if (itr == listRecipe->end()) {
            break;
        }
    }

    //Build all buttons containing the right name
    for (int i = 0; i < NUMBER_OBJET_PER_PAGE; ++i) {
        try {
            if (itr == listRecipe->end()) {
                recipesButton->push_back(new QToolButton());
                recipesButton->back()->setText(tr(""));
                recipesButton->back()->setFixedSize(0, 0);
                Recipe* a = new Recipe();
                bufferRecipes->push_back(a);
            }
            else {
                std::string n = (*itr)->getName();
                recipesButton->push_back(new QToolButton());
                recipesButton->back()->setText(tr(n.c_str()));
                recipesButton->back()->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
                connect(recipesButton->back(), SIGNAL(clicked()), this, SLOT(showRecipeDetailclicked()));
                bufferRecipes->push_back(*itr);
                itr++;
            }


        }
        catch (std::exception) {
            return;
        }
    }

    this->activeRecipeBuffer = std::move(bufferRecipes);
    //delete listIngredient; //Causes crash
    return;


}

void cookpp::getPagePantry(int page, std::list<StockedAliment*>* listStockedAliment, std::vector< QToolButton*>* pantryButton)
{
    std::string n = "";
    std::unique_ptr<std::vector<StockedAliment*>> bufferStockedAliment= std::make_unique<std::vector<StockedAliment*>>();
    auto itr = listStockedAliment->begin();



    //Set the iterator to the right emplacement
    for (int i = 0; i < NUMBER_OBJET_PER_PAGE * page; i++) {
        itr++;
        if (itr == listStockedAliment->end()) {
            break;
        }
    }

    //Build all buttons containing the right name
    for (int i = 0; i < NUMBER_OBJET_PER_PAGE; ++i) {
        try {
            if (itr == listStockedAliment->end()) {
                pantryButton->push_back(new QToolButton());
                pantryButton->back()->setText(tr(""));
                pantryButton->back()->setFixedSize(0, 0);
                StockedAliment* a = new StockedAliment();
                bufferStockedAliment->push_back(a);
            }
            else {
                std::string n = (*itr)->getName();
                pantryButton->push_back(new QToolButton());
                pantryButton->back()->setText(tr(n.c_str()));
                pantryButton->back()->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
                connect(pantryButton->back(), SIGNAL(clicked()), this, SLOT(showStockedAlimentDetailclicked()));
                bufferStockedAliment->push_back(*itr);
                itr++;
            }


        }
        catch (std::exception) {
            return;
        }
    }

    this->activeStockedAlimentBuffer = std::move(bufferStockedAliment);
    //delete listIngredient; //Causes crash
    return;


}

void cookpp::ingredientEditor()
{
    try{
        deleteCurrentView();

        QFormLayout* mainLayout = new QFormLayout;
        QVBoxLayout* vbox = new QVBoxLayout;
        QLineEdit* name = new QLineEdit("Name");
        QComboBox* type = new QComboBox();
        QTableWidget* infoNutri = new QTableWidget();
        QDialogButtonBox* dialogButton = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        Ingredient* toEdit = this->currentIngredientSelected;


        //QDialogButtonBox * okButton = new QDialogButtonBox(QDialogButtonBox::Ok);
        //QDialogButtonBox* cancelButton = new QDialogButtonBox(QDialogButtonBox::Cancel);



        QString* qstr = new QString();

        *qstr = QString::fromStdString("");
        qstr->append(QString::fromStdString(toEdit->getName()));
        name->setText(*qstr);
        name->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
        if (toEdit->getName() != "Undefined") {
            name->setFrame(false);
            name->setReadOnly(true);
        }
        else {
            name->setFrame(true);
            name->setReadOnly(false);
        }
        name->setAlignment(Qt::AlignCenter);



        type->addItem(tr("Grain"));
        type->addItem(tr("Vegetable"));
        type->addItem(tr("Fruit"));
        type->addItem(tr("Protein"));
        type->addItem(tr("Oil"));
        type->addItem(tr("Other"));
        type->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
        type->setFrame(true);


        auto t = toEdit->getInfoNutri().getNutriValues();

        infoNutri->setColumnCount(2);
        infoNutri->setRowCount(t.size());
        infoNutri->verticalHeader()->setVisible(false);
        infoNutri->horizontalHeader()->setVisible(false);
        auto keysName = toEdit->getInfoNutri().getNutriKeys();


        QTableWidgetItem* itemTitle = new QTableWidgetItem();
        QTableWidgetItem* itemValue = new QTableWidgetItem();
        itemTitle->setText("Per Amount (g)");

        *qstr = QString::fromStdString("");
        qstr->append(QString::number(t.at(0), 'G', 5));
        itemValue->setText(*qstr);

        itemTitle->setFlags(itemTitle->flags() ^ Qt::NoItemFlags);
        itemTitle->setFlags(itemTitle->flags() ^ Qt::ItemIsEditable | Qt::ItemIsSelectable);
        infoNutri->setItem(0, 0, itemTitle);
        infoNutri->setItem(0, 1, itemValue);

        int i = 1;
        auto it = t.begin();
        it++;
        for (it; it != t.end(); it++) {
            QTableWidgetItem* itemTitle = new QTableWidgetItem();
            QTableWidgetItem* itemValue = new QTableWidgetItem();

            *qstr = QString::fromStdString("");
            *qstr = QString::fromStdString(keysName.at(i));


            if (keysName.at(i) == "sodium") {
                qstr->append(" (mg)");
                itemTitle->setText(*qstr);
                *qstr = QString::fromStdString("");
                qstr->append(QString::number((*it) * 1000, 'G', 8));
                itemValue->setText(*qstr);
            }
            else if (keysName.at(i) == "calories") {
                qstr->append(" (kcal)");
                itemTitle->setText(*qstr);
                *qstr = QString::fromStdString("");
                qstr->append(QString::number((*it), 'G', 5));
                itemValue->setText(*qstr);
            }
            else{
                qstr->append(" (g)");
                itemTitle->setText(*qstr);
                *qstr = QString::fromStdString("");
                qstr->append(QString::number((*it), 'G', 5));
                itemValue->setText(*qstr);
            }
            
            itemValue->setFlags(itemTitle->flags() ^ Qt::NoItemFlags);
            itemTitle->setFlags(itemTitle->flags() ^ Qt::ItemIsEditable | Qt::ItemIsSelectable);

            infoNutri->setItem(i, 0, itemTitle);
            infoNutri->setItem(i, 1, itemValue);
            i++;
        }
        infoNutri->setFrameStyle(QFrame::NoFrame);


        //connect(dialogButton, SIGNAL(accepted()), &dialog, SLOT(accept()));
        connect(dialogButton, SIGNAL(accepted()), this, SLOT(saveIngredientEditclicked()));
        connect(dialogButton, SIGNAL(rejected()), this, SLOT(gotoMainMenuclicked()));


        QLayout* oldLayout = this->detailBox->layout();
        deleteSpecificLayout(oldLayout);

        name->setObjectName("name");
        type->setObjectName("type");
        infoNutri->setObjectName("infoNutri");
        vbox->addWidget(name, Qt::AlignCenter);
        vbox->addWidget(type, Qt::AlignCenter);
        vbox->addWidget(infoNutri, Qt::AlignCenter);
        vbox->addWidget(dialogButton, Qt::AlignCenter);
        this->detailBox->setLayout(vbox);
        mainLayout->addWidget(this->detailBox);
        setLayout(mainLayout);
        setWindowTitle(tr("Cook++ - Ingredients"));


    }
    catch (std::exception) {
        OutputDebugStringA("Error with button sender");
    }
}

void cookpp::saveIngredientEdit()
{
    Ingredient* toSave = this->currentIngredientSelected;
    InfoNutri* infoNutriToSave = new InfoNutri;
    std::string ingredientName = "";
    std::string ingredientType = "";


    for (int i = 0; i < this->detailBox->layout()->count(); ++i)
    {
        QWidget* widget = this->detailBox->layout()->itemAt(i)->widget();
        if (widget != NULL)
        {
            QString qname = widget->objectName();
            std::string sname = qname.toStdString();
            if (sname == "name") {
                QLineEdit* item = qobject_cast<QLineEdit*>(widget);
                ingredientName = item->text().toStdString();
                toSave->setName(ingredientName);
            }
            else if (sname == "type") {
                QComboBox* item = qobject_cast<QComboBox*>(widget);
                ingredientType = item->currentText().toStdString();
                toSave->setType(ingredientType);
            }
            else if (sname == "infoNutri") {
                QTableWidget* table = qobject_cast<QTableWidget*>(widget);
                QTableWidgetItem* itemTitle = new QTableWidgetItem;
                QTableWidgetItem* itemValue = new QTableWidgetItem;
                std::vector<std::string> keys = infoNutriToSave->getNutriKeys();
                for (int row = 0; row < table->rowCount(); ++row) {
                    std::string key = table->item(row, 0)->text().toStdString();
                    double value = table->item(row, 1)->text().toDouble();
                    if (key == "sodium (mg)") {
                        value = value / 1000;
                    }
                    infoNutriToSave->setValueByKey(keys[row], value);
                }
                toSave->setInfoNutri(*infoNutriToSave);
            }
        }
        else
        {
            // You may want to recurse, or perform different actions on layouts.
            // See gridLayout->itemAt(i)->layout()
        }


    }

    //
    auto list = this->facade->getAllIngredient();
    int writeIndex = list.size();
    //See where to write the current ingredient
    int i = 0;
    for (auto it = list.begin(); it != list.end(); it++) {
        if((*it)->getName() == toSave->getName()) {
            break;
        }
        i++;
    }
    writeIndex = i;
    this->facade->saveIngredient(toSave, writeIndex);
    //this->facade->addIngredient(toAdd);


    delete infoNutriToSave;


    displayAllIngredients();

    return;
}



void cookpp::displayAllIngredients()
{
    //Delete old layout to drwn the new https://forum.qt.io/topic/14898/howto-change-layout-of-a-widget/10
    deleteCurrentView();


    QGridLayout* mainLayout = new QGridLayout;


    std::list<Ingredient*>  listIngredient;
    int maxPage = 1;
    try {
        listIngredient = this->facade->getAllIngredient();
      
        if (listIngredient.size() <= NUMBER_OBJET_PER_PAGE ) {
            maxPage = 0;
        }
        else {
            int maxPage = floor(listIngredient.size() / NUMBER_OBJET_PER_PAGE);
        }


    }
    catch (std::exception) {
        Ingredient* t = new Ingredient();
        listIngredient.push_back(t);
    }
 

    std::vector<QToolButton*> ingredientsButton;


    if (this->currentPage < 0) {
        this->currentPage = maxPage;
    }
    if (this->currentPage > maxPage) {
        this->currentPage = 0;
    }
 

    getPageIngredient(this->currentPage, &listIngredient, &ingredientsButton);



    for (int i = 0; i < NUMBER_OBJET_PER_PAGE; ++i) {
        int row = i / 3;
        int column = ((i) % 3) + 1;
        mainLayout->addWidget(ingredientsButton.at(i), row, column);
    }
    
    /*---Add Left and Right Buttons---*/
    QToolButton* previousPageButton = new QToolButton();
    QToolButton* nextPageButton = new QToolButton();
    previousPageButton->setText(tr("<"));
    nextPageButton->setText(tr(">"));
    previousPageButton->setFixedSize(BTN_FIXED_HEIGHT, BTN_FIXED_HEIGHT);
    nextPageButton->setFixedSize(BTN_FIXED_HEIGHT, BTN_FIXED_HEIGHT);
    connect(previousPageButton, SIGNAL(clicked()), this, SLOT(ingredientListPreviousclicked()));
    connect(nextPageButton, SIGNAL(clicked()), this, SLOT(ingredientListNextclicked()));
    mainLayout->addWidget(previousPageButton, 1, 0);
    mainLayout->addWidget(nextPageButton, 1,4);


    /*---Add Bottom Page text---*/
    QLineEdit* displayPage = new QLineEdit();
    displayPage->setReadOnly(true);
    displayPage->setAlignment(Qt::AlignCenter);
    QFont font = displayPage->font();
    //font.setPointSize(font.pointSize() + 7);
    displayPage->setFont(font);
    std::string pageStr = std::to_string(this->currentPage);
    pageStr.append(" / ");
    pageStr.append(std::to_string(maxPage));
    displayPage->setText(QString::fromStdString(pageStr));
    displayPage->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
    displayPage->setFrame(false);
    mainLayout->addWidget(displayPage,3,2);
    mainLayout->addWidget(this->detailBox, 0, 6, 4, 2);
    setLayout(mainLayout);

    setWindowTitle(tr("Cook++ - Ingredients"));

}

void cookpp::displayAllRecipes()
{
    //Delete old layout to drwn the new https://forum.qt.io/topic/14898/howto-change-layout-of-a-widget/10
    deleteCurrentView();


    QGridLayout* mainLayout = new QGridLayout;


    std::list<Recipe*>  listRecipe;
    int maxPage = 1;
    try {
        listRecipe = this->facade->getAllRecipe();

        if (listRecipe.size() <= NUMBER_OBJET_PER_PAGE) {
            maxPage = 0;
        }
        else {
            int maxPage = floor(listRecipe.size() / NUMBER_OBJET_PER_PAGE);
        }
    }
    catch (std::exception) {
        Recipe* t = new Recipe();
        listRecipe.push_back(t);
    }


    std::vector<QToolButton*> recipesButton;


    if (this->currentPage < 0) {
        this->currentPage = maxPage;
    }
    if (this->currentPage > maxPage) {
        this->currentPage = 0;
    }


    getPageRecipe(this->currentPage, &listRecipe, &recipesButton);



    for (int i = 0; i < NUMBER_OBJET_PER_PAGE; ++i) {
        int row = i / 3;
        int column = ((i) % 3) + 1;
        mainLayout->addWidget(recipesButton.at(i), row, column);
    }

    /*---Add Left and Right Buttons---*/
    QToolButton* previousPageButton = new QToolButton();
    QToolButton* nextPageButton = new QToolButton();
    previousPageButton->setText(tr("<"));
    nextPageButton->setText(tr(">"));
    previousPageButton->setFixedSize(BTN_FIXED_HEIGHT, BTN_FIXED_HEIGHT);
    nextPageButton->setFixedSize(BTN_FIXED_HEIGHT, BTN_FIXED_HEIGHT);
    connect(previousPageButton, SIGNAL(clicked()), this, SLOT(recipeListPreviousclicked()));
    connect(nextPageButton, SIGNAL(clicked()), this, SLOT(recipeListNextclicked()));
    mainLayout->addWidget(previousPageButton, 1, 0);
    mainLayout->addWidget(nextPageButton, 1, 4);


    /*---Add Bottom Page text---*/
    QLineEdit* displayPage = new QLineEdit();
    displayPage->setReadOnly(true);
    displayPage->setAlignment(Qt::AlignCenter);
    QFont font = displayPage->font();
    //font.setPointSize(font.pointSize() + 7);
    displayPage->setFont(font);
    std::string pageStr = std::to_string(this->currentPage);
    pageStr.append(" / ");
    pageStr.append(std::to_string(maxPage));
    displayPage->setText(QString::fromStdString(pageStr));
    displayPage->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
    displayPage->setFrame(false);
    mainLayout->addWidget(displayPage, 3, 2);
    mainLayout->addWidget(this->detailBox, 0, 6, 4, 2);
    setLayout(mainLayout);

    setWindowTitle(tr("Cook++ - Recipes"));

}

void cookpp::displayPantry()
{
    //Delete old layout to drwn the new https://forum.qt.io/topic/14898/howto-change-layout-of-a-widget/10
    deleteCurrentView();


    QGridLayout* mainLayout = new QGridLayout;



    Pantry* pantry = new Pantry();
    std::list<StockedAliment*> listStockedAliment;
    
    int maxPage = 1;
    try {
        this->facade->getPantry(pantry);
        listStockedAliment = pantry->getStockAsList();


        if (listStockedAliment.size() <= NUMBER_OBJET_PER_PAGE) {
            maxPage = 0;
        }
        else {
            int maxPage = floor(listStockedAliment.size() / NUMBER_OBJET_PER_PAGE);
        }
    }
    catch (std::exception) {
        StockedAliment* t = new StockedAliment();
        listStockedAliment.push_back(t);
    }

    
    std::vector<QToolButton*> pantryButton;
 

    if (this->currentPage < 0) {
        this->currentPage = maxPage;
    }
    if (this->currentPage > maxPage) {
        this->currentPage = 0;
    }


    getPagePantry(this->currentPage, &listStockedAliment, &pantryButton);



    for (int i = 0; i < NUMBER_OBJET_PER_PAGE; ++i) {
        int row = i / 3;
        int column = ((i) % 3) + 1;
        mainLayout->addWidget(pantryButton.at(i), row, column);
    }

    /*---Add Left and Right Buttons---*/
    QToolButton* previousPageButton = new QToolButton();
    QToolButton* nextPageButton = new QToolButton();
    previousPageButton->setText(tr("<"));
    nextPageButton->setText(tr(">"));
    previousPageButton->setFixedSize(BTN_FIXED_HEIGHT, BTN_FIXED_HEIGHT);
    nextPageButton->setFixedSize(BTN_FIXED_HEIGHT, BTN_FIXED_HEIGHT);
    connect(previousPageButton, SIGNAL(clicked()), this, SLOT(pantryPreviousclicked()));
    connect(nextPageButton, SIGNAL(clicked()), this, SLOT(pantryNextclicked()));
    mainLayout->addWidget(previousPageButton, 1, 0);
    mainLayout->addWidget(nextPageButton, 1, 4);


    /*---Add Bottom Page text---*/
    QLineEdit* displayPage = new QLineEdit();
    displayPage->setReadOnly(true);
    displayPage->setAlignment(Qt::AlignCenter);
    QFont font = displayPage->font();
    //font.setPointSize(font.pointSize() + 7);
    displayPage->setFont(font);
    std::string pageStr = std::to_string(this->currentPage);
    pageStr.append(" / ");
    pageStr.append(std::to_string(maxPage));
    displayPage->setText(QString::fromStdString(pageStr));
    displayPage->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
    displayPage->setFrame(false);
    mainLayout->addWidget(displayPage, 3, 2);
    mainLayout->addWidget(this->detailBox, 0, 6, 4, 2);
    setLayout(mainLayout);

    setWindowTitle(tr("Cook++ - Pantry"));
    
}

QGroupBox* cookpp::createDebugOutput() {

    QGroupBox* groupBox = new QGroupBox(tr("Output"));
    QVBoxLayout* vbox = new QVBoxLayout;

    QTextEdit* display = new QTextEdit("Messages :");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignLeft);

    QFont font = display->font();
    //font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    vbox->addWidget(display);
    groupBox->setLayout(vbox);

    return groupBox;
}


QGroupBox* cookpp::createMainMenuBox() {

    QGroupBox* groupBox = new QGroupBox(tr("Output"));
    QVBoxLayout* vbox = new QVBoxLayout;
    
    QToolButton* showIngredientButton = new QToolButton();
    showIngredientButton->setText(tr("Show all ingredients"));

    QToolButton* showPantryButton = new QToolButton();
    showPantryButton->setText(tr("Show current pantry"));

    QToolButton* showRecipeButton = new QToolButton();
    showRecipeButton->setText(tr("Show all recipes"));

    vbox->addWidget(showIngredientButton);
    vbox->addWidget(showPantryButton);
    vbox->addWidget(showRecipeButton);
    groupBox->setLayout(vbox);


    return groupBox;
}

void cookpp::deleteCurrentView()
{
    QLayoutItem* item;
    try {
        item = layout();
        if (item == NULL) {
            return;
        }
        else {
            while ((item = layout()->takeAt(0)) != NULL)
            {
                delete item->widget();
                delete item;
            }
            delete layout();
        }
        this->detailBox = new QGroupBox(tr("Details"));
    }
    catch (std::exception) {
        OutputDebugStringA("No layout to delete \n");
    }
}

void cookpp::deleteSpecificLayout(QLayout* item)
{

    try {

        QLayoutItem* buffer;
        if (item == NULL) {
            return;
        }
        else {
            while ((buffer = item->takeAt(0)) != NULL)
            {
                delete buffer->widget();
                delete buffer;
            }
            delete item;
        }

    }
    catch (std::exception) {
        OutputDebugStringA("No layout to delete \n");
    }
}

void cookpp::setDetailBoxToMainLayout(int row, int col, int rowSpan, int colSpan) {
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(this->detailBox, row, col, rowSpan, colSpan);
    setLayout(mainLayout);
}







void cookpp::createActions()
{

    /*----------Act Declaration----------*/
    //mnNewAct
    mnMainMenuAct = new QAction(tr("&Main Menu"), this);
    mnExitAct = new QAction(tr("&Exit"), this);

    mnAddRecipeAct = new QAction(tr("&Add New Recipe"), this);
    mnEditRecipeAct = new QAction(tr("&Edit Recipe"), this);
    mnAddIngredientAct = new QAction(tr("&Add New Ingredient"), this);
    mnEditIngredientAct = new QAction(tr("&Edit Ingredient"), this);
    mnAddToPantryAct = new QAction(tr("&Add To Pantry"), this);
    mnRemoveFromPantryAct = new QAction(tr("&Remove From Pantry"), this);

    mnViewIngredientsAct = new QAction(tr("&View Ingredients"), this);
    mnViewRecipesAct = new QAction(tr("&View Recipes"), this);
    mnViewPantryAct = new QAction(tr("&View Pantry"), this);

    mnaboutAct = new QAction(tr("&About"), this);

    /*----------Act Properties Setup--------------*/
    mnMainMenuAct->setShortcuts(QKeySequence::New);
    mnMainMenuAct->setStatusTip(tr("Go to Main Menu"));
    connect(mnMainMenuAct, &QAction::triggered, this, &cookpp::mnMainMenu);

    mnViewIngredientsAct->setStatusTip(tr("View all known ingredients"));
    connect(mnViewIngredientsAct, &QAction::triggered, this, &cookpp::mnViewIngredients);

    mnViewRecipesAct->setStatusTip(tr("View all known recipes"));
    connect(mnViewRecipesAct, &QAction::triggered, this, &cookpp::mnViewRecipes);

    mnViewPantryAct->setStatusTip(tr("View Stocked Aliments in Pantry "));
    connect(mnViewPantryAct, &QAction::triggered, this, &cookpp::mnViewPantry);

    mnAddIngredientAct->setStatusTip(tr("Create a new Ingredient"));
    connect(mnAddIngredientAct, &QAction::triggered, this, &cookpp::mnAddIngredient);
}

void cookpp::createMenus()
{
    this->menuBar = new QMenuBar();
    menuBar->setNativeMenuBar(false);

    QMenu * fileMenu = menuBar->addMenu(tr("&File"));
    //fileMenu->addAction(mnNewAct);
    fileMenu->addAction(mnMainMenuAct);
    fileMenu->addSeparator();
    fileMenu->addAction(mnExitAct);

    QMenu* editMenu = menuBar->addMenu(tr("&Edit"));
    editMenu->addAction(mnAddRecipeAct);
    editMenu->addAction(mnEditRecipeAct);
    editMenu->addSeparator();
    editMenu->addAction(mnAddIngredientAct);
    editMenu->addAction(mnEditIngredientAct);
    editMenu->addSeparator();
    editMenu->addAction(mnAddToPantryAct);
    editMenu->addAction(mnRemoveFromPantryAct);
    editMenu->addSeparator();

    QMenu* viewMenu = menuBar->addMenu(tr("&View"));
    viewMenu->addAction(mnViewIngredientsAct);
    viewMenu->addAction(mnViewRecipesAct);
    viewMenu->addAction(mnViewPantryAct);

    QMenu* helpMenu = menuBar->addMenu(tr("&Help"));
    helpMenu->addAction(mnaboutAct);

    this->layout()->setMenuBar(menuBar);
}



void cookpp::ingredientListNextclicked()
{
    this->currentPage++;
    displayAllIngredients();
    OutputDebugStringA("Next page ! \n");
    std::cout << "Next page ! \n";
}

void cookpp::ingredientListPreviousclicked() 
{
    this->currentPage--;
    displayAllIngredients();
    OutputDebugStringA("Previous page ! \n");
    std::cout << "Previous page ! \n";
}

void cookpp::recipeListNextclicked()
{
    this->currentPage++;
    displayAllRecipes();
}

void cookpp::recipeListPreviousclicked()
{
    this->currentPage--;
    displayAllRecipes();
}


/*----- MN METHODS --------*/
void cookpp::mnMainMenu() 
{
    displayMainMenu();
}

void cookpp::mnViewIngredients() {
    displayAllIngredients();
}

void cookpp::mnViewRecipes() {
    displayAllRecipes();
}

void cookpp::mnViewPantry() {
    displayPantry();
}

void cookpp::mnAddIngredient() {
    this->currentIngredientSelected = new Ingredient;
    ingredientEditor();
}



void cookpp::showIngredientDetailclicked()
{
    QObject* buttonSender = QObject::sender();
    try {
        QString qs = qobject_cast<QToolButton*>(buttonSender)->text();
        std::string ss = qs.toStdString();


        QVBoxLayout* vbox = new QVBoxLayout;
        
        Ingredient* ingrToShow = new Ingredient();
     

        QLineEdit* name = new QLineEdit("Name");
        QLineEdit* type = new QLineEdit("Type");
        QLineEdit* season = new QLineEdit("Season");
        QTableWidget* infoNutri = new QTableWidget();
        QPushButton* editButton = new QPushButton(tr("&Edit"));

        auto itr = this->activeIngredientBuffer->begin();

        for (itr; itr != this->activeIngredientBuffer->end(); itr++) {
            if ((*itr)->getName() == ss) {
                ingrToShow = (*itr);
                break;
            }
        }

        name->setText(qs);
        name->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
        name->setFrame(false);
        name->setReadOnly(true);
        name->setAlignment(Qt::AlignCenter);

        type->setText(QString::fromStdString(ingrToShow->getType()));
        type->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
        type->setFrame(false);
        type->setReadOnly(true);
        type->setAlignment(Qt::AlignCenter);


        if (ingrToShow->getSeason() != "N/A") {
            season->setText(qs);
            season->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
            season->setFrame(false);
            season->setReadOnly(true);
            season->setAlignment(Qt::AlignCenter);
        }
        else {
            season->setFixedSize(0,0);
        }


        auto t = ingrToShow->getInfoNutri().getNutriValues();

        infoNutri->setColumnCount(2);
        infoNutri->setRowCount(t.size());
        infoNutri->verticalHeader()->setVisible(false);
        infoNutri->horizontalHeader()->setVisible(false);
        auto keysName = ingrToShow->getInfoNutri().getNutriKeys();


        QTableWidgetItem* itemTitle = new QTableWidgetItem();
        itemTitle->setText("Per Amount");
        infoNutri->setItem(0, 0, itemTitle);

        QTableWidgetItem* itemValue = new QTableWidgetItem();
        QString* qstr = new QString();
        qstr->append(QString::number(t.at(0) , 'G', 5));
        qstr->append(" g");
        itemValue->setText(*qstr);
        infoNutri->setItem(0, 1, itemValue);

        int i = 1;
        auto it = t.begin();
        it++;
        for (it; it != t.end(); it++) {
            QTableWidgetItem* itemTitle = new QTableWidgetItem();

            itemTitle->setText(QString::fromStdString(keysName.at(i)));
            infoNutri->setItem(i, 0, itemTitle);

            QTableWidgetItem* itemValue = new QTableWidgetItem();
            QString* qstr = new QString();
            
            if (keysName.at(i) == "sodium") {
                qstr->append(QString::number((*it)*1000, 'G', 8));
                qstr->append(" mg");
            }
            else {
                qstr->append(QString::number((*it) , 'G', 5));
                if (keysName.at(i) == "calories") {
                    qstr->append(" kcal");
                }
                else {
                    qstr->append(" g");
                }
            }
            itemValue->setText(*qstr);
            infoNutri->setItem(i, 1, itemValue);
            i++;
        }
        infoNutri->setFrameStyle(QFrame::NoFrame);


        editButton->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
        this->currentIngredientSelected = ingrToShow;
        connect(editButton, SIGNAL(clicked()), this, SLOT(editIngredientclicked()));


        QLayout* oldLayout = this->detailBox->layout();
        deleteSpecificLayout(oldLayout);
        vbox->addWidget(name, Qt::AlignCenter);
        vbox->addWidget(type, Qt::AlignCenter);
        vbox->addWidget(season, Qt::AlignCenter);
        vbox->addWidget(infoNutri, Qt::AlignCenter);
        vbox->addWidget(editButton, Qt::AlignCenter);
        this->detailBox->setLayout(vbox);

       

    }
    catch(std::exception){
        OutputDebugStringA("Error with button sender");
    }


}

void cookpp::showRecipeDetailclicked()
{
    QObject* buttonSender = QObject::sender();
    try {
        QString qs = qobject_cast<QToolButton*>(buttonSender)->text();
        std::string ss = qs.toStdString();


        QGridLayout* grid = new QGridLayout;

        Recipe* recipeToShow = new Recipe();


        QLineEdit* name = new QLineEdit("Name");
        QLineEdit* nutriScore = new QLineEdit("NutriScore");
        QTextEdit* notes = new QTextEdit("Notes");
        QTableWidget* aliments = new QTableWidget();
        QTableWidget* steps = new QTableWidget();
        QTableWidget* infoNutri = new QTableWidget();
        QString* qstr = new QString();
        int i = 0;
        auto itr = this->activeRecipeBuffer->begin();

        for (itr; itr != this->activeRecipeBuffer->end(); itr++) {
            if ((*itr)->getName() == ss) {
                recipeToShow = (*itr);
                break;
            }
        }

        name->setText(qs);
        name->setFixedSize(200, BTN_FIXED_HEIGHT);
        name->setFrame(false);
        name->setReadOnly(true);
        name->setAlignment(Qt::AlignCenter);



        *qstr = QString::fromStdString("");
        qstr->append("Score : ");
        qstr->append(QString::number(recipeToShow->getNutriScore(), 'G', 3));
        qstr->append("/100");
        nutriScore->setText(*qstr);
        nutriScore->setFixedSize(200, BTN_FIXED_HEIGHT);
        nutriScore->setFrame(false);
        nutriScore->setReadOnly(true);
        nutriScore->setAlignment(Qt::AlignCenter);




        /*----Aliments table----*/
        auto a = recipeToShow->getAliments();

        aliments->setColumnCount(2);
        aliments->setRowCount(a.size());
        aliments->verticalHeader()->setVisible(false);
        aliments->horizontalHeader()->setVisible(false);

        i = 0;
        auto it1 = a.begin();
        for (it1; it1 != a.end(); it1++) {
            QTableWidgetItem* alimName = new QTableWidgetItem();
            alimName->setText(QString::fromStdString(it1->getName()));
            aliments->setItem(i, 0, alimName);

            QTableWidgetItem* alimMass = new QTableWidgetItem();
            *qstr = QString::fromStdString("");
            qstr->append(QString::number(it1->getMass()));
            qstr->append(" g");
            alimMass->setText(*qstr);
            aliments->setItem(i, 1, alimMass);
            i++;
        }
        aliments->setFrameStyle(QFrame::NoFrame);

        
        /*----Steps table----*/
        auto s = recipeToShow->getSteps();

        steps->setColumnCount(1);
        steps->setRowCount(s.size());
        steps->setColumnWidth(0, 300);
        steps->verticalHeader()->setVisible(false);
        steps->horizontalHeader()->setVisible(false);

        i = 0;
        auto it0 = s.begin();
        for (it0; it0 != s.end(); it0++) {
            QTableWidgetItem* step = new QTableWidgetItem();
            step->setText(QString::fromStdString(*it0));
            step->setToolTip(QString::fromStdString(*it0));
            steps->setItem(i, 0, step);
            i++;
        }
        steps->setFrameStyle(QFrame::NoFrame);


        /*----Notes-----*/
        *qstr = QString::fromStdString("");
        qstr->append(QString::fromStdString(recipeToShow->getNotes()));
        notes->setText(*qstr);
        //notes->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
        //notes->setFrame(false);
        notes->setReadOnly(true);
        notes->setAlignment(Qt::AlignCenter);
        //notes->setFixedWidth(180);
        //notes->setFixedHeight(180);

        /*----Info Nutri table----*/
        auto t = recipeToShow->getInfoNutri().getNutriValues();
        infoNutri->setColumnCount(2);
        infoNutri->setRowCount(t.size());
        infoNutri->verticalHeader()->setVisible(false);
        infoNutri->horizontalHeader()->setVisible(false);
        auto keysName = recipeToShow->getInfoNutri().getNutriKeys();

        QTableWidgetItem* itemTitle = new QTableWidgetItem();
        itemTitle->setText("Per Amount");
        infoNutri->setItem(0, 0, itemTitle);

        QTableWidgetItem* itemValue = new QTableWidgetItem();
        *qstr = QString::fromStdString("");
        qstr->append(QString::number(t.at(0) , 'G', 5));
        qstr->append(" g");
        itemValue->setText(*qstr);
        infoNutri->setItem(0, 1, itemValue);

        i = 1;
        auto it = t.begin();
        it++;
        for (it; it != t.end(); it++) {
            QTableWidgetItem* itemTitle = new QTableWidgetItem();
            itemTitle->setText(QString::fromStdString(keysName.at(i)));
            infoNutri->setItem(i, 0, itemTitle);

            QTableWidgetItem* itemValue = new QTableWidgetItem();
            *qstr = QString::fromStdString("");


            if (keysName.at(i) == "sodium") {
                qstr->append(QString::number((*it)*1000, 'G', 8));
                qstr->append(" mg");
            }
            else {
                qstr->append(QString::number((*it), 'G', 5));
                if (keysName.at(i) == "calories") {
                    qstr->append(" kcal");
                }
                else {
                    qstr->append(" g");
                }
            }
            itemValue->setText(*qstr);
            infoNutri->setItem(i, 1, itemValue);
            i++;
        }
        infoNutri->setFrameStyle(QFrame::NoFrame);


        QLayout* oldLayout = this->detailBox->layout();
        deleteSpecificLayout(oldLayout);
        grid->addWidget(name, 0,0,1,2);
        grid->addWidget(nutriScore, 1, 0, 1, 2);
        grid->addWidget(notes, 2, 0, 2, 2);
        grid->addWidget(aliments, 0, 2, 4, 1);
        grid->addWidget(steps, 0,3, 4, 1);
        grid->addWidget(infoNutri, 0, 4, 4, 1);
        /*        
        grid->addWidget(name, 0,0,1,1);
        grid->addWidget(nutriScore, 0, 0, 1, 1);
        grid->addWidget(aliments, 1, 1, 2, 1);
        grid->addWidget(steps, 1, 0, 2, 1);
        grid->addWidget(notes, 3, 0, 1, 2);
        grid->addWidget(infoNutri, 3, 2, 3, 1);
        */
        //grid->setContentsMargins(-1, -1, -1, -1);
        //grid->setSpacing(1);
        this->detailBox->setLayout(grid);
    }
    catch (std::exception) {
        OutputDebugStringA("Error with button sender");
    }
}

void cookpp::showStockedAlimentDetailclicked()
{
    QObject* buttonSender = QObject::sender();
    try {
        QString qs = qobject_cast<QToolButton*>(buttonSender)->text();
        std::string ss = qs.toStdString();


        QGridLayout* grid = new QGridLayout;

        StockedAliment* stockedAlimentToShow = new StockedAliment();


        QLineEdit* name = new QLineEdit("Name");
        QLineEdit* obtainedDate = new QLineEdit("ObtainedDate");
        QLineEdit* spoilRate = new QLineEdit("SpoilRate");
        QLineEdit* spoilDate = new QLineEdit("spoilDate");
        QString* qstr = new QString();

        int i = 0;
        auto itr = this->activeStockedAlimentBuffer->begin();

        for (itr; itr != this->activeStockedAlimentBuffer->end(); itr++) {
            if ((*itr)->getName() == ss) {
                stockedAlimentToShow = (*itr);
                break;
            }
        }

        name->setText(qs);
        name->setFixedSize(200, BTN_FIXED_HEIGHT);
        name->setFrame(false);
        name->setReadOnly(true);
        name->setAlignment(Qt::AlignCenter);



        *qstr = QString::fromStdString("");
        qstr->append("Obtained date : ");
        qstr->append(QString::fromStdString(stockedAlimentToShow->getObtainedDate()));
        obtainedDate->setText(*qstr);
        obtainedDate->setFixedSize(200, BTN_FIXED_HEIGHT);
        obtainedDate->setFrame(false);
        obtainedDate->setReadOnly(true);
        obtainedDate->setAlignment(Qt::AlignCenter);

        *qstr = QString::fromStdString("");
        qstr->append("Spoils in ");
        qstr->append(QString::number(stockedAlimentToShow->getSpoilRateInDays()));
        qstr->append(" days");
        spoilRate->setText(*qstr);
        spoilRate->setFixedSize(200, BTN_FIXED_HEIGHT);
        spoilRate->setFrame(false);
        spoilRate->setReadOnly(true);
        spoilRate->setAlignment(Qt::AlignCenter);


        *qstr = QString::fromStdString("");
        qstr->append("Spoil date : ");
        qstr->append(QString::fromStdString(stockedAlimentToShow->getSpoilDate()));
        spoilDate->setText(*qstr);
        spoilDate->setFixedSize(200, BTN_FIXED_HEIGHT);
        spoilDate->setFrame(false);
        spoilDate->setReadOnly(true);
        spoilDate->setAlignment(Qt::AlignCenter);





        QLayout* oldLayout = this->detailBox->layout();
        deleteSpecificLayout(oldLayout);
        grid->addWidget(name, 0, 0, 1, 1);
        grid->addWidget(obtainedDate, 1, 0, 1, 1);
        grid->addWidget(spoilRate, 0, 1, 1, 1);
        grid->addWidget(spoilDate, 1, 1, 1, 1);
        ;
        this->detailBox->setLayout(grid);
    }
    catch (std::exception) {
        OutputDebugStringA("Error with button sender");
    }
}

void cookpp::saveIngredientEditclicked()
{
    saveIngredientEdit();

    

}

void cookpp::editIngredientclicked()
{
    ingredientEditor();
}



void cookpp::gotoMainMenuclicked()
{
    displayMainMenu();
}










QGroupBox* cookpp::createFirstExclusiveGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("Exclusive Radio Buttons"));

    QRadioButton* radio1 = new QRadioButton(tr("&Radio button 1"));
    QRadioButton* radio2 = new QRadioButton(tr("R&adio button 2"));
    QRadioButton* radio3 = new QRadioButton(tr("Ra&dio button 3"));

    radio1->setChecked(true);
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    groupBox->close();

    return groupBox;
}

QGroupBox* cookpp::createSecondExclusiveGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("E&xclusive Radio Buttons"));
    groupBox->setCheckable(true);
    groupBox->setChecked(false);
    QRadioButton* radio1 = new QRadioButton(tr("Rad&io button 1"));
    QRadioButton* radio2 = new QRadioButton(tr("Radi&o button 2"));
    QRadioButton* radio3 = new QRadioButton(tr("Radio &button 3"));
    radio1->setChecked(true);
    QCheckBox* checkBox = new QCheckBox(tr("Ind&ependent checkbox"));
    checkBox->setChecked(true);
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addWidget(checkBox);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

QGroupBox* cookpp::createNonExclusiveGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("Non-Exclusive Checkboxes"));
    groupBox->setFlat(true);
    QCheckBox* checkBox1 = new QCheckBox(tr("&Checkbox 1"));
    QCheckBox* checkBox2 = new QCheckBox(tr("C&heckbox 2"));
    checkBox2->setChecked(true);
    QCheckBox* tristateBox = new QCheckBox(tr("Tri-&state button"));
    tristateBox->setTristate(true);
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(checkBox1);
    vbox->addWidget(checkBox2);
    vbox->addWidget(tristateBox);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

QGroupBox* cookpp::createPushButtonGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("&Push Buttons"));
    groupBox->setCheckable(true);
    groupBox->setChecked(true);
    QPushButton* pushButton = new QPushButton(tr("&Normal Button"));
    QPushButton* toggleButton = new QPushButton(tr("&Toggle Button"));
    toggleButton->setCheckable(true);
    toggleButton->setChecked(true);
    QPushButton* flatButton = new QPushButton(tr("&Flat Button"));
    flatButton->setFlat(true);
    QPushButton* popupButton = new QPushButton(tr("Pop&up Button"));
    QMenu* menu = new QMenu(this);
    menu->addAction(tr("&First Item"));
    menu->addAction(tr("&Second Item"));
    menu->addAction(tr("&Third Item"));
    menu->addAction(tr("F&ourth Item"));
    popupButton->setMenu(menu);
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(pushButton);
    vbox->addWidget(toggleButton);
    vbox->addWidget(flatButton);
    vbox->addWidget(popupButton);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}
