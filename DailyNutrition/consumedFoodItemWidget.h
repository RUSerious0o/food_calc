#ifndef CONSUMEDFOODITEMWIDGET_H
#define CONSUMEDFOODITEMWIDGET_H

#include <QObject>
#include <QWidget>

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

#include <QTime>
#include <QEvent>
#include <QDebug>
#include <QFrame>

#include <memory>

#include "food.h"
#include "consumedFoodItemEventFilter.h"

class ConsumedFoodItemWidget : public QFrame
{
    Q_OBJECT
public:
    explicit ConsumedFoodItemWidget(int recordId, int foodWeight, std::shared_ptr<Food> food, QWidget *parent = nullptr);

public slots:
    void onItemRemoveRequested();

signals:
    void foodItemRemoveRequested(int recordId);

private:
    int m_recordId;
    int m_foodWeight;
    std::shared_ptr<Food> m_food;

    QHBoxLayout *mainLayout;
    QLabel *foodNameLabel;
    QLabel *foodWeightLabel;
    QLabel *deleteItemLabel;
    QLabel *foodCalsLabel;

    ConsumedFoodItemEventFilter *m_eventFilter;
};

#endif // CONSUMEDFOODITEMWIDGET_H
