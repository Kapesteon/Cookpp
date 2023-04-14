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
    "removeStockedAlimentFromPantryclicked",
    "addNewStockedAlimentInPantryclicked",
    "savePantryEditclicked",
    "gotoMainMenuclicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASScookppENDCLASS_t {
    uint offsetsAndSizes[60];
    char stringdata0[7];
    char stringdata1[30];
    char stringdata2[1];
    char stringdata3[26];
    char stringdata4[22];
    char stringdata5[26];
    char stringdata6[22];
    char stringdata7[18];
    char stringdata8[11];
    char stringdata9[18];
    char stringdata10[14];
    char stringdata11[13];
    char stringdata12[16];
    char stringdata13[12];
    char stringdata14[13];
    char stringdata15[28];
    char stringdata16[24];
    char stringdata17[32];
    char stringdata18[22];
    char stringdata19[26];
    char stringdata20[18];
    char stringdata21[22];
    char stringdata22[29];
    char stringdata23[31];
    char stringdata24[26];
    char stringdata25[28];
    char stringdata26[38];
    char stringdata27[36];
    char stringdata28[22];
    char stringdata29[20];
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
        QT_MOC_LITERAL(163, 17),  // "mnViewIngredients"
        QT_MOC_LITERAL(181, 13),  // "mnViewRecipes"
        QT_MOC_LITERAL(195, 12),  // "mnViewPantry"
        QT_MOC_LITERAL(208, 15),  // "mnAddIngredient"
        QT_MOC_LITERAL(224, 11),  // "mnAddRecipe"
        QT_MOC_LITERAL(236, 12),  // "mnEditPantry"
        QT_MOC_LITERAL(249, 27),  // "showIngredientDetailclicked"
        QT_MOC_LITERAL(277, 23),  // "showRecipeDetailclicked"
        QT_MOC_LITERAL(301, 31),  // "showStockedAlimentDetailclicked"
        QT_MOC_LITERAL(333, 21),  // "editIngredientclicked"
        QT_MOC_LITERAL(355, 25),  // "saveIngredientEditclicked"
        QT_MOC_LITERAL(381, 17),  // "editRecipeclicked"
        QT_MOC_LITERAL(399, 21),  // "saveRecipeEditclicked"
        QT_MOC_LITERAL(421, 28),  // "addNewAlimentInRecipeclicked"
        QT_MOC_LITERAL(450, 30),  // "removeAlimentFromRecipeclicked"
        QT_MOC_LITERAL(481, 25),  // "addNewStepInRecipeclicked"
        QT_MOC_LITERAL(507, 27),  // "removeStepFromRecipeclicked"
        QT_MOC_LITERAL(535, 37),  // "removeStockedAlimentFromPantr..."
        QT_MOC_LITERAL(573, 35),  // "addNewStockedAlimentInPantryc..."
        QT_MOC_LITERAL(609, 21),  // "savePantryEditclicked"
        QT_MOC_LITERAL(631, 19)   // "gotoMainMenuclicked"
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
    "removeStockedAlimentFromPantryclicked",
    "addNewStockedAlimentInPantryclicked",
    "savePantryEditclicked",
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
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  182,    2, 0x08,    1 /* Private */,
       3,    0,  183,    2, 0x08,    2 /* Private */,
       4,    0,  184,    2, 0x08,    3 /* Private */,
       5,    0,  185,    2, 0x08,    4 /* Private */,
       6,    0,  186,    2, 0x08,    5 /* Private */,
       7,    0,  187,    2, 0x08,    6 /* Private */,
       8,    0,  188,    2, 0x08,    7 /* Private */,
       9,    0,  189,    2, 0x08,    8 /* Private */,
      10,    0,  190,    2, 0x08,    9 /* Private */,
      11,    0,  191,    2, 0x08,   10 /* Private */,
      12,    0,  192,    2, 0x08,   11 /* Private */,
      13,    0,  193,    2, 0x08,   12 /* Private */,
      14,    0,  194,    2, 0x08,   13 /* Private */,
      15,    0,  195,    2, 0x08,   14 /* Private */,
      16,    0,  196,    2, 0x08,   15 /* Private */,
      17,    0,  197,    2, 0x08,   16 /* Private */,
      18,    0,  198,    2, 0x08,   17 /* Private */,
      19,    0,  199,    2, 0x08,   18 /* Private */,
      20,    0,  200,    2, 0x08,   19 /* Private */,
      21,    0,  201,    2, 0x08,   20 /* Private */,
      22,    0,  202,    2, 0x08,   21 /* Private */,
      23,    0,  203,    2, 0x08,   22 /* Private */,
      24,    0,  204,    2, 0x08,   23 /* Private */,
      25,    0,  205,    2, 0x08,   24 /* Private */,
      26,    0,  206,    2, 0x08,   25 /* Private */,
      27,    0,  207,    2, 0x08,   26 /* Private */,
      28,    0,  208,    2, 0x08,   27 /* Private */,
      29,    0,  209,    2, 0x08,   28 /* Private */,

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
        // method 'removeStockedAlimentFromPantryclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addNewStockedAlimentInPantryclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'savePantryEditclicked'
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
        case 7: _t->mnViewIngredients(); break;
        case 8: _t->mnViewRecipes(); break;
        case 9: _t->mnViewPantry(); break;
        case 10: _t->mnAddIngredient(); break;
        case 11: _t->mnAddRecipe(); break;
        case 12: _t->mnEditPantry(); break;
        case 13: _t->showIngredientDetailclicked(); break;
        case 14: _t->showRecipeDetailclicked(); break;
        case 15: _t->showStockedAlimentDetailclicked(); break;
        case 16: _t->editIngredientclicked(); break;
        case 17: _t->saveIngredientEditclicked(); break;
        case 18: _t->editRecipeclicked(); break;
        case 19: _t->saveRecipeEditclicked(); break;
        case 20: _t->addNewAlimentInRecipeclicked(); break;
        case 21: _t->removeAlimentFromRecipeclicked(); break;
        case 22: _t->addNewStepInRecipeclicked(); break;
        case 23: _t->removeStepFromRecipeclicked(); break;
        case 24: _t->removeStockedAlimentFromPantryclicked(); break;
        case 25: _t->addNewStockedAlimentInPantryclicked(); break;
        case 26: _t->savePantryEditclicked(); break;
        case 27: _t->gotoMainMenuclicked(); break;
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
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 28;
    }
    return _id;
}
QT_WARNING_POP
