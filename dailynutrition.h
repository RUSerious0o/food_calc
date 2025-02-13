#ifndef DAILYNUTRITION_H
#define DAILYNUTRITION_H

#include <QWidget>
#include <QCalendarWidget>
#include <QDate>
#include <QTime>

#include "datastorage.h"
#include "foodlistform.h"
#include "ingredientListForm.h"
#include "allFoodListForm.h"
#include "NewItem/newItem.h"

namespace Ui {
class DailyNutrition;
}

class DailyNutrition : public QWidget
{
    Q_OBJECT

public:
    explicit DailyNutrition(QWidget *parent = nullptr);
    ~DailyNutrition();

public slots:
    void updateSelectedDate();
    void onShowCalendarButtonClicked();
    void onRefreshDateClicked();

private:
    Ui::DailyNutrition *ui;
    DataStorage &m_dataStorage;
    FoodListForm *foodListWidget;
    QCalendarWidget *m_calendar;

    void setupSlots();
};

#endif // DAILYNUTRITION_H
