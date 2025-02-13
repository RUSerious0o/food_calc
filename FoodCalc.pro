QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DailyNutrition/consumedFoodItemEventFilter.cpp \
    DailyNutrition/consumedFoodItemWidget.cpp \
    DailyNutrition/dailyConsumedFoodWidget.cpp \
    DailyNutrition/dailynutrition.cpp \
    FoodList/allFoodListForm.cpp \
    FoodList/disheslistform.cpp \
    FoodList/foodlistform.cpp \
    FoodList/ingredientListForm.cpp \
    FoodList/productslistitem.cpp \
    datastorage.cpp \
    dish.cpp \
    dishEditForm.cpp \
    dishIngredientsListItemForm.cpp \
    dishesSummaryForm.cpp \
    food.cpp \
    ingredientsSummaryForm.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DailyNutrition/consumedFoodItemEventFilter.h \
    DailyNutrition/consumedFoodItemWidget.h \
    DailyNutrition/dailyConsumedFoodWidget.h \
    DailyNutrition/dailynutrition.h \
    FoodList/allFoodListForm.h \
    FoodList/disheslistform.h \
    FoodList/foodlistform.h \
    FoodList/ingredientListForm.h \
    FoodList/productslistitem.h \
    datastorage.h \
    dish.h \
    dishEditForm.h \
    dishIngredientsListItemForm.h \
    dishesSummaryForm.h \
    food.h \
    ingredientsSummaryForm.h \
    mainwindow.h

FORMS += \
    DailyNutrition/dailynutrition.ui \
    FoodList/foodlistform.ui \
    FoodList/productslistitem.ui \
    dishEditForm.ui \
    dishIngredientsListItemForm.ui \
    ingredientsSummaryForm.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = ./pics/icon_small.ico

RESOURCES += \
    res.qrc
