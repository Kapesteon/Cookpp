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

#define BTN_REMOVE_ALIMENT_SEPARATOR "&-Aliment:"

cookpp::cookpp(QWidget *parent)
    : QWidget(parent)
{
    initDb();

    QVBoxLayout* mainLayout = new QVBoxLayout(this); // Main layout of widget
    this->facade = new FacadeUserDB();
    this->detailBox = new QGroupBox(tr("Details"));
    this->messageOutput = new QTextEdit(tr("Messages :"));
    this->currentPantrySelected = new Pantry;


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

    //QGridLayout* mainGrid = new QGridLayout;
    //QTabWidget* tabwid = new QTabWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout();
    //if you want to set margins : 
    QLabel* title;
    title = new QLabel(tr("Cook++"));
    title->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    title->setStyleSheet("font: 18pt;");

    QToolButton* generateMenuButton = new QToolButton();
    QToolButton* editPantryButton = new QToolButton();
    generateMenuButton->setText(tr("Generate Menu"));
    editPantryButton->setText(tr("Edit Pantry"));
    generateMenuButton->setFixedSize(BTN_FIXED_WIDTH*2, BTN_FIXED_HEIGHT*2);
    editPantryButton->setFixedSize(BTN_FIXED_WIDTH *2, BTN_FIXED_HEIGHT*2);
    
    connect(generateMenuButton, SIGNAL(clicked()), this, SLOT(gotoGenerateMenuclicked()));
    connect(editPantryButton, SIGNAL(clicked()), this, SLOT(editPantryclicked()));

    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->addWidget(title); // center alignment
    mainLayout->addWidget(generateMenuButton); // center alignment
    mainLayout->addWidget(editPantryButton); // center alignment
    mainLayout->setAlignment(generateMenuButton, Qt::AlignHCenter);
    mainLayout->setAlignment(editPantryButton, Qt::AlignHCenter);
    /*
    mainLayout->addWidget(title,0,0); // center alignment
    mainLayout->addWidget(generateMenuButton,0,1); // center alignment
    mainLayout->addWidget(editPantryButton,0,2); // center alignment
    */
    setLayout(mainLayout);
 
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




/*---------------INGREDIENTS------------*/
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
            double f = (float(listIngredient.size()) / float(NUMBER_OBJET_PER_PAGE));
            maxPage = floor(f);
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







/*----------RECIPES--------*/
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
            double f = (float(listRecipe.size()) / float(NUMBER_OBJET_PER_PAGE));
            maxPage = floor(f);
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

void cookpp::recipeEditor()
{
    try {
        deleteCurrentView();

        QFormLayout* mainLayout = new QFormLayout;
        //QGridLayout* grid = new QGridLayout;
        QHBoxLayout* hbox = new QHBoxLayout;
        QLineEdit* name = new QLineEdit("Name");
        QTableWidget* aliments = new QTableWidget();
        QTableWidget* steps = new QTableWidget();
        QTextEdit* notes = new QTextEdit("Notes");
        QToolButton* markAsCompleteButton = new QToolButton();
        QDialogButtonBox* dialogButton = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        /*--*/
        QComboBox* alimentDrop = new QComboBox();
        Recipe* toEdit = this->currentRecipeSelected;


        QString* qstr = new QString();
        *qstr = QString::fromStdString("");
        qstr->append(QString::fromStdString(toEdit->getName()));
        name->setText(*qstr);
        name->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
        if (toEdit->getName() != "N/A") {
            name->setFrame(false);
            name->setReadOnly(true);
        }
        else {
            name->setFrame(true);
            name->setReadOnly(false);
        }
        name->setAlignment(Qt::AlignCenter);
        name->setObjectName("name");

        *qstr = QString::fromStdString("");
        qstr->append(QString::fromStdString(toEdit->getNotes()));
        notes->setText(*qstr);
        notes->setFixedSize(BTN_FIXED_WIDTH*3, BTN_FIXED_HEIGHT*5);
        notes->setObjectName("notes");

        /*--------Aliments table----------*/
        auto alimList = toEdit->getAliments();
        this->setupRecipeAlimentsTable(aliments, &alimList);
        aliments->setObjectName("aliments");

        /*---------  Steps Table   --------------*/
        auto stepsList = toEdit->getSteps();
        this->setupRecipeStepsTable(steps, &stepsList);
        steps->setObjectName("steps");


        //connect(dialogButton, SIGNAL(accepted()), &dialog, SLOT(accept()));
        connect(dialogButton, SIGNAL(accepted()), this, SLOT(saveRecipeEditclicked()));
        connect(dialogButton, SIGNAL(rejected()), this, SLOT(gotoMainMenuclicked()));


        QLayout* oldLayout = this->detailBox->layout();
        deleteSpecificLayout(oldLayout);


        hbox->addWidget(name, Qt::AlignCenter);
        hbox->addWidget(aliments, Qt::AlignCenter);
        hbox->addWidget(steps, Qt::AlignCenter);
        hbox->addWidget(notes, Qt::AlignCenter);
        hbox->addWidget(dialogButton, Qt::AlignCenter);
        /*
        vbox->addWidget(name, Qt::AlignCenter);
        vbox->addWidget(aliments, Qt::AlignCenter);
        vbox->addWidget(steps, Qt::AlignCenter);
        vbox->addWidget(notes, Qt::AlignCenter);
        vbox->addWidget(dialogButton, Qt::AlignCenter);
        */
        /*
        grid->addWidget(name, 0, 0, 1, 2);
        grid->addWidget(notes, 1, 0, 2, 2);
        grid->addWidget(aliments, 0, 2, 4, 1);
        grid->addWidget(steps, 0, 3, 4, 1);
        grid->addWidget(dialogButton,3,0,1,2);
        */

        this->detailBox->setLayout(hbox);
        mainLayout->addWidget(this->detailBox);
        setLayout(mainLayout);
        setWindowTitle(tr("Cook++ - Recipe"));


    }
    catch (std::exception) {
        OutputDebugStringA("Error with button sender");
    }
}

void cookpp::saveRecipeEdit()
{
    
    Recipe* toSave = this->currentRecipeSelected;
    auto list = this->facade->getAllRecipe();
    int writeIndex = list.size();
    //See where to write the current ingredient
    int i = 0;
    for (auto it = list.begin(); it != list.end(); it++) {
        if ((*it)->getName() == toSave->getName()) {
            break;
        }
        i++;
    }
    writeIndex = i;
    toSave->markAsComplete();
    this->facade->saveRecipe(toSave, writeIndex);
    //this->facade->addIngredient(toAdd);



    displayAllRecipes();
}

void cookpp::setupRecipeAlimentsTable(QTableWidget* aliments, std::vector<Aliment> * alimList)
{
    aliments->setColumnCount(3);
    aliments->setRowCount(alimList->size() + 2);
    aliments->verticalHeader()->setVisible(false);
    aliments->horizontalHeader()->setVisible(false);

    QComboBox* alimentDrop;
    QString* qstr = new QString();
    /*--Headers of table Aliment */
    QTableWidgetItem* colTitle = new QTableWidgetItem();
    QTableWidgetItem* colMass = new QTableWidgetItem();
    QTableWidgetItem* colBtn = new QTableWidgetItem();
    colTitle->setText("Aliment");
    colMass->setText("Mass (g)");
    colBtn->setText("");
    colTitle->setFlags(Qt::NoItemFlags);
    colMass->setFlags(Qt::NoItemFlags);
    colBtn->setFlags(Qt::NoItemFlags);
    aliments->setItem(0, 0, colTitle);
    aliments->setItem(0, 1, colMass);
    aliments->setItem(0, 2, colBtn);
    aliments->setColumnWidth(2, 20);
    *qstr = QString::fromStdString("");
    QWidget* pWidget = new QWidget();
    QPushButton* btn_edit = new QPushButton();
    QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
    auto allExistingAliments = this->facade->getAllIngredient();
    int i = 1;
    auto it = alimList->begin();
    for (it; it != alimList->end(); it++) {
        QTableWidgetItem* cellName = new QTableWidgetItem();
        QTableWidgetItem* cellMass = new QTableWidgetItem();
        QTableWidgetItem* cellButtonRemove = new QTableWidgetItem();
        QToolButton* buttonRemove = new QToolButton();

        *qstr = QString::fromStdString("");
        *qstr = QString::fromStdString(it->getName());
        cellName->setText(*qstr);

        *qstr = QString::fromStdString("");
        qstr->append(QString::number(it->getMass()));
        cellMass->setText(*qstr);


        /*Set Remove button*/
        *qstr = QString::fromStdString("");
        *qstr = QString::fromStdString(BTN_REMOVE_ALIMENT_SEPARATOR);
        *qstr = QString::fromStdString(it->getName());
        buttonRemove->setObjectName(*qstr);
        buttonRemove->setText(tr(" - "));
        buttonRemove->setFixedSize(20, 20);
        connect(buttonRemove, SIGNAL(clicked()), this, SLOT(removeAlimentFromRecipeclicked()));
        cellButtonRemove->setFlags(Qt::NoItemFlags);
        pWidget = new QWidget();
        btn_edit = new QPushButton();
        pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(buttonRemove);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);
        aliments->setCellWidget(i, 2, pWidget);

        /*Set Dropdown aliment*/
        alimentDrop = new QComboBox();
        for (auto it0 = allExistingAliments.begin(); it0 != allExistingAliments.end(); it0++) {
            *qstr = QString::fromStdString("");
            *qstr = QString::fromStdString((*it0)->getName());
            alimentDrop->addItem(*qstr);
        }
        Ingredient bufferIngr = static_cast<Ingredient>(*it);
        int index = this->facade->getIngredientIndex(&bufferIngr);
        alimentDrop->setCurrentIndex(index);
        alimentDrop->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
        alimentDrop->setFrame(true);
        pWidget = new QWidget();
        pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(alimentDrop);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);
        aliments->setCellWidget(i, 0, pWidget);
        aliments->setItem(i, 1, cellMass);

        i++;
    }



    /*-- Button add at the end of Table--*/
    QTableWidgetItem* cellAddButton = new QTableWidgetItem();
    pWidget = new QWidget();
    QPushButton* btnAdd = new QPushButton();
    pLayout = new QHBoxLayout(pWidget);
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(addNewAlimentInRecipeclicked()));
    btnAdd->setText("+");
    pLayout->addWidget(btnAdd);
    pLayout->setAlignment(Qt::AlignCenter);
    pLayout->setContentsMargins(0, 0, 0, 0);
    pWidget->setLayout(pLayout);
    aliments->setCellWidget(i, 2, pWidget);
    aliments->addScrollBarWidget(new QScrollBar(), Qt::AlignLeft);
}

