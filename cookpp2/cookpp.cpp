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

    setMinimumSize(650, 480);
    setMaximumSize(651, 481);
    resize(650, 480);

}

cookpp::~cookpp()
{}

void cookpp::displayMainMenu() {

    deleteCurrentView();

    QGridLayout* mainGrid = new QGridLayout;
    mainGrid->addWidget(createMainMenuBox(), 0, 0, 2, 2);
    mainGrid->addWidget(createSecondExclusiveGroup(), 0, 2, 2, 2);
    mainGrid->addWidget(createDebugOutput(), 3, 0 , 1, 4);
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


void cookpp::displayAllIngredients()
{
    //Delete old layout to drwn the new https://forum.qt.io/topic/14898/howto-change-layout-of-a-widget/10
    deleteCurrentView();


    QGridLayout* mainLayout = new QGridLayout;


    std::list<Ingredient*>  listIngredient;
    int maxPage = 1;
    try {
        listIngredient = this->facade->getAllIngredient();
        int maxPage = floor(listIngredient.size() / NUMBER_OBJET_PER_PAGE);
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
        int maxPage = floor(listRecipe.size() / NUMBER_OBJET_PER_PAGE);
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
        qstr->append(QString::number(t.at(0)));
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

            qstr->append(QString::number(*it));
            if (keysName.at(i) == "calories") {
                qstr->append(" kcal");
            }
            else {
                qstr->append(" g");
            }
            itemValue->setText(*qstr);
            infoNutri->setItem(i, 1, itemValue);
            i++;
        }
        infoNutri->setFrameStyle(QFrame::NoFrame);


        QLayout* oldLayout = this->detailBox->layout();
        deleteSpecificLayout(oldLayout);
        vbox->addWidget(name, Qt::AlignCenter);
        vbox->addWidget(type, Qt::AlignCenter);
        vbox->addWidget(season, Qt::AlignCenter);
        vbox->addWidget(infoNutri, Qt::AlignCenter);
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
        QLineEdit* notes = new QLineEdit("Notes");
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
        name->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
        name->setFrame(false);
        name->setReadOnly(true);
        name->setAlignment(Qt::AlignLeft);



        *qstr = QString::fromStdString("");
        qstr->append("Score : ");
        nutriScore->setText(QString::number(recipeToShow->getNutriScore()));
        qstr->append(" /100");
        nutriScore->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
        nutriScore->setFrame(false);
        nutriScore->setReadOnly(true);
        nutriScore->setAlignment(Qt::AlignRight);




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
        steps->verticalHeader()->setVisible(false);
        steps->horizontalHeader()->setVisible(false);

        i = 0;
        auto it0 = s.begin();
        for (it0; it0 != s.end(); it0++) {
            QTableWidgetItem* step = new QTableWidgetItem();
            step->setText(QString::fromStdString(*it0));
            steps->setItem(i, 0, step);
            i++;
        }
        steps->setFrameStyle(QFrame::NoFrame);


        /*----Notes-----*/
        *qstr = QString::fromStdString("");
        qstr->append(QString::fromStdString(recipeToShow->getNotes()));
        notes->setText(*qstr);
        notes->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
        notes->setFrame(false);
        notes->setReadOnly(true);
        notes->setAlignment(Qt::AlignCenter);

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
        qstr->append(QString::number(t.at(0)));
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
            qstr->append(QString::number(*it));
            qstr->append(" mg");
            itemValue->setText(*qstr);
            infoNutri->setItem(i, 1, itemValue);
            i++;
        }
        infoNutri->setFrameStyle(QFrame::NoFrame);


        QLayout* oldLayout = this->detailBox->layout();
        deleteSpecificLayout(oldLayout);
        grid->addWidget(name, 0,0,1,1);
        grid->addWidget(nutriScore, 0, 0, 1, 1);
        grid->addWidget(aliments, 1, 0, 2, 1);
        grid->addWidget(steps, 1, 1, 2, 1);
        grid->addWidget(notes, 3, 0, 1, 2);
        grid->addWidget(infoNutri, 3, 1, 2, 1);
        this->detailBox->setLayout(grid);
    }
    catch (std::exception) {
        OutputDebugStringA("Error with button sender");
    }
}
