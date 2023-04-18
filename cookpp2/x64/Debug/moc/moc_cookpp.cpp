/****************************************************************************
** Meta object code from reading C++ file 'cookpp.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../cookpp.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cookpp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASScookppENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASScookppENDCLASS = QtMocHelpers::stringData(
    "cookpp",
    "ingredientListPreviousclicked",
    "",
    "ingredientListNextclicked",
    "recipeListNextclicked",
    "recipeListPreviousclicked",
    "pantryPreviousclicked",
    "pantryNextclicked",
    "mnMainMenu",
    "mnGenerateMenu",
    "mnViewIngredients",
    "mnViewRecipes",
    "mnViewPantry",
    "mnAddIngredient",
    "mnAddRecipe",
    "mnEditPantry",
    "showIngredientDetailclicked",
    "showRecipeDetailclicked",
    "showStockedAlimentDetailclicked",
    "editIngredientclicked",
    "saveIngredientEditclicked",
    "editRecipeclicked",
    "saveRecipeEditclicked",
    "addNewAlimentInRecipeclicked",
    "removeAlimentFromRecipeclicked",
    "addNewStepInRecipeclicked",
    "removeStepFromRecipeclicked",
    "editPantryclicked",
    "removeStockedAlimentFromPantryclicked",
    "addNewStockedAlimentInPantryclicked",
    "savePantryEditclicked",
    "gotoGenerateMenuclicked",
    "generateMenuclicked",
    "gotoMainMenuclicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASScookppENDCLASS_t {
    uint offsetsAndSizes[68];
    char stringdata0[7];
    char stringdata1[30];
    char stringdata2[1];
    char stringdata3[26];
    char stringdata4[22];
    char stringdata5[26];
    char stringdata6[22];
    char stringdata7[18];
    char stringdata8[11];
    char stringdata9[15];
    char stringdata10[18];
    char stringdata11[14];
    char stringdata12[13];
    char stringdata13[16];
    char stringdata14[12];
    char stringdata15[13];
    char stringdata16[28];
    char stringdata17[24];
    char stringdata18[32];
    char stringdata19[22];
    char stringdata20[26];
    char stringdata21[18];
    char stringdata22[22];
    char stringdata23[29];
    char stringdata24[31];
    char stringdata25[26];
    char stringdata26[28];
    char stringdata27[18];
    char stringdata28[38];
    char stringdata29[36];
    char stringdata30[22];
    char stringdata31[24];
    char stringdata32[20];
    char stringdata33[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASScookppENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASScookppENDCLASS_t qt_meta_stringdata_CLASScookppENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "cookpp"
        QT_MOC_LITERAL(7, 29),  // "ingredientListPreviousclicked"
        QT_MOC_LITERAL(37, 0),  // ""
        QT_MOC_LITERAL(38, 25),  // "ingredientListNextclicked"
        QT_MOC_LITERAL(64, 21),  // "recipeListNextclicked"
        QT_MOC_LITERAL(86, 25),  // "recipeListPreviousclicked"
        QT_MOC_LITERAL(112, 21),  // "pantryPreviousclicked"
        QT_MOC_LITERAL(134, 17),  // "pantryNextclicked"
        QT_MOC_LITERAL(152, 10),  // "mnMainMenu"
        QT_MOC_LITERAL(163, 14),  // "mnGenerateMenu"
        QT_MOC_LITERAL(178, 17),  // "mnViewIngredients"
        QT_MOC_LITERAL(196, 13),  // "mnViewRecipes"
        QT_MOC_LITERAL(210, 12),  // "mnViewPantry"
        QT_MOC_LITERAL(223, 15),  // "mnAddIngredient"
        QT_MOC_LITERAL(239, 11),  // "mnAddRecipe"
        QT_MOC_LITERAL(251, 12),  // "mnEditPantry"
        QT_MOC_LITERAL(264, 27),  // "showIngredientDetailclicked"
        QT_MOC_LITERAL(292, 23),  // "showRecipeDetailclicked"
        QT_MOC_LITERAL(316, 31),  // "showStockedAlimentDetailclicked"
        QT_MOC_LITERAL(348, 21),  // "editIngredientclicked"
        QT_MOC_LITERAL(370, 25),  // "saveIngredientEditclicked"
        QT_MOC_LITERAL(396, 17),  // "editRecipeclicked"
        QT_MOC_LITERAL(414, 21),  // "saveRecipeEditclicked"
        QT_MOC_LITERAL(436, 28),  // "addNewAlimentInRecipeclicked"
        QT_MOC_LITERAL(465, 30),  // "removeAlimentFromRecipeclicked"
        QT_MOC_LITERAL(496, 25),  // "addNewStepInRecipeclicked"
        QT_MOC_LITERAL(522, 27),  // "removeStepFromRecipeclicked"
        QT_MOC_LITERAL(550, 17),  // "editPantryclicked"
        QT_MOC_LITERAL(568, 37),  // "removeStockedAlimentFromPantr..."
        QT_MOC_LITERAL(606, 35),  // "addNewStockedAlimentInPantryc..."
        QT_MOC_LITERAL(642, 21),  // "savePantryEditclicked"
        QT_MOC_LITERAL(664, 23),  // "gotoGenerateMenuclicked"
        QT_MOC_LITERAL(688, 19),  // "generateMenuclicked"
        QT_MOC_LITERAL(708, 19)   // "gotoMainMenuclicked"
    },
    "cookpp",
    "ingredientListPreviousclicked",
    "",
    "ingredientListNextclicked",
    "recipeListNextclicked",
    "recipeListPreviousclicked",
    "pantryPreviousclicked",
    "pantryNextclicked",
    "mnMainMenu",
    "mnGenerateMenu",
    "mnViewIngredients",
    "mnViewRecipes",
    "mnViewPantry",
    "mnAddIngredient",
    "mnAddRecipe",
    "mnEditPantry",
    "showIngredientDetailclicked",
    "showRecipeDetailclicked",
    "showStockedAlimentDetailclicked",
    "editIngredientclicked",
    "saveIngredientEditclicked",
    "editRecipeclicked",
    "saveRecipeEditclicked",
    "addNewAlimentInRecipeclicked",
    "removeAlimentFromRecipeclicked",
    "addNewStepInRecipeclicked",
    "removeStepFromRecipeclicked",
    "editPantryclicked",
    "removeStockedAlimentFromPantryclicked",
    "addNewStockedAlimentInPantryclicked",
    "savePantryEditclicked",
    "gotoGenerateMenuclicked",
    "generateMenuclicked",
    "gotoMainMenuclicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASScookppENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  206,    2, 0x08,    1 /* Private */,
       3,    0,  207,    2, 0x08,    2 /* Private */,
       4,    0,  208,    2, 0x08,    3 /* Private */,
       5,    0,  209,    2, 0x08,    4 /* Private */,
       6,    0,  210,    2, 0x08,    5 /* Private */,
       7,    0,  211,    2, 0x08,    6 /* Private */,
       8,    0,  212,    2, 0x08,    7 /* Private */,
       9,    0,  213,    2, 0x08,    8 /* Private */,
      10,    0,  214,    2, 0x08,    9 /* Private */,
      11,    0,  215,    2, 0x08,   10 /* Private */,
      12,    0,  216,    2, 0x08,   11 /* Private */,
      13,    0,  217,    2, 0x08,   12 /* Private */,
      14,    0,  218,    2, 0x08,   13 /* Private */,
      15,    0,  219,    2, 0x08,   14 /* Private */,
      16,    0,  220,    2, 0x08,   15 /* Private */,
      17,    0,  221,    2, 0x08,   16 /* Private */,
      18,    0,  222,    2, 0x08,   17 /* Private */,
      19,    0,  223,    2, 0x08,   18 /* Private */,
      20,    0,  224,    2, 0x08,   19 /* Private */,
      21,    0,  225,    2, 0x08,   20 /* Private */,
      22,    0,  226,    2, 0x08,   21 /* Private */,
      23,    0,  227,    2, 0x08,   22 /* Private */,
      24,    0,  228,    2, 0x08,   23 /* Private */,
      25,    0,  229,    2, 0x08,   24 /* Private */,
      26,    0,  230,    2, 0x08,   25 /* Private */,
      27,    0,  231,    2, 0x08,   26 /* Private */,
      28,    0,  232,    2, 0x08,   27 /* Private */,
      29,    0,  233,    2, 0x08,   28 /* Private */,
      30,    0,  234,    2, 0x08,   29 /* Private */,
      31,    0,  235,    2, 0x08,   30 /* Private */,
      32,    0,  236,    2, 0x08,   31 /* Private */,
      33,    0,  237,    2, 0x08,   32 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject cookpp::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASScookppENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASScookppENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASScookppENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<cookpp, std::true_type>,
        // method 'ingredientListPreviousclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ingredientListNextclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recipeListNextclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recipeListPreviousclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pantryPreviousclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pantryNextclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mnMainMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mnGenerateMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mnViewIngredients'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mnViewRecipes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mnViewPantry'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mnAddIngredient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mnAddRecipe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mnEditPantry'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showIngredientDetailclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showRecipeDetailclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showStockedAlimentDetailclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editIngredientclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveIngredientEditclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editRecipeclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveRecipeEditclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addNewAlimentInRecipeclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeAlimentFromRecipeclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addNewStepInRecipeclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeStepFromRecipeclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editPantryclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeStockedAlimentFromPantryclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addNewStockedAlimentInPantryclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'savePantryEditclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'gotoGenerateMenuclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'generateMenuclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'gotoMainMenuclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void cookpp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<cookpp *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ingredientListPreviousclicked(); break;
        case 1: _t->ingredientListNextclicked(); break;
        case 2: _t->recipeListNextclicked(); break;
        case 3: _t->recipeListPreviousclicked(); break;
        case 4: _t->pantryPreviousclicked(); break;
        case 5: _t->pantryNextclicked(); break;
        case 6: _t->mnMainMenu(); break;
        case 7: _t->mnGenerateMenu(); break;
        case 8: _t->mnViewIngredients(); break;
        case 9: _t->mnViewRecipes(); break;
        case 10: _t->mnViewPantry(); break;
        case 11: _t->mnAddIngredient(); break;
        case 12: _t->mnAddRecipe(); break;
        case 13: _t->mnEditPantry(); break;
        case 14: _t->showIngredientDetailclicked(); break;
        case 15: _t->showRecipeDetailclicked(); break;
        case 16: _t->showStockedAlimentDetailclicked(); break;
        case 17: _t->editIngredientclicked(); break;
        case 18: _t->saveIngredientEditclicked(); break;
        case 19: _t->editRecipeclicked(); break;
        case 20: _t->saveRecipeEditclicked(); break;
        case 21: _t->addNewAlimentInRecipeclicked(); break;
        case 22: _t->removeAlimentFromRecipeclicked(); break;
        case 23: _t->addNewStepInRecipeclicked(); break;
        case 24: _t->removeStepFromRecipeclicked(); break;
        case 25: _t->editPantryclicked(); break;
        case 26: _t->removeStockedAlimentFromPantryclicked(); break;
        case 27: _t->addNewStockedAlimentInPantryclicked(); break;
        case 28: _t->savePantryEditclicked(); break;
        case 29: _t->gotoGenerateMenuclicked(); break;
        case 30: _t->generateMenuclicked(); break;
        case 31: _t->gotoMainMenuclicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *cookpp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cookpp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASScookppENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int cookpp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 32)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 32;
    }
    return _id;
}
QT_WARNING_POP