void cookpp::setupRecipeStepsTable(QTableWidget* steps, std::vector<std::string>* stepsList)
{
    {

        steps->setColumnCount(2);
        steps->setRowCount(stepsList->size() + 2);
        steps->horizontalHeader()->setVisible(false);


        QComboBox* alimentDrop;
        QString* qstr = new QString();
        /*--Headers of table Steps */
        QTableWidgetItem* colString = new QTableWidgetItem();
        QTableWidgetItem* colBtn = new QTableWidgetItem();
        colString->setText("Steps");
        colBtn->setText("");
        colString->setFlags(Qt::NoItemFlags);
        colBtn->setFlags(Qt::NoItemFlags);
        steps->setItem(0, 0, colString);
        steps->setItem(0, 1, colBtn);
        steps->setColumnWidth(0, 200);
        steps->setColumnWidth(1, 20);

        *qstr = QString::fromStdString("");
        QWidget* pWidget = new QWidget();
        QPushButton* btn_edit = new QPushButton();
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        int i = 1;
        auto it = stepsList->begin();
        for (it; it != stepsList->end(); it++) {
            QTableWidgetItem* cellString = new QTableWidgetItem();
            QTableWidgetItem* cellButtonRemove = new QTableWidgetItem();
            QToolButton* buttonRemove = new QToolButton();

            *qstr = QString::fromStdString("");
            *qstr = QString::fromStdString(*it);
            cellString->setText(*qstr);


            /*Set Remove button*/
            *qstr = QString::fromStdString("");
            *qstr = QString::number(i-1);
            buttonRemove->setObjectName(*qstr);
            buttonRemove->setText(tr(" - "));
            buttonRemove->setFixedSize(20, 20);
            connect(buttonRemove, SIGNAL(clicked()), this, SLOT(removeStepFromRecipeclicked()));
            cellButtonRemove->setFlags(Qt::NoItemFlags);
            pWidget = new QWidget();
            btn_edit = new QPushButton();
            pLayout = new QHBoxLayout(pWidget);
            pLayout->addWidget(buttonRemove);
            pLayout->setAlignment(Qt::AlignCenter);
            pLayout->setContentsMargins(0, 0, 0, 0);
            pWidget->setLayout(pLayout);
            steps->setCellWidget(i, 1, pWidget);

       
            steps->setItem(i, 0, cellString);

            i++;
        }



        /*-- Button add at the end of Table--*/
        QTableWidgetItem* cellAddButton = new QTableWidgetItem();
        pWidget = new QWidget();
        QPushButton* btnAdd = new QPushButton();
        pLayout = new QHBoxLayout(pWidget);
        connect(btnAdd, SIGNAL(clicked()), this, SLOT(addNewStepInRecipeclicked()));
        btnAdd->setText("+");
        pLayout->addWidget(btnAdd);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);
        steps->setCellWidget(i, 1, pWidget);
        steps->addScrollBarWidget(new QScrollBar(), Qt::AlignLeft);
    }
}

