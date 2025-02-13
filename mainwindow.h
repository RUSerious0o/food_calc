#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QString>

#include "DailyNutrition/dailynutrition.h"
#include "ingredientsSummaryForm.h"
#include "dishesSummaryForm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onSectionSelected();

private:
    Ui::MainWindow *ui;
    DailyNutrition *dailyNutritionWidget;
    DishesSummaryForm *dishesWidget;
    IngredientsSummaryForm *ingredientsSummaryWidget;

    const char *DAILY_NUTRITION_SECTION_CAPTION = "Дневник";
    const char *FOOD_LIST_SECTION_CAPTION = "Продукты";
    const char *DISHES_LIST_SECTION_CAPTION = "Блюда";
    const char *PRODUCTS_DB_FILENAME = "res/productsDB.txt";
    const char *MAIN_WINDOW_TITLE = "Калькулятор калорий";
//    const char *MAIN_WINDOW_ICON_PATH = ":/pics/icon_small.ico";

    void setupSectionList();
    void readProductsDB();
};
#endif // MAINWINDOW_H
