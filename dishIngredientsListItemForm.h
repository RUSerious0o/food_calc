#ifndef DISHINGREDIENTSLISTITEMFORM_H
#define DISHINGREDIENTSLISTITEMFORM_H

#include <QWidget>
#include <QMouseEvent>

#include <memory>

#include "food.h"

namespace Ui {
class DishIngredientsListItemForm;
}

class DishIngredientsListItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit DishIngredientsListItemForm(const std::shared_ptr<Food> food, int weight, QWidget *parent = nullptr);
    ~DishIngredientsListItemForm();

signals:
    void itemClicked(const std::shared_ptr<Food> food, int weight);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::DishIngredientsListItemForm *ui;
    std::shared_ptr<Food> m_food;
    int m_weight;
};

#endif // DISHINGREDIENTSLISTITEMFORM_H