void cookpp::updateCurrentRecipeSelected()
{
    Recipe * recipeCopy = this->currentRecipeSelected;
    std::string recipeName = std::string();
    std::string recipeNotes = std::string();
    Ingredient* bufferIngredient;
    Aliment * bufferAliment;
    std::vector<Aliment>* alimentsToCopy = new std::vector<Aliment>;
    std::string* notesToCopy = new std::string;


    for (int i = 0; i < this->detailBox->layout()->count(); ++i)
    {
        QWidget* widget = this->detailBox->layout()->itemAt(i)->widget();
        if (widget != NULL)
        {
            QString qname = widget->objectName();
            std::string sname = qname.toStdString();
            if (sname == "name") {
                QLineEdit* item = qobject_cast<QLineEdit*>(widget);
                recipeName = item->text().toStdString();
                recipeCopy->setName(recipeName);
            }
            else if (sname == "notes") {
                QTextEdit* item = qobject_cast<QTextEdit*>(widget);
                recipeNotes = item->toPlainText().toStdString();
                recipeCopy->setNotes(recipeNotes);
            }
            else if (sname == "aliments") {
                QTableWidget* table = qobject_cast<QTableWidget*>(widget);
                //Row = 1 to account for header      //rowCount()-1 to account for footer "addButton"
                for (int row = 1; row < table->rowCount()-1; ++row) {
                    //std::string rowAlimentName = table->item(row, 0)->text().toStdString();
                    double mass = table->item(row, 1)->text().toDouble();

                    auto w = table->cellWidget(row, 0)->layout()->itemAt(0)->widget();
                    QComboBox* dropDownCell = qobject_cast<QComboBox*>(w);
                    std::string rowAlimentName = dropDownCell->currentText().toStdString();
                    bufferIngredient = new Ingredient;
                    *bufferIngredient = this->facade->getIngredientByName(rowAlimentName);
                    bufferAliment = new Aliment(*bufferIngredient,mass);


                    alimentsToCopy->push_back(*bufferAliment);

                }
                recipeCopy->setAliments(*alimentsToCopy);


            }
            else if (sname == "steps") {
                QTableWidget* table = qobject_cast<QTableWidget*>(widget);
                //Row = 1 to account for header      //rowCount()-1 to account for footer "addButton"
                for (int row = 1; row < table->rowCount()-1; ++row) {
                    std::string step = table->item(row, 0)->text().toStdString();
                    recipeCopy->setStep(step, row - 1);
                }

            }
        }
        else
        {

        }



    }

    this->currentRecipeSelected = recipeCopy;

    return;
}





