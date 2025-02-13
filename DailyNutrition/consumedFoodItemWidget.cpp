#include "consumedFoodItemWidget.h"

ConsumedFoodItemWidget::ConsumedFoodItemWidget(int recordId, int foodWeight, std::shared_ptr<Food> food, QWidget *parent)
    : QFrame(parent)
    , m_recordId(recordId)
    , m_foodWeight(foodWeight)
    , m_food(food)
    , mainLayout(new QHBoxLayout(this))
    , foodNameLabel(new QLabel(food->name(), this))
    , foodWeightLabel(new QLabel(QString("%1 г").arg(foodWeight), this))    
    , deleteItemLabel(new QLabel("", this))
    , foodCalsLabel(new QLabel(QString("%1 ккал").arg(food->calories() * float(foodWeight) / 100), this))
    , m_eventFilter(new ConsumedFoodItemEventFilter(this))
{    
    mainLayout->addSpacing(2);
    mainLayout->setContentsMargins(2,4,2,2);
    mainLayout->addWidget(foodNameLabel);
    mainLayout->addWidget(foodCalsLabel);
    mainLayout->addWidget(foodWeightLabel);

    deleteItemLabel->setPixmap(QPixmap(":/pics/delete_icon_16.png"));
    deleteItemLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mainLayout->addWidget(deleteItemLabel);

    mainLayout->setStretch(0,1);
    mainLayout->setStretch(1,4);
    mainLayout->setStretch(2,0);
    mainLayout->setStretch(3,0);
    mainLayout->setStretch(4,0);

    deleteItemLabel->installEventFilter(m_eventFilter);
    connect(m_eventFilter, &ConsumedFoodItemEventFilter::removeRequested, this, &ConsumedFoodItemWidget::onItemRemoveRequested);

    this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->setLineWidth(2);

//    setStyleSheet("ConsumedFoodItemWidget {border-width: 1px; border-style: ridge; border-radius: 6px}"); -- закругление - ОК, но выглядит вырвиглазно
}

void ConsumedFoodItemWidget::onItemRemoveRequested()
{
    emit foodItemRemoveRequested(m_recordId);
}
