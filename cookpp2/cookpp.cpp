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

    displayAllIngredients();

    resize(600, 600);

}

void cookpp::displayMainMenu() {

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
    //enum { NumDigitButtons = NUMBER_OBJET_PER_PAGE};
    //QToolButton* ingredientsButton[NumDigitButtons];
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

            }
            else {
                std::string n = (*itr)->getName();
                ingredientsButton->push_back(new QToolButton());
                ingredientsButton->back()->setText(tr(n.c_str()));
                ingredientsButton->back()->setFixedSize(BTN_FIXED_WIDTH, BTN_FIXED_HEIGHT);
                itr++;
            }


        }
        catch (std::exception) {
            return;
        }
    }

    return;

        
}

void cookpp::deleteCurrentView()
{
    QLayoutItem* item;
    while ((item = layout()->takeAt(0)) != NULL)
    {
        delete item->widget();
        delete item;
    }
    delete layout();
}

void cookpp::displayAllIngredients()
{
    //Delete old layout to drwn the new https://forum.qt.io/topic/14898/howto-change-layout-of-a-widget/10
    if (layout())
    {
        deleteCurrentView();
    }

    QGridLayout* mainLayout = new QGridLayout;

    FacadeUserDB * facade = new FacadeUserDB();
    std::list<Ingredient*>  listIngredient;
    
    listIngredient = facade->getAllIngredient();
    int maxPage = (listIngredient.size() + NUMBER_OBJET_PER_PAGE - 1) / NUMBER_OBJET_PER_PAGE; //get ceilling

    std::vector<QToolButton*> ingredientsButton;

    if (this->currentpage < 0) {
        this->currentpage = 0;
    }
    if (this->currentpage > maxPage) {
        this->currentpage = maxPage;
    }
 

    getPageIngredient(this->currentpage, &listIngredient, &ingredientsButton);



    for (int i = 0; i < NUMBER_OBJET_PER_PAGE; ++i) {
        int row = i / 3;
        int column = ((i) % 3) + 1;
        mainLayout->addWidget(ingredientsButton.at(i), row, column);
    }
    
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

    setLayout(mainLayout);

    delete facade;

    setWindowTitle(tr("Cook++ - Ingredients"));

}



cookpp::~cookpp()
{}

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

void cookpp::ingredientListNextclicked()
{
    this->currentpage++;
    displayAllIngredients();
    OutputDebugStringA("Next page ! \n");
    std::cout << "Next page ! \n";
}

void cookpp::ingredientListPreviousclicked() 
{
    this->currentpage--;
    displayAllIngredients();
    OutputDebugStringA("Previous page ! \n");
    std::cout << "Previous page ! \n";
}