/*------------PANTRY------------*/
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

void cookpp::pantryEditor() {
    try {
        deleteCurrentView();

        QFormLayout* mainLayout = new QFormLayout;
        QHBoxLayout* hbox = new QHBoxLayout;
        QTableWidget* stockedAliments = new QTableWidget();
        QDialogButtonBox* dialogButton = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        /*--*/
        QComboBox* alimentDrop = new QComboBox();
        Pantry* toEdit = this->currentPantrySelected;

        /*--------Aliments table----------*/
        auto alimList = toEdit->getStockAsList();
        this->setupPantryAlimentTable(stockedAliments, &alimList);
        stockedAliments->setObjectName("stockedAliments");


        //connect(dialogButton, SIGNAL(accepted()), &dialog, SLOT(accept()));
        connect(dialogButton, SIGNAL(accepted()), this, SLOT(savePantryEditclicked())); //TO IMPLETMENT
        connect(dialogButton, SIGNAL(rejected()), this, SLOT(gotoMainMenuclicked()));


        QLayout* oldLayout = this->detailBox->layout();
        deleteSpecificLayout(oldLayout);

        hbox->addWidget(stockedAliments, Qt::AlignCenter);
        hbox->addWidget(dialogButton, Qt::AlignCenter);

        this->detailBox->setLayout(hbox);
        mainLayout->addWidget(this->detailBox);
        setLayout(mainLayout);
        setWindowTitle(tr("Cook++ - Pantry"));


    }
    catch (std::exception) {
        OutputDebugStringA("Error with button sender");
    }
}

