#ifndef DISHESSUMMARYFORM_H
#define DISHESSUMMARYFORM_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include "food.h"
#include "dishEditForm.h"
#include "datastorage.h"
#include "FoodList/disheslistform.h"

#include <memory>

class DishesSummaryForm : public QWidget
{
    Q_OBJECT
public:
    explicit DishesSummaryForm(QWidget *parent = nullptr);

    void refresh();

public slots:
    void onAddDishButtonClicked();
    void onDishSelected(const std::shared_ptr<Food>);

signals:


private:
    DataStorage &m_dataStorage;

    QVBoxLayout *mainLayout;
    QPushButton *addDishButton;
    DishesListForm *dishesList;
    DishEditForm *dishEditWidget;

    const char* ADD_DISH_BUTTON_TEXT = "Добавить блюдо";

    void showDishEditForm();
    void hideDishEditForm();

    void setupSlots();
};

#endif // DISHESSUMMARYFORM_H
