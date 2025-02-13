#ifndef DAILYNUTRITION_H
#define DAILYNUTRITION_H

#include <QWidget>
#include <QCalendarWidget>
#include <QDate>
#include <QTime>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QSpinBox>
#include <QComboBox>

#include <memory>

#include "datastorage.h"
#include "FoodList/allFoodListForm.h"
#include "DailyNutrition/dailyConsumedFoodWidget.h"
#include "food.h"

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
    void refreshSelectedTime();
    void onShowCalendarButtonClicked();
    void onRefreshDateClicked();
    void onFoodSelected(std::shared_ptr<Food>);
    void onSelectedTimeHoursChanged(int);
    void onSelectedTimeMinutesChanged(int);
    void onConsumeFoodButtonClicked();

private:
    Ui::DailyNutrition *ui;
    DataStorage &m_dataStorage;
    FoodListForm *foodListWidget;
    QCalendarWidget *m_calendar;
    DailyConsumedFoodWidget *dailyConsWidget;
    std::shared_ptr<Food> m_selectedFood;
    QDate m_selectedDate;
    QTime m_selectedTime;

    void setupSlots();
};

#endif // DAILYNUTRITION_H