void cookpp::setupPantryAlimentTable(QTableWidget* stockedAliments, std::list<StockedAliment*>* alimList)
{
    stockedAliments->setColumnCount(5);
    stockedAliments->setRowCount(alimList->size() + 2);
    stockedAliments->verticalHeader()->setVisible(false);
    stockedAliments->horizontalHeader()->setVisible(false);

    QComboBox* alimentDrop;
    QString* qstr = new QString();
    /*--Headers of table Aliment */
    QTableWidgetItem* colTitle = new QTableWidgetItem();
    QTableWidgetItem* colMass = new QTableWidgetItem();
    QTableWidgetItem* colObtainedDate = new QTableWidgetItem();
    QTableWidgetItem* colSpoilRate = new QTableWidgetItem();
    QTableWidgetItem* colBtn = new QTableWidgetItem();
    colTitle->setText("Aliment");
    colTitle->setToolTip("Aliment");
    colMass->setText("Mass (g)");
    colMass->setToolTip("Mass (g)");
    colObtainedDate->setText("Date Obtained");
    colObtainedDate->setToolTip("Date Obtained");
    colSpoilRate->setText("Days before Spoilage");
    colSpoilRate->setToolTip("Days before Spoilage");
    colBtn->setText("");
    colTitle->setFlags(Qt::NoItemFlags);
    colMass->setFlags(Qt::NoItemFlags);
    colObtainedDate->setFlags(Qt::NoItemFlags);
    colSpoilRate->setFlags(Qt::NoItemFlags);
    colBtn->setFlags(Qt::NoItemFlags);
    stockedAliments->setItem(0, 0, colTitle);
    stockedAliments->setItem(0, 1, colMass);
    stockedAliments->setItem(0, 2, colObtainedDate);
    stockedAliments->setItem(0, 3, colSpoilRate);
    stockedAliments->setItem(0, 4, colBtn);
    stockedAliments->setColumnWidth(4, 20);
    *qstr = QString::fromStdString("");
    QWidget* pWidget = new QWidget();
    QPushButton* btn_edit = new QPushButton();
    QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
    auto allExistingAliments = this->facade->getAllIngredient();
    int i = 1;
    auto it = alimList->begin();
    for (it; it != alimList->end(); it++) {
        QTableWidgetItem* cellName = new QTableWidgetItem();
        QTableWidgetItem* cellMass = new QTableWidgetItem();
        QTableWidgetItem* cellObtainedDate = new QTableWidgetItem();
        QTableWidgetItem* cellSpoilRate = new QTableWidgetItem();
        QTableWidgetItem* cellButtonRemove = new QTableWidgetItem();
        QToolButton* buttonRemove = new QToolButton();

        /* Name cell*/
        *qstr = QString::fromStdString("");
        *qstr = QString::fromStdString((*it)->getName());
        cellName->setText(*qstr);

        /* Mass cell*/
        *qstr = QString::fromStdString("");
        qstr->append(QString::number((*it)->getMass()));
        cellMass->setText(*qstr);

        /* Obtained Date cell*/
        *qstr = QString::fromStdString("");
        qstr->append(QString::fromStdString((*it)->getObtainedDate()));
        cellObtainedDate->setText(*qstr);

        /* Spoil Rate cell*/
        *qstr = QString::fromStdString("");
        qstr->append(QString::number((*it)->getSpoilRateInDays()));
        cellSpoilRate->setText(*qstr);


        /*Set Remove button*/
        *qstr = QString::fromStdString("");
        *qstr = QString::number(i-1); //-1 to account for header row
        buttonRemove->setObjectName(*qstr);
        buttonRemove->setText(tr(" - "));
        buttonRemove->setFixedSize(20, 20);
        connect(buttonRemove, SIGNAL(clicked()), this, SLOT(removeStockedAlimentFromPantryclicked()));
        cellButtonRemove->setFlags(Qt::NoItemFlags);
        pWidget = new QWidget();
        btn_edit = new QPushButton();
        pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(buttonRemove);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);



        stockedAliments->setItem(i, 0, cellName);
        stockedAliments->setItem(i, 1, cellMass);
        stockedAliments->setItem(i, 2, cellObtainedDate);
        stockedAliments->setItem(i, 3, cellSpoilRate);
        stockedAliments->setCellWidget(i, 4, pWidget);
        i++;
    }


    /*Set Dropdown aliment*/
    alimentDrop = new QComboBox();
    for (auto it0 = allExistingAliments.begin(); it0 != allExistingAliments.end(); it0++) {
        *qstr = QString::fromStdString("");
        *qstr = QString::fromStdString((*it0)->getName());
        alimentDrop->addItem(*qstr);
    }
    alimentDrop->setCurrentIndex(0);
    alimentDrop->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
    alimentDrop->setFrame(true);
    pWidget = new QWidget();
    pLayout = new QHBoxLayout(pWidget);
    pLayout->addWidget(alimentDrop);
    pLayout->setAlignment(Qt::AlignCenter);
    pLayout->setContentsMargins(0, 0, 0, 0);
    pWidget->setLayout(pLayout);
    stockedAliments->setCellWidget(stockedAliments->rowCount()-1, 0, pWidget);

    /* Mass cell*/
    QTableWidgetItem* cellMass = new QTableWidgetItem();
    *qstr = QString::fromStdString("");
    qstr->append(QString::number(0));
    cellMass->setText(*qstr);
    stockedAliments->setItem(stockedAliments->rowCount() - 1, 1, cellMass);

    /* Obtained Date cell*/
    QTableWidgetItem* cellObtainedDate = new QTableWidgetItem();
    *qstr = QString::fromStdString("");
    qstr->append(QString::fromStdString("2022/12/31"));
    cellObtainedDate->setText(*qstr);
    stockedAliments->setItem(stockedAliments->rowCount() - 1, 2, cellObtainedDate);

    /* Spoil Rate cell*/
    QTableWidgetItem* cellSpoilRate = new QTableWidgetItem();
    *qstr = QString::fromStdString("");
    qstr->append(QString::number(0));
    cellSpoilRate->setText(*qstr);
    stockedAliments->setItem(stockedAliments->rowCount() - 1, 3, cellSpoilRate);

    /*-- Button add at the end of Table--*/
    QTableWidgetItem* cellAddButton = new QTableWidgetItem();
    pWidget = new QWidget();
    QPushButton* btnAdd = new QPushButton();
    pLayout = new QHBoxLayout(pWidget);
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(addNewStockedAlimentInPantryclicked()));
    btnAdd->setText("+");
    pLayout->addWidget(btnAdd);
    pLayout->setAlignment(Qt::AlignCenter);
    pLayout->setContentsMargins(0, 0, 0, 0);
    pWidget->setLayout(pLayout);
    stockedAliments->setCellWidget(stockedAliments->rowCount() - 1, 4, pWidget);

    stockedAliments->addScrollBarWidget(new QScrollBar(), Qt::AlignLeft);
}

