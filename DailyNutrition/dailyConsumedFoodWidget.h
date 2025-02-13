#ifndef DAILYCONSUMEDFOODWIDGET_H
#define DAILYCONSUMEDFOODWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDate>

#include <vector>

#include "datastorage.h"
#include "consumedFoodItemWidget.h"

class DailyConsumedFoodWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DailyConsumedFoodWidget(const QDate &date, QWidget *parent = nullptr);

public slots:
    void onFoodConsumed(DataStorage::ConsumedFood food);
    void onConsumedFoodRemoveRequested(int recordId);
    void onConsumedFoodRemovedFromDB(int recordId);

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *PFCLayout;
    QLabel *proteinsLabel;
    QLabel *fatsLabel;
    QLabel *carbohsLabel;
    QLabel *caloriesLabel;

    std::vector<QVBoxLayout*> timePeriodLayouts;
    std::vector<QLabel*> timePeriodCaptionLabels;
    std::map<int, ConsumedFoodItemWidget*> m_widgets;

    DataStorage &m_dataStorage;
    std::map<int, DataStorage::ConsumedFood> m_consumedFood;

    double proteinsSum;
    double fatsSum;
    double carbohsSum;
    double caloriesSum;

    const int TIME_PERIOD_LENGTH_MIN = 240;
    const QString PFC_LABEL_PATTERN = "%1 г / %2 \%";

    void setupUi();
    void setupConsumedFoodWidgets();
    void addConsumedFoodItemWidget(DataStorage::ConsumedFood cFood);
    void refreshPFCValues();
};

#endif // DAILYCONSUMEDFOODWIDGET_H
