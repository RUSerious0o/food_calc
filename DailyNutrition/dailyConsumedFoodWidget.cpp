#include "dailyConsumedFoodWidget.h"

DailyConsumedFoodWidget::DailyConsumedFoodWidget(const QDate &date, QWidget *parent)
    : QWidget(parent)
    , mainLayout(new QVBoxLayout(this))
    , PFCLayout(new QHBoxLayout())
    , proteinsLabel(new QLabel("", this))
    , fatsLabel(new QLabel("", this))
    , carbohsLabel(new QLabel("", this))
    , caloriesLabel(new QLabel("0", this))
    , timePeriodLayouts({
                            new QVBoxLayout(),
                            new QVBoxLayout(),
                            new QVBoxLayout(),
                            new QVBoxLayout(),
                            new QVBoxLayout(),
                            new QVBoxLayout(),
                        })
    , timePeriodCaptionLabels {
                            new QLabel("00:00 - 03:59", this),
                            new QLabel("04:00 - 07:59", this),
                            new QLabel("08:00 - 11:59", this),
                            new QLabel("12:00 - 15:59", this),
                            new QLabel("16:00 - 19:59", this),
                            new QLabel("20:00 - 23:59", this),
          }
    , m_widgets()
    , m_dataStorage(DataStorage::getInstance())
    , m_consumedFood(m_dataStorage.consumedFood(date))
    , proteinsSum(0)
    , fatsSum(0)
    , carbohsSum(0)
    , caloriesSum(0)
{
    setupUi();
    setupConsumedFoodWidgets();

    for(auto layout : timePeriodLayouts) {
        layout->setSpacing(2);
    }

    connect(&m_dataStorage, &DataStorage::foodConsumed, this, &DailyConsumedFoodWidget::onFoodConsumed);
    connect(&m_dataStorage, &DataStorage::consumedFoodRemoved, this, &DailyConsumedFoodWidget::onConsumedFoodRemovedFromDB);

//    setStyleSheet("timePeriodCaptionLabels {font-size: 12px; font-style: bold}");     // TODO
}

void DailyConsumedFoodWidget::onFoodConsumed(DataStorage::ConsumedFood cFood)
{
    m_consumedFood[cFood.recordId] = cFood;
    addConsumedFoodItemWidget(cFood);
    refreshPFCValues();
}

void DailyConsumedFoodWidget::onConsumedFoodRemoveRequested(int recordId)
{
    m_dataStorage.removeConsumedFood(recordId);
}

void DailyConsumedFoodWidget::onConsumedFoodRemovedFromDB(int recordId)
{
    m_widgets[recordId]->hide();
    m_widgets.erase(recordId);
    m_consumedFood.erase(recordId);
    refreshPFCValues();
}

void DailyConsumedFoodWidget::setupUi()
{
    mainLayout->addLayout(PFCLayout);
    PFCLayout->addWidget(new QLabel(tr("Белки: "), this));
    PFCLayout->addWidget(proteinsLabel);
    PFCLayout->addWidget(new QLabel(tr("Жиры: "), this));
    PFCLayout->addWidget(fatsLabel);
    PFCLayout->addWidget(new QLabel(tr("Углеводы: "), this));
    PFCLayout->addWidget(carbohsLabel);
    PFCLayout->addWidget(new QLabel(tr("Калории: "), this));
    PFCLayout->addWidget(caloriesLabel);

    for(int i = 0; i < 6; ++i) {
        mainLayout->addLayout(timePeriodLayouts[i]);
        timePeriodLayouts[i]->addWidget(timePeriodCaptionLabels[i]);
    }
}

void DailyConsumedFoodWidget::setupConsumedFoodWidgets()
{
    for(auto cFood : m_consumedFood) {
        addConsumedFoodItemWidget(cFood.second);
    }

    refreshPFCValues();
}

void DailyConsumedFoodWidget::addConsumedFoodItemWidget(DataStorage::ConsumedFood cFood)
{
    auto widget = new ConsumedFoodItemWidget(cFood.recordId, cFood.foodWeight, cFood.food, this);
    int layoutId = (cFood.time.hour()*60 + cFood.time.minute()) / TIME_PERIOD_LENGTH_MIN;
    timePeriodLayouts[layoutId]->addWidget(widget);
    m_widgets[cFood.recordId] = widget;
    connect(widget, &ConsumedFoodItemWidget::foodItemRemoveRequested, this, &DailyConsumedFoodWidget::onConsumedFoodRemoveRequested);
}

void DailyConsumedFoodWidget::refreshPFCValues()
{
    caloriesSum = 0;
    proteinsSum = 0;
    fatsSum = 0;
    carbohsSum = 0;

    for(auto cFood : m_consumedFood) {
        auto food = cFood.second.food;
        int foodWeight = cFood.second.foodWeight;

        caloriesSum += floor(food->calories() * foodWeight / 10) / 10;
        proteinsSum += floor(food->proteins() * foodWeight / 10) / 10;
        fatsSum += floor(food->fats() * foodWeight / 10) / 10;
        carbohsSum += floor(food->carbohs() * foodWeight / 10) / 10;
    }

    proteinsLabel->setText(QString(PFC_LABEL_PATTERN).arg(proteinsSum).arg(
                           floor(proteinsSum * 4100 / (caloriesSum == 0 ? 1 : caloriesSum)) / 10));
    fatsLabel->setText(QString(PFC_LABEL_PATTERN).arg(fatsSum).arg(
                           floor(fatsSum * 9300 / (caloriesSum == 0 ? 1 : caloriesSum)) / 10));
    carbohsLabel->setText(QString(PFC_LABEL_PATTERN).arg(carbohsSum).arg(
                           floor(carbohsSum * 4100 / (caloriesSum == 0 ? 1 : caloriesSum)) / 10));
    caloriesLabel->setText(QString("%1").arg(caloriesSum));
}