void cookpp::updateCurrentPantrySelected(bool isLastRowAdded) {
    Pantry* pantryCopy = this->currentPantrySelected;
    std::string stockedAlimentName = std::string();
    std::string stockedAlimentObtainedDate = std::string();
    int stockedAlimentSpoilRateInt = int();
    Ingredient* bufferIngredient;
    StockedAliment* bufferStockedAliment;
    std::vector<StockedAliment> alimentsToCopy =  std::vector<StockedAliment>();


    for (int i = 0; i < this->detailBox->layout()->count(); ++i)
    {
        QWidget* widget = this->detailBox->layout()->itemAt(i)->widget();
        if (widget != NULL)
        {
            QString qname = widget->objectName();
            std::string sname = qname.toStdString();
            if (sname == "stockedAliments") {
                QTableWidget* table = qobject_cast<QTableWidget*>(widget);
                //Row = 1 to account for header      //rowCount()-1 to account for footer "addButton"
                for (int row = 1; row < table->rowCount() - 1; ++row) {
                    std::string name            = table->item(row, 0)->text().toStdString();
                    double mass                 = table->item(row, 1)->text().toDouble();
                    std::string obtainedDate    = table->item(row, 2)->text().toStdString();
                    int spoilRateDays           = table->item(row, 3)->text().toInt();

                    bufferIngredient = new Ingredient;
                    bufferStockedAliment = new StockedAliment;
                    *bufferIngredient = this->facade->getIngredientByName(name);
                    *bufferStockedAliment = StockedAliment(*bufferIngredient, mass, obtainedDate, spoilRateDays);



                    alimentsToCopy.push_back(*bufferStockedAliment);

                }
                if (isLastRowAdded) {
                    int lastRow = table->rowCount() - 1;
                    auto w = table->cellWidget(lastRow, 0)->layout()->itemAt(0)->widget();
                    QComboBox* dropDownCell = qobject_cast<QComboBox*>(w);
                    std::string name = dropDownCell->currentText().toStdString();
                    double mass = table->item(lastRow, 1)->text().toDouble();
                    std::string obtainedDate = table->item(lastRow, 2)->text().toStdString();
                    int spoilRateDays = table->item(lastRow, 3)->text().toInt();

                    bufferIngredient = new Ingredient;
                    *bufferIngredient = this->facade->getIngredientByName(name);
                    bufferStockedAliment = new StockedAliment(*bufferIngredient, mass, obtainedDate, spoilRateDays);
                    alimentsToCopy.push_back(*bufferStockedAliment);

                    
                }

                pantryCopy->setStock(alimentsToCopy);

            }

        }


    }

    this->currentPantrySelected = pantryCopy;

    return;
}

void cookpp::savePantryEdit() {
    Pantry* toSave = this->currentPantrySelected;

    this->facade->savePantry(toSave);


    displayPantry();
}


/*------------MENU GEN-------------*/

void cookpp::menuGenerator() {
    deleteCurrentView();

    QLabel* nDaysLabel;
    QLabel* nCoversLabel;

    QLineEdit* nDaysEdit;
    QLineEdit* nCoversEdit;

    QDialogButtonBox* buttonBox;

    nDaysLabel = new QLabel(tr("Number of days:"));
    nDaysLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    nCoversLabel = new QLabel(tr("Servings per day:"));
    nCoversLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    nDaysEdit = new QLineEdit;
    nDaysEdit->setObjectName("nDaysEdit");
    nDaysEdit->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
    nCoversEdit = new QLineEdit;
    nCoversEdit->setObjectName("nCoversEdit");
    nCoversEdit->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);

    this->messageOutput = new QTextEdit;
    this->messageOutput->setObjectName("outputBox");
    this->messageOutput->setReadOnly(true);
    this->messageOutput->setAlignment(Qt::AlignLeft);


    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
        | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(generateMenuclicked()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(gotoMainMenuclicked()));

    QLayout* oldLayout = this->detailBox->layout();
    deleteSpecificLayout(oldLayout);
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(nDaysLabel, 0, 0);
    mainLayout->addWidget(nDaysEdit, 0, 1);
    mainLayout->addWidget(nCoversLabel, 1, 0);
    mainLayout->addWidget(nCoversEdit, 1, 1);
    mainLayout->addWidget(messageOutput, 0, 2, 2, 1);
    mainLayout->addWidget(buttonBox, 3, 0, 1, 3);
    setLayout(mainLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Cook++ - Menu"));


}



