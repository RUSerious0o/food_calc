#ifndef DISHESLISTFORM_H
#define DISHESLISTFORM_H

#include "FoodList/foodlistform.h"

#include <memory>

class DishesListForm : public FoodListForm
{
public:
    explicit DishesListForm(QWidget *parent = nullptr);

public slots:
    void onDishAddedToDB(std::shared_ptr<Food> newDish);
    void onDishRemovedFromDB(const QString &dishName);
    void onDishesEdited(std::map<QString, std::shared_ptr<Food>>);

protected:
    virtual void setupUniqueSlots() override;

private:
    DataStorage &m_dataStorage;
};

#endif // DISHESLISTFORM_H
