#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QListWidget>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dailyNutritionWidget(new DailyNutrition(this))
    , dishesWidget(new DishesSummaryForm(this))
    , ingredientsSummaryWidget (new IngredientsSummaryForm(this))
{
    ui->setupUi(this);
    resize(1024, 768);
//    setWindowIcon(QIcon(MAIN_WINDOW_ICON_PATH));
    setWindowTitle(MAIN_WINDOW_TITLE);

    setupSectionList();

    connect(ui->sectionList, &QListWidget::itemClicked, this, &MainWindow::onSectionSelected);    
}

MainWindow::~MainWindow()
{
    DataStorage::getInstance().exportIngredientsDB();
    delete ui;    
}

void MainWindow::onSectionSelected()
{
     if(ui->sectionList->currentItem()->text() == tr(DAILY_NUTRITION_SECTION_CAPTION)) {
         ui->stackedWidget->setCurrentWidget(dailyNutritionWidget);
    }

    if(ui->sectionList->currentItem()->text() == tr(FOOD_LIST_SECTION_CAPTION)) {        
        ui->stackedWidget->setCurrentWidget(ingredientsSummaryWidget);
    }

    if(ui->sectionList->currentItem()->text() == tr(DISHES_LIST_SECTION_CAPTION)) {
        ui->stackedWidget->setCurrentWidget(dishesWidget);
        dishesWidget->refresh();
    }
}

void MainWindow::setupSectionList()
{
    ui->sectionList->addItems({
                                tr(DAILY_NUTRITION_SECTION_CAPTION),
                                tr(FOOD_LIST_SECTION_CAPTION),
                                tr(DISHES_LIST_SECTION_CAPTION)
                             });

    ui->stackedWidget->addWidget(dailyNutritionWidget);
    ui->stackedWidget->addWidget(ingredientsSummaryWidget);
    ui->stackedWidget->addWidget(dishesWidget);
}

void MainWindow::readProductsDB()
{
    QFile productsDB(PRODUCTS_DB_FILENAME);
    if(!productsDB.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
}