/*-------------UTILITY--------------*/
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
    mnGenerateMenuAct = new QAction(tr("&Generate Menu"), this);
    mnExitAct = new QAction(tr("&Exit"), this);

    mnAddRecipeAct = new QAction(tr("&Add New Recipe"), this);
    mnAddIngredientAct = new QAction(tr("&Add New Ingredient"), this);
    mnEditPantryAct = new QAction(tr("&Edit Pantry"), this);

    mnViewIngredientsAct = new QAction(tr("&View Ingredients"), this);
    mnViewRecipesAct = new QAction(tr("&View Recipes"), this);
    mnViewPantryAct = new QAction(tr("&View Pantry"), this);

    mnaboutAct = new QAction(tr("&About"), this);

    /*----------Act Properties Setup--------------*/
    mnMainMenuAct->setShortcuts(QKeySequence::New);
    mnMainMenuAct->setStatusTip(tr("Go to Main Menu"));
    connect(mnMainMenuAct, &QAction::triggered, this, &cookpp::mnMainMenu);


    mnGenerateMenuAct->setStatusTip(tr("Generate Menu"));
    connect(mnGenerateMenuAct, &QAction::triggered, this, &cookpp::mnGenerateMenu);


    mnViewIngredientsAct->setStatusTip(tr("View all known ingredients"));
    connect(mnViewIngredientsAct, &QAction::triggered, this, &cookpp::mnViewIngredients);

    mnViewRecipesAct->setStatusTip(tr("View all known recipes"));
    connect(mnViewRecipesAct, &QAction::triggered, this, &cookpp::mnViewRecipes);

    mnViewPantryAct->setStatusTip(tr("View Stocked Aliments in Pantry "));
    connect(mnViewPantryAct, &QAction::triggered, this, &cookpp::mnViewPantry);

    mnAddIngredientAct->setStatusTip(tr("Create a new Ingredient"));
    connect(mnAddIngredientAct, &QAction::triggered, this, &cookpp::mnAddIngredient);

    mnAddRecipeAct->setStatusTip(tr("Create a new Recipe"));
    connect(mnAddRecipeAct, &QAction::triggered, this, &cookpp::mnAddRecipe);

    mnEditPantryAct->setStatusTip(tr("Edit Pantry"));
    connect(mnEditPantryAct, &QAction::triggered, this, &cookpp::mnEditPantry);


}

void cookpp::createMenus()
{
    this->menuBar = new QMenuBar();
    menuBar->setNativeMenuBar(false);

    QMenu * fileMenu = menuBar->addMenu(tr("&File"));
    //fileMenu->addAction(mnNewAct);
    fileMenu->addAction(mnMainMenuAct);
    fileMenu->addSeparator();
    fileMenu->addAction(mnGenerateMenuAct);
    fileMenu->addSeparator();
    fileMenu->addAction(mnExitAct);

    QMenu* editMenu = menuBar->addMenu(tr("&Edit"));
    editMenu->addAction(mnAddRecipeAct);
    editMenu->addSeparator();
    editMenu->addAction(mnAddIngredientAct);
    editMenu->addSeparator();
    editMenu->addAction(mnEditPantryAct);
    editMenu->addSeparator();

    QMenu* viewMenu = menuBar->addMenu(tr("&View"));
    viewMenu->addAction(mnViewIngredientsAct);
    editMenu->addSeparator();
    viewMenu->addAction(mnViewRecipesAct);
    editMenu->addSeparator();
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

void cookpp::pantryPreviousclicked()
{
    this->currentPage--;
    displayPantry();
}

void cookpp::pantryNextclicked()
{
    this->currentPage++;
    displayPantry();
}


/*----- MN METHODS --------*/
void cookpp::mnMainMenu() 
{
    displayMainMenu();
}

void cookpp::mnGenerateMenu() {
    this->menuGenerator();
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

void cookpp::mnAddRecipe()
{
    this->currentRecipeSelected = new Recipe;
    this->currentRecipeSelected->addAliment(Aliment());
    recipeEditor();
}

void cookpp::mnEditPantry() {
    Pantry* a = new Pantry;
    this->facade->getPantry(a);
    this->facade->getPantry(this->currentPantrySelected);
    pantryEditor();
}



/*----- CLICKED SLOT -----*/
void cookpp::gotoMainMenuclicked()
{
    displayMainMenu();
}

//Ingredient
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

void cookpp::saveIngredientEditclicked()
{
    saveIngredientEdit();
}

void cookpp::editIngredientclicked()
{
    ingredientEditor();
}



//Recipe
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
        QPushButton* editButton = new QPushButton(tr("&Edit"));
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
        notes->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
        notes->setReadOnly(false);
        notes->setAlignment(Qt::AlignCenter);
        notes->setFixedWidth(180);
        notes->setFixedHeight(180);

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

        editButton->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_WIDTH);
        this->currentRecipeSelected = recipeToShow;
        connect(editButton, SIGNAL(clicked()), this, SLOT(editRecipeclicked()));


        QLayout* oldLayout = this->detailBox->layout();
        deleteSpecificLayout(oldLayout);
        grid->addWidget(name, 0,0,1,2);
        grid->addWidget(nutriScore, 1, 0, 1, 2);
        grid->addWidget(notes, 2, 0, 2, 2);
        grid->addWidget(aliments, 0, 2, 4, 1);
        grid->addWidget(steps, 0,3, 4, 1);
        grid->addWidget(infoNutri, 0, 4, 4, 1);
        grid->addWidget(editButton);
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

void cookpp::addNewAlimentInRecipeclicked()
{
    updateCurrentRecipeSelected();
    this->currentRecipeSelected->addAliment(Aliment("Carot"));
    recipeEditor();
}

void cookpp::removeAlimentFromRecipeclicked() {
    QObject* buttonSender = QObject::sender();
    try {
        QString qs = qobject_cast<QToolButton*>(buttonSender)->objectName();
        std::string s = qs.toStdString();

        std::string delimiter = BTN_REMOVE_ALIMENT_SEPARATOR;
        //std::string key = s.substr(0, s.find(delimiter));
        std::string alimentName = s.substr(s.find(delimiter) + 1, s.size());
        this->currentRecipeSelected->removeAliment(alimentName);
        recipeEditor();


    }
    catch (std::exception) {
        OutputDebugStringA("Error with button sender");
    }
}

void cookpp::addNewStepInRecipeclicked() {

    updateCurrentRecipeSelected();
    this->currentRecipeSelected->addStep("New Step");
    recipeEditor();
}

void cookpp::removeStepFromRecipeclicked() {
    QObject* buttonSender = QObject::sender();
    try {
        QString qs = qobject_cast<QToolButton*>(buttonSender)->objectName();
        int pos = qs.toInt();
        updateCurrentRecipeSelected();
        this->currentRecipeSelected->removeStep(pos);
        recipeEditor();


    }
    catch (std::exception) {
        OutputDebugStringA("Error with button sender");
    }
}

void cookpp::saveRecipeEditclicked()
{
    updateCurrentRecipeSelected();
    saveRecipeEdit();
}

void cookpp::editRecipeclicked()
{
    recipeEditor();
}







//Pantry
void cookpp::editPantryclicked() {
    pantryEditor();
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

void cookpp::removeStockedAlimentFromPantryclicked() {
    QObject* buttonSender = QObject::sender();
    try {
        QString qs = qobject_cast<QToolButton*>(buttonSender)->objectName();
        int pos = qs.toInt();
        updateCurrentPantrySelected(false);
        this->currentPantrySelected->removeFromStock(pos);
        pantryEditor();


    }
    catch (std::exception) {
        OutputDebugStringA("Error with button sender");
    }
}

void cookpp::addNewStockedAlimentInPantryclicked() {
    updateCurrentPantrySelected(true);
    pantryEditor();
}

void cookpp::savePantryEditclicked() {
    updateCurrentPantrySelected(false);
    savePantryEdit();
}

//Menu
void cookpp::gotoGenerateMenuclicked() {
    menuGenerator();
}
void cookpp::generateMenuclicked() 
{
    int days = 0;
    int covers = 0;
    QTextEdit* messageOutputBox = new QTextEdit();

    for (int i = 0; i < layout()->count(); ++i)
    {
        QWidget* widget = layout()->itemAt(i)->widget();
        if (widget != NULL)
        {
            QString qname = widget->objectName();
            std::string sname = qname.toStdString();
            if (sname == "nDaysEdit") {
                QLineEdit* item = qobject_cast<QLineEdit*>(widget);
                days = item->text().toInt();
            }
            else if (sname == "nCoversEdit") {
                QLineEdit* item = qobject_cast<QLineEdit*>(widget);
                covers = item->text().toInt();

            }
            else if (sname == "outputBox") {
                //QTextEdit* messageOutputBox = qobject_cast<QTextEdit*>(widget);

            }
        }
    }
    QString* qstr = new QString;
    *qstr = QString::fromStdString("");
    if (days == 0) {
        *qstr = QString::fromStdString("Can't set Days to value 0");
        this->messageOutput->append(*qstr);
        *qstr = QString::fromStdString("");
        this->messageOutput->append(*qstr);
        return;
    }
    if (covers == 0) {
        *qstr = QString::fromStdString("Can't set Servings to value 0");
        this->messageOutput->append(*qstr);
        *qstr = QString::fromStdString("");
        this->messageOutput->append(*qstr);
        return;
    }
    try {
        MenuGenerator* mgen = new MenuGenerator();
        Pantry* pgen = new Pantry();
        Menu menu;
        std::time_t currentTime = std::time(nullptr);
        menu.setStartDate(currentTime);
        this->facade->getPantry(pgen);
        std::forward_list<StockedAliment*> stockedAliment = pgen->getStock();

        std::list<Recipe*> recipesList;
        recipesList = this->facade->getAllRecipe();

        mgen->setListRecipe(recipesList);
        mgen->setStockedAliment(stockedAliment);
        menu = mgen->generateMenu(days, covers, pgen, this->facade);
        menu.writeMenu();

        delete mgen;
        if (menu.getErrorMenu()) {
            *qstr = QString::fromStdString("");
            this->messageOutput->append(*qstr);
            *qstr = QString::fromStdString("Menu could not generate properly !");
            this->messageOutput->append(*qstr);
        }
        else {
            *qstr = QString::fromStdString("");
            this->messageOutput->append(*qstr);
            *qstr = QString::fromStdString("Menu generated in current directory !");
            this->messageOutput->append(*qstr);
        }

    }
    catch (std::exception) {

    }
}